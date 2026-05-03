#include "ai_input.h"

#include "fsm.h"
#include "world.h"
#include "game_object.h"
#include "random.h"

void AiInput::get_input() {

}

void AiInput::handle_input(World& world, GameObject& obj) {
    // random direction
    int probability = randint(0,10);
    if (probability < 2) {
        next_action_type = ActionType::MoveUp;
    }
    else if (probability > 2 && probability < 5) {
        next_action_type = ActionType::MoveDown;
    }
    else if (probability > 5 && probability < 7) {
        next_action_type = ActionType::MoveRight;
    }
    else if (probability >= 7 && probability <= 10) {
        next_action_type = ActionType::MoveLeft;
    }

    Action* action = obj.fsm->current_state->input(world, obj, next_action_type);

    if (action) {
        action->perform(world, obj);
        delete action;
    }
}
