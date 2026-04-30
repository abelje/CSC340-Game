#include "action.h"

#include <iostream>

#include "fsm.h"
#include "game_object.h"
#include "projectile.h"
#include "world.h"

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

void Sprint::perform(World&, GameObject& obj) {
    obj.physics.walk_acceleration *= 2.0f;
}

void ShootArrow::perform(World& world, GameObject& obj) {
    auto arrow = dynamic_cast<Projectile*>(world.available_items["arrow"]());
    arrow->physics.position = obj.physics.position;
    arrow->last_direction = obj.last_direction;
    std::cout << obj.last_direction << std::endl;
    if (obj.last_direction == "left") {
        arrow->physics.acceleration.x = arrow->physics.acceleration.x;
        arrow->physics.velocity.x = -arrow->physics.velocity.x;
    }
    if (obj.last_direction == "up") {
        arrow->physics.velocity.y = arrow->physics.velocity.x;
        arrow->physics.velocity.x = 0;
    }
    if (obj.last_direction == "down") {
        arrow->physics.velocity.y = -arrow->physics.velocity.x;
        arrow->physics.velocity.x = 0;
    }
    world.projectiles.push_back(arrow);
}
