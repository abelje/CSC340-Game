#pragma once
#include <string>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <unordered_map>
#include <vector>
#include "sprite.h"
#include "vec.h"

class Color {
public:
    int red{255}, green{0}, blue{0}, alpha{255};
};

class Graphics {
public:
    Graphics(const std::string& title, int window_width, int window_height);
    void clear();
    void update();

    void draw(const SDL_FRect& rect, const Color& color, bool filled=true);
    void draw_sprite(const Vec<float>& pixel, const Sprite& sprite);

    int get_texture_id(const std::string& image_filename);

    int width, height;

private:
    std::string title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;
    std::unordered_map<std::string, int> texture_ids;
};
