#include "game_object.h"

#include <iostream>

#include "physics.h"
#include "world.h"
#include "graphics.h"
#include "action.h"
#include "fsm.h"

GameObject::GameObject(const Vec<float> &position, const Vec<int> &size, World &world, FSM* fsm, Input* input, Color color)
    : physics{position, {0,0}, {0, 0}}, size{size}, fsm{fsm}, input{input}, color{color} {
    fsm->current_state->on_enter(world, *this);
}

GameObject::~GameObject() {

}

// void GameObject::input(World &world) {
//     const bool *key_states = SDL_GetKeyboardState(NULL);
//
//     ActionType action_type = ActionType::None;
//
//     if (key_states[SDL_SCANCODE_LCTRL] || key_states[SDL_SCANCODE_RCTRL]) {
//         action_type = ActionType::Sprint;
//     }
//     // check for both W,D -> UpRight
//     if (key_states[SDL_SCANCODE_W] && key_states[SDL_SCANCODE_D]) {
//         action_type = ActionType::MoveUpRight;
//     }
//     // check for both W,A -> UpLeft
//     else if (key_states[SDL_SCANCODE_W] && key_states[SDL_SCANCODE_A]) {
//         action_type = ActionType::MoveUpLeft;
//     }
//     // check for both W,S -> Stop
//     else if (key_states[SDL_SCANCODE_W] && key_states[SDL_SCANCODE_S]) {
//         action_type = ActionType::None;
//     }
//     // check A,D -> Stop
//     else if (key_states[SDL_SCANCODE_A] && key_states[SDL_SCANCODE_D]) {
//         action_type = ActionType::None;
//     }
//     // check for both S,A -> DownLeft
//     else if (key_states[SDL_SCANCODE_S] && key_states[SDL_SCANCODE_A]) {
//         action_type = ActionType::MoveDownLeft;
//     }
//     // check for both S,D -> DownRight
//     else if (key_states[SDL_SCANCODE_S] && key_states[SDL_SCANCODE_D]) {
//         action_type = ActionType::MoveDownRight;
//     }
//     else if (key_states[SDL_SCANCODE_W]) {
//         action_type = ActionType::MoveUp;
//     }
//     else if (key_states[SDL_SCANCODE_A]) {
//         action_type = ActionType::MoveLeft;
//     }
//     else if (key_states[SDL_SCANCODE_S]) {
//         action_type = ActionType::MoveDown;
//     }
//     else if (key_states[SDL_SCANCODE_D]) {
//         action_type = ActionType::MoveRight;
//     }
//
//     Action* action = fsm->current_state->input(world, *this, action_type);
//     if (action != nullptr) {
//         action->perform(world, *this);
//         delete action;
//     }
// }

void GameObject::update(World &world, double dt) {

}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {physics.position,color};
}
