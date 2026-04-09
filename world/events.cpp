#include "events.h"

#include "world.h"
#include "game_object.h"
#include <iostream>

void NextLevel::perform(World &world, GameObject &obj) {
    std::cout << "Next Level!!\n";
    if (&obj != world.player) return;
    world.end_level = true;
}
