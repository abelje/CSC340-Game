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
    obj.set_sprite("idle_" + obj.last_direction);
    // Stop acceleration so damping will stop you
    obj.physics.acceleration.x = 0;
    obj.physics.acceleration.y = 0;
    obj.physics.walk_acceleration = 30.0f;
}

Action *Standing::input(World& world, GameObject& obj, ActionType action_type) {
    if (action_type == ActionType::Sprint) {
        obj.fsm->transition(Transition::Sprint, world, obj);
        return new Sprint();
    }
    if (action_type == ActionType::MoveRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "right";
        obj.set_sprite("walk_right");
        return new MoveRight();
    }
    if (action_type == ActionType::MoveLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "left";
        obj.set_sprite("walk_right");
        return new MoveLeft();
    }
    if (action_type == ActionType::MoveUp) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "up";
        obj.set_sprite("walk_up");
        return new MoveUp();
    }
    if (action_type == ActionType::MoveDown) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "down";
        obj.set_sprite("walk_down");
        return new MoveDown();
    }
    if (action_type == ActionType::AttackAll) {
        obj.fsm->transition(Transition::AttackAll, world, obj);
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
        obj.set_sprite("idle_" + obj.last_direction);
        obj.fsm->transition(Transition::Stop, world, obj);
    }
    if (action_type == ActionType::Sprint) {
        obj.fsm->transition(Transition::Sprint, world, obj);
        return new Sprint();
    }

    // Diagonal Directions
    if (action_type == ActionType::MoveUpRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "right";
        obj.set_sprite("walk_right");
        return new MoveUpRight();
    }
    if (action_type == ActionType::MoveUpLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "left";
        obj.set_sprite("walk_right");
        return new MoveUpLeft();
    }
    if (action_type == ActionType::MoveDownLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "left";
        obj.set_sprite("walk_right");
        return new MoveDownLeft();
    }
    if (action_type == ActionType::MoveDownRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "right";
        obj.set_sprite("walk_right");
        return new MoveDownRight();
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
    // Stop (by moving opposite directions at the same time)
    if (action_type == ActionType::None) {
        obj.fsm->transition(Transition::Stop, world, obj);
    }

    // Move Diagonal Directions while Sprinting
    if (action_type == ActionType::MoveUpRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "right";
        return new MoveUpRight();
    }
    if (action_type == ActionType::MoveUpLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "left";
        return new MoveUpLeft();
    }
    if (action_type == ActionType::MoveDownLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "left";
        return new MoveDownLeft();
    }
    if (action_type == ActionType::MoveDownRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "right";
        return new MoveDownRight();
    }

    // Allow directional actions to sprint in each direction
    if (action_type == ActionType::MoveRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "right";
        return new MoveRight();
    }
    if (action_type == ActionType::MoveLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "left";
        return new MoveLeft();
    }
    if (action_type == ActionType::MoveUp) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "up";
        return new MoveUp();
    }
    if (action_type == ActionType::MoveDown) {
        obj.fsm->transition(Transition::Move, world, obj);
        obj.last_direction = "down";
        return new MoveDown();
    }

    return nullptr;
}
/////////////////
// Attack all //
////////////////
void AttackAllEnemies::on_enter(World & world, GameObject & obj) {
    obj.color = {255, 100, 0, 255};
    for (auto& enemy : world.game_objects) {
        enemy->take_damage(obj.damage);
    }
    elapsed = 0;
}

void AttackAllEnemies::update(World & world, GameObject & obj, double dt) {
    elapsed += dt;
    if (elapsed >= cooldown) {
        obj.fsm->transition(Transition::Stop, world, obj);
    }
}