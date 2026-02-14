#include "game_object.h"

#include "physics.h"
#include "world.h"
#include "graphics.h"

GameObject::GameObject(const Vec<float> &position, const Vec<int> &size, World &world)
    : physics{position, {0,0}, {0, 0}}, size{size} {}

GameObject::~GameObject() {

}

void GameObject::input(World &world) {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    physics.acceleration.x = 0;
    physics.acceleration.y = 0;
    if (key_states[SDL_SCANCODE_W]) {
        physics.acceleration.y += physics.walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_A]) {
        physics.acceleration.x += -physics.walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_S]) {
        physics.acceleration.y += -physics.walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_D]) {
        physics.acceleration.x += physics.walk_acceleration;
    }
}

void GameObject::update(World &world, double dt) {

}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {physics.position,{255, 0, 255, 255}};
}
