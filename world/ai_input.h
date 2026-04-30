#pragma once

#include "world.h"
#include "game_object.h"
#include "input.h"

class AiInput : public Input {
public:
    void get_input() override;
    void handle_input(World& world, GameObject& obj) override;
};
