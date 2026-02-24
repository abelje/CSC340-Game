#include "states.h"
#include "action.h"
#include "game_object.h"
#include "world.h"

// Helper Function
bool on_platform(World& world, GameObject& obj) {
    constexpr float epsilon = 1e-4;
    Vec<float> left_foot{obj.physics.position.x + epsilon, obj.physics.position.y - epsilon};
    Vec<float> right_foot{obj.physics.position.x + obj.size.x - epsilon, obj.physics.position.y - epsilon};
    return world.collides(left_foot) || world.collides(right_foot);
}

/////////////////
/// Standing ///
////////////////

void Standing::on_enter(World&, GameObject& obj) {
    obj.color = {255, 0, 0, 255};

    // Stop acceleration so damping will stop you
    obj.physics.acceleration.x = 0;
    obj.physics.acceleration.y = 0;
    obj.physics.walk_acceleration = 30.0f;
}

Action *Standing::input(World& world, GameObject& obj, ActionType action_type) {
    if (action_type == ActionType::Jump) {
        obj.fsm->transition(Transition::Jump, world, obj);
        return new Jump();
    }
    if (action_type == ActionType::Sprint) {
        obj.fsm->transition(Transition::Sprint, world, obj);
        return new Sprint();
    }
    if (action_type == ActionType::MoveRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveRight();
    }
    if (action_type == ActionType::MoveLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveLeft();
    }
    if (action_type == ActionType::MoveUp) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveUp();
    }
    if (action_type == ActionType::MoveDown) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveDown();
    }

    return nullptr;
}

/////////////////
/// Running ////
////////////////

void Running::on_enter(World&, GameObject& obj) {
    obj.color = Color{255, 255, 0, 255};
}

Action* Running::input(World& world, GameObject& obj, ActionType action_type) {
    if (action_type == ActionType::None) {
        obj.fsm->transition(Transition::Stop, world, obj);
    }
    if (action_type == ActionType::Sprint) {
        obj.fsm->transition(Transition::Sprint, world, obj);
        return new Sprint();
    }
    // Be able to run different directions while running?
    if (action_type == ActionType::MoveUpRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveUpRight();
    }
    if (action_type == ActionType::MoveUpLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveUpLeft();
    }
    if (action_type == ActionType::MoveDownLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveDownLeft();
    }
    if (action_type == ActionType::MoveDownRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveDownRight();
    }
    if (action_type == ActionType::Jump) {
        obj.fsm->transition(Transition::Jump, world, obj);
        return new Jump();
    }
    return nullptr;
}

/////////////////
// Sprinting ///
////////////////

void Sprinting::on_enter(World&, GameObject& obj) {
    obj.color = {128, 0, 128, 255};
}

Action *Sprinting::input(World& world, GameObject& obj, ActionType action_type) {
    if (action_type == ActionType::None) {
        obj.fsm->transition(Transition::Stop, world, obj);
    }
    // if (action_type == ActionType::Decelerate) {
    //     obj.fsm->transition(Transition::Decelerate, world, obj);
    //     obj.color = Color{0, 0, 0, 255};
    //     return new Decelerate();
    // }

    if (action_type == ActionType::MoveUpRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveUpRight();
    }
    if (action_type == ActionType::MoveUpLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveUpLeft();
    }
    if (action_type == ActionType::MoveDownLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveDownLeft();
    }
    if (action_type == ActionType::MoveDownRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveDownRight();
    }

    if (action_type == ActionType::MoveRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveRight();
    }
    if (action_type == ActionType::MoveLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveLeft();
    }
    if (action_type == ActionType::MoveUp) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveUp();
    }
    if (action_type == ActionType::MoveDown) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveDown();
    }

    return nullptr;
}