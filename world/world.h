#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include "tilemap.h"
#include "vec.h"
#include "game_object.h"

class Player;

class World {
public:
    World(int width, int height);

    void add_platform(float x, float y, float width, float height);
    bool collides(const Vec<float>& position) const;
    GameObject* create_player(World& world);
    void update(float dt);
    void move_to(Vec<float>& position, const Vec<int>& size, Vec<float>& velocity);

    Tilemap tilemap;

private:
    std::unique_ptr<GameObject> player;
};