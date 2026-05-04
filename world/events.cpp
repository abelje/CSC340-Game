#include "events.h"

#include "world.h"
#include "game_object.h"
#include <iostream>

void NextLevel::perform(World &world, GameObject &obj) {
    if (&obj != world.player) return;
    world.end_level = true;
}

void LockedLevel::perform(World& world, GameObject& obj) {
    if (&obj != world.player) return;
    bool has_enemy = false;
    for (GameObject* object : world.game_objects) {
        if (object->obj_name == "spider" || object->obj_name == "pinkslime") {
            has_enemy = true;
        }
    }
    if (!has_enemy) {
        world.end_level = true;
    }
}
