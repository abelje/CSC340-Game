#include "action.h"
#include "game_object.h"
#include "world.h"

void Jump::perform(World &world, GameObject &obj) {
    obj.physics.velocity.y = obj.physics.jump_velocity;
}
