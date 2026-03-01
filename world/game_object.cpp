#include "game_object.h"

#include <iostream>

#include "physics.h"
#include "world.h"
#include "graphics.h"
#include "action.h"
#include "fsm.h"
#include "input.h"

GameObject::GameObject(const Vec<float> &position, const Vec<int> &size, World &world, FSM* fsm, Input* input, Color color)
    : physics{position, {0,0}, {0, 0}}, size{size}, fsm{fsm}, input{input}, color{color} {
    fsm->current_state->on_enter(world, *this);
}

GameObject::~GameObject() {
    delete fsm;
    delete input;
}

void GameObject::update(World &world, double dt) {

}

std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {physics.position,color};
}
