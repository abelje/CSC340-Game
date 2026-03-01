#pragma once
#include <utility>
#include "vec.h"
#include "graphics.h"
#include "physics.h"

class World;
class FSM;
class Input;

class GameObject {
public:
    GameObject(const Vec<float> &position, const Vec<int> &size, World &world, FSM* fsm, Input* input, Color color);
    ~GameObject();

    // void input(World& world);
    void update(World& world, double dt);

    std::pair<Vec<float>, Color> get_sprite() const;

    // Game Object data
    Physics physics;
    Vec<int> size;
    FSM* fsm;
    Input* input;
    Color color;
    Sprite sprite;
};