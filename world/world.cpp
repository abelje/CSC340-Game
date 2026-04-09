#include "world.h"
#include <SDL3/SDL_rect.h>
#include <algorithm>

#include "game_object.h"
#include "vec.h"
#include "physics.h"
#include "fsm.h"
#include "states.h"
#include "keyboard_input.h"
#include "level.h"
#include "audio.h"
#include "events.h"

World::World(const Level& level, Audio& audio, GameObject* player, Events events)
    : tilemap{level.width, level.height}, audio{&audio}, player{player}, events{events} {
    load_level(level);
}

World::~World() {
    for (auto obj : game_objects) {
        if (obj == player) continue;
        delete obj;
    }
}

void World::add_platform(float x, float y, float width, float height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tilemap(x+j, y+i) = Tile{};
        }
    }
}

bool World::collides(const Vec<float>& position) const {
    int x = std::floor(position.x);
    int y = std::floor(position.y);
    return tilemap(x, y).blocking;
}

void World::update(float dt) {
    for (auto& obj : game_objects) {
        // currently only updating player
        obj->update(*this, dt);
        auto position = obj->physics.position;
        auto velocity = obj->physics.velocity;
        auto acceleration = obj->physics.acceleration;

        velocity += 0.5f * acceleration * dt;
        position += velocity * dt;
        velocity += 0.5f * acceleration * dt;
        velocity *= {obj->physics.damping, obj->physics.damping};

        velocity.x = std::clamp(velocity.x, -obj->physics.terminal_velocity, obj->physics.terminal_velocity);
        velocity.y = std::clamp(velocity.y, -obj->physics.terminal_velocity, obj->physics.terminal_velocity);

        // check for x collisions
        // Check for collisions with the world - x direction
        Vec<float> future_position{position.x, obj->physics.position.y};
        Vec<float> future_velocity{velocity.x, 0};
        move_to(future_position, obj->size, future_velocity);

        // y direction attempt after (maybe) moving in x
        future_velocity.y = velocity.y;
        future_position.y = position.y;
        move_to(future_position, obj->size, future_velocity);

        // update player
        obj->physics.position = future_position;
        obj->physics.velocity = future_velocity;

        touch_tiles(*obj);
    }
}

void World::move_to(Vec<float>& position, const Vec<int>& size, Vec<float>& velocity) {
    // test sides first. if both collide move backward
    // bottom side
    if (collides(position) && collides({position.x + size.x, position.y})) {
        position.y = std::ceil(position.y);
        velocity.y = 0;
    }
    // top side
    else if (collides({position.x, position.y + size.y}) && collides({position.x + size.x, position.y + size.y})) {
        position.y = std::floor(position.y);
        velocity.y = 0;
    }
    // left side
    if (collides(position) && collides({position.x, position.y + size.y})) {
        position.x = std::ceil(position.x);
        velocity.x = 0;
    }
    // right side
    else if (collides({position.x + size.x, position.y}) && collides({position.x + size.x, position.y + size.y})) {
        position.x = std::floor(position.x);
        velocity.x = 0;
    }
    // test corners next, move back in smaller axis
    if (collides(position)) {
        float dx = std::ceil(position.x) - position.x;
        float dy = std::ceil(position.y) - position.y;
        if (dx > dy) {
            position.y = std::ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::ceil(position.x);
            velocity.x = 0;
        }
    }
    else if (collides({position.x, position.y + size.y})) {
        float dx = std::ceil(position.x) - position.x;
        float dy = position.y - std::floor(position.y);
        if (dx > dy) {
            position.y = std::floor(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::ceil(position.x);
            velocity.x = 0;
        }
    }
    else if (collides({position.x + size.x, position.y})) {
        float dx = position.x - std::floor(position.x);
        float dy = std::ceil(position.y) - position.y;
        if (dx > dy) {
            position.y = std::ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::floor(position.x);
            velocity.x = 0;
        }
    }
    else if (collides({position.x + size.x, position.y + size.y})) {
        float dx = position.x - std::floor(position.x);
        float dy = position.y - std::floor(position.y);
        if (dx > dy) {
            position.y = std::floor(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::floor(position.x);
            velocity.x = 0;
        }
    }
}

void World::load_level(const Level& level) {
    for (const auto& [pos, tile_id] : level.tile_locations) {
        tilemap(pos.x, pos.y) = level.tile_types.at(tile_id);
    }
    audio->load_sounds({});

    // get all enemies
    for (const auto& [pos, enemy_name] : level.enemy_locations) {
        auto enemy = new GameObject{enemy_name, nullptr, nullptr, Color{0, 0, 0, 0}};
        enemy->physics.position = pos;
        game_objects.push_back(enemy);
    }

    game_objects.push_back(player);
}

void World::touch_tiles(GameObject &obj) {
    int x = std::floor(obj.physics.position.x);
    int y = std::floor(obj.physics.position.y);
    const std::vector<Vec<int>> displacements {{0, 0}, {obj.size.x, 0}, {0, obj.size.y}, {obj.size.x, obj.size.y}};
    for (const auto& displacement : displacements) {
        Tile& tile = tilemap(x + displacement.x, y + displacement.y);
        if (!tile.event_name.empty()) {
            auto itr = events.find(tile.event_name);
            if (itr == events.end()) {
                throw std::runtime_error("Cannot find event: " + tile.event_name);
            }
            itr->second->perform(*this, obj);
        }
    }
}
