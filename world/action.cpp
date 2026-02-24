#include "action.h"

#include "game_object.h"
#include "world.h"

void Jump::perform(World&, GameObject& obj) {
    obj.physics.velocity.y = obj.physics.jump_velocity;
}

void MoveRight::perform(World&, GameObject& obj) {
    obj.physics.acceleration.x = obj.physics.walk_acceleration;
}

void MoveLeft::perform(World&, GameObject& obj) {
    obj.physics.acceleration.x = -obj.physics.walk_acceleration;
}

void MoveUp::perform(World&, GameObject& obj) {
    obj.physics.acceleration.y = obj.physics.walk_acceleration;
}

void MoveDown::perform(World&, GameObject& obj) {
    obj.physics.acceleration.y = -obj.physics.walk_acceleration;
}

void MoveUpLeft::perform(World&, GameObject& obj) {
    obj.physics.acceleration.y = obj.physics.walk_acceleration;
    obj.physics.acceleration.x = -obj.physics.walk_acceleration;
}

void MoveUpRight::perform(World&, GameObject& obj) {
    obj.physics.acceleration.y = obj.physics.walk_acceleration;
    obj.physics.acceleration.x = obj.physics.walk_acceleration;
}

void MoveDownLeft::perform(World&, GameObject& obj) {
    obj.physics.acceleration.y = -obj.physics.walk_acceleration;
    obj.physics.acceleration.x = -obj.physics.walk_acceleration;
}

void MoveDownRight::perform(World&, GameObject& obj) {
    obj.physics.acceleration.y = -obj.physics.walk_acceleration;
    obj.physics.acceleration.x = obj.physics.walk_acceleration;
}