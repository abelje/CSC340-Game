#include "world.h"
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include "vec.h"
#include "physics.h"
#include <iostream>

World::World(int width, int height)
    : tilemap(width, height) {}

void World::add_platform(float x, float y, float width, float height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tilemap(x+j, y+i) = Tile::Platform;
        }
    }
}

bool World::collides(const Vec<float>& position) const {
    int x = std::floor(position.x);
    int y = std::floor(position.y);
    return tilemap(x, y) == Tile::Platform;
}

GameObject *World::create_player(World& world) {
    player = std::make_unique<GameObject>(Vec<float>{10, 5}, Vec<int>{1,1}, world);
    return player.get();
}

void World::update(float dt) {
    // currently only updating player
    auto position = player->physics.position;
    auto velocity = player->physics.velocity;
    auto acceleration = player->physics.acceleration;

    velocity += 0.5f * acceleration * dt;
    position += velocity * dt;
    velocity += 0.5f * acceleration * dt;
    velocity.x *= player->physics.damping;

    // No infinite speed
    velocity.x = std::clamp(velocity.x, -player->physics.terminal_velocity, player->physics.terminal_velocity);
    velocity.y = std::clamp(velocity.y, -player->physics.terminal_velocity, player->physics.terminal_velocity);

    // check for x collisions
    // check for collisions in the world - x direction
    Vec<float> future_position{position.x, player->physics.position.y};
    Vec<float> future_velocity{velocity.x, 0};
    move_to(future_position, player->size, future_velocity);

    // y collisions
    // now y direction after (maybe) moving in x
    future_velocity.y = velocity.y;
    future_position.y = position.y;
    move_to(future_position, player->size, future_velocity);

    // update the player position and velocity
    player->physics.position = future_position;
    player->physics.velocity = future_velocity;
}

void World::move_to(Vec<float>& position, const Vec<int>& size, Vec<float>& velocity) {
    // test for collisions on the bottom or top first
    float right_x = position.x + size.x;
    float up_y   = position.y + size.y;

    if (collides(position) && collides({right_x, position.y})) { // bottom
        position.y = static_cast<float>(ceil(position.y));
        velocity.y = 0;
    }
    else if (collides({position.x, up_y}) && collides({right_x, up_y})) {
        position.y = std::floor(up_y) - size.y;
        velocity.y = 0;
    }
    // then test for collisions on the left and right sides
    if (collides(position) && collides({position.x, up_y})) {
        // left side
        position.x = ceil(position.x);
        velocity.x = 0;
    }
    else if (collides({right_x, position.y}) && collides({right_x, up_y})) {
        // right side
        position.x = floor(right_x) - size.x;
        velocity.x = 0;
    }
    // now test each corner

    // exclude the bottom right so the combination of left and right doesn't stack with this
    if (collides(position) && !collides({right_x, position.y})) {
        // bottom left
        double dx = ceil(position.x) - position.x;
        double dy = ceil(position.y) - position.y;
        if (dx > dy) {
            position.y = ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = ceil(position.x);
            velocity.x = 0;
        }
    }
    else if (collides({right_x, position.y}) && !collides(position)) {
        // bottom right
        double dx = right_x - floor(right_x);
        double dy = ceil(position.y) - position.y;
        if (dx > dy) {
            position.y = ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = floor(position.x);
            velocity.x = 0;
        }
    }
    if (collides({right_x, up_y}) && !collides({position.x, up_y})) {
        // top right
        double dx = right_x - floor(right_x);
        double dy = up_y - floor(up_y);
        if (dx > dy) {
            position.y = floor(up_y) - size.y;
            velocity.y = 0;
        }
        else {
            position.x = floor(right_x) - size.x;
            velocity.x = 0;
        }
    }
    else if (collides({position.x, up_y}) && !collides({right_x, up_y})) {
        // top left
        double dx = ceil(position.x) - position.x;
        double dy = up_y - floor(up_y);
        if (dx > dy) {
            position.y = floor(up_y) - size.y;
            velocity.y = 0;
        }
        else {
            position.x = ceil(right_x) - size.x;
            velocity.x = 0;
        }
    }
}