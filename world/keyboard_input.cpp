#include "keyboard_input.h"
#include "game_object.h"
#include "fsm.h"

void KeyboardInput::get_input() {
    if (next_action_type == ActionType::Sprint || next_action_type == ActionType::AttackAll) return;
    const bool *key_states = SDL_GetKeyboardState(NULL);

    // check for both W,D -> UpRight
    if (key_states[SDL_SCANCODE_W] && key_states[SDL_SCANCODE_D]) {
        next_action_type = ActionType::MoveUpRight;
    }
    // check for both W,A -> UpLeft
    else if (key_states[SDL_SCANCODE_W] && key_states[SDL_SCANCODE_A]) {
        next_action_type = ActionType::MoveUpLeft;
    }
    // check for both W,S -> Stop
    else if (key_states[SDL_SCANCODE_W] && key_states[SDL_SCANCODE_S]) {
        next_action_type = ActionType::None;
    }
    // check A,D -> Stop
    else if (key_states[SDL_SCANCODE_A] && key_states[SDL_SCANCODE_D]) {
        next_action_type = ActionType::None;
    }
    // check for both S,A -> DownLeft
    else if (key_states[SDL_SCANCODE_S] && key_states[SDL_SCANCODE_A]) {
        next_action_type = ActionType::MoveDownLeft;
    }
    // check for both S,D -> DownRight
    else if (key_states[SDL_SCANCODE_S] && key_states[SDL_SCANCODE_D]) {
        next_action_type = ActionType::MoveDownRight;
    }
    // MoveUp
    else if (key_states[SDL_SCANCODE_W]) {
        next_action_type = ActionType::MoveUp;
    }
    // MoveLeft
    else if (key_states[SDL_SCANCODE_A]) {
        next_action_type = ActionType::MoveLeft;
    }
    // MoveDown
    else if (key_states[SDL_SCANCODE_S]) {
        next_action_type = ActionType::MoveDown;
    }
    // MoveRight
    else if (key_states[SDL_SCANCODE_D]) {
        next_action_type = ActionType::MoveRight;
    }
}

void KeyboardInput::handle_input(World &world, GameObject &obj) {
    Action* action = obj.fsm->current_state->input(world, obj, next_action_type);

    // consume the action
    next_action_type = ActionType::None;
    if (action != nullptr) {
        action->perform(world, obj);
        delete action;
    }
}

Action* KeyboardInput::collect_discrete_event(SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.repeat == 0) {
        if (event->key.scancode == SDL_SCANCODE_LCTRL || event->key.scancode == SDL_SCANCODE_RCTRL) {
            next_action_type = ActionType::Sprint;
        }
        if (event->key.scancode == SDL_SCANCODE_M) {
            next_action_type = ActionType::AttackAll;
        }
        if (event->key.scancode == SDL_SCANCODE_K) {
            return new AttackDown();
        }
    }

    return nullptr;
}
