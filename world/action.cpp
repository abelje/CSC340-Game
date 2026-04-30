#include "action.h"

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

void AttackDown::perform(World& world, GameObject& obj) {
    auto sword = dynamic_cast<Projectile*>(world.available_items["arrow"]());
    sword->physics.position = obj.physics.position;
    world.projectiles.push_back(sword);
}
