// Take in length and width of image, and size of Tile
// Iterate through and generate json for tileset.json

// Format:
/*
{
  "tiles": [
    {
        "sprite": {
          "name": "border",
          "filename": "Overworld_Tileset.png",
          "location": [
            235,
            128
          ],
          "size": [
            16,
            16
          ],
          "scale": 4,
          "number_of_frames": 1,
          "dt_per_frame": -1
        },
        "blocking": true,
        "event_name": ""
    }
  ]
}
 */

#include "json.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <tuple>
using nlohmann::ordered_json;

void parse_args(int argc, char* argv[]);
ordered_json generate_tileset_json(std::string filename, int img_width, int img_height, int tilesize, int scale, bool blocking=false);
void output_json(ordered_json j, std::string filename);
ordered_json* find_tile_by_location(ordered_json& tiles, int row, int col);
void edit_tile(std::string json_filename, int row, int col, int tilesize, std::string choice, std::string change);
void remove_tile(std::string json_filename, int row, int col, int tilesize);

// enemy json
ordered_json generate_enemy_json(std::string filename, std::vector<std::string> names, std::unordered_map<std::string, std::tuple<int, int>> locations, int tilesize, int scale, int number_of_frames, double dt_per_frame);

int main() {
  std::cout << "Choose what command to use: \n'g'-> generate tileset json \n'e'-> edit tileset json\n'r'-> remove tile from tileset\n";
  std::string cmd;
  std::cin >> cmd;
  if (cmd == "g") {
    std::string filename, img_filename;
    int img_width, img_height, tilesize, scale;
    std::cout << "Enter values: output_filename img_filename img_width img_height tilesize scale\n";
    std::cin >> filename >> img_filename >> img_width >> img_height >> tilesize >> scale;
    ordered_json tileset_json = generate_tileset_json(img_filename, img_width, img_height, tilesize, scale);
    output_json(tileset_json, filename);
  }
  if (cmd == "e") {
    std::string json_filename;
    int row, col, tilesize;
    std::string choice, change;
    std::cout << "Enter values: json_filename row col tilesize choice change\n";
    std::cin >> json_filename >> row >> col >> tilesize >> choice >> change;
    edit_tile(json_filename, row, col, tilesize, choice, change);
  }
  if (cmd == "r") {
    std::string json_filename;
    int row, col, tilesize;
    std::cout << "Enter values: json_filename row col tilesize\n";
    std::cin >> json_filename >> row >> col >> tilesize;
    remove_tile(json_filename, row, col, tilesize);
  }
  if (cmd == "enemy") {
    std::string filename = "spider_spritesheet.png";
    int tilesize = 16, scale = 4, number_of_frames = 4;
    double dt_per_frame = 0.1;
    std::vector<std::string> names = {"idle", "walking", "death"};
    std::unordered_map<std::string, std::tuple<int, int>> locations;
    locations["idle"] = {0, 64};
    locations["walking"] = {0, 32};
    locations["death"] = {0, 0};

    auto enemy_json = generate_enemy_json(filename, names, locations, tilesize, scale, number_of_frames, dt_per_frame);
    output_json(enemy_json, "output.json");
  }
  // ordered_json tileset_json = generate_tileset_json("Overworld_Tileset.png", 288, 208, 16, 4);
  // output_json(tileset_json, "output.json");
  // edit_tile("output.json", 0, 0, "name", "Hello World!");
  // remove_tile("output.json", 0, 0);
}

ordered_json generate_tileset_json(std::string filename, int img_width, int img_height, int tilesize, int scale, bool blocking) {
  // Create json, adding tiles and an empty array
  ordered_json j = {
    {"tiles", ordered_json::array()}
  };
  int i = 0;
  // Remove file extension for name loop
  std::string name = filename.substr(0, filename.length() - 4);
  for (int width = 0; width < img_width; width += tilesize) {
    for (int height = 0; height < img_height; height += tilesize) {
      // Add sprite
      j["tiles"] += {{"sprite",
        {
          {"name", name + "_" + std::to_string(i)},
          {"filename", filename},
          {"location", {width, height}},
          {"size", {tilesize, tilesize}},
          {"scale", scale},
          {"number_of_frames", 1},
          {"dt_per_frame", -1}
        }
      },
      {"blocking", blocking},
      {"event_name", ""}
      };
      ++i;
    }
  }
  std::cout << i << " tiles generated!\n";
  return j;
}

void output_json(ordered_json j, std::string filename) {
  std::ofstream file{filename};
  file << std::setw(4) << j << std::endl;
}

ordered_json* find_tile_by_location(ordered_json& tiles, int row, int col) {
  for (auto& tile : tiles) {
    auto& location = tile["sprite"]["location"];
    if (location[0] == row && location[1] == col) {
      return &tile;
    }
  }
  return nullptr;
}

void edit_tile(std::string json_filename, int row, int col, int tilesize, std::string choice, std::string change) {
  std::ifstream file{json_filename};
  ordered_json j = ordered_json::parse(file);
  ordered_json* tile = find_tile_by_location(j["tiles"], (col-1) * tilesize, (row-1) * tilesize);
  if (!tile) {
    throw std::runtime_error("Could not find tile");
  }

  if (choice == "name") {
    (*tile)["sprite"]["name"] = change;
  }
  if (choice == "filename") {
    (*tile)["sprite"]["filename"] = change;
  }
  if (choice == "size") {
    (*tile)["sprite"]["size"][0]= std::stoi(change);
    (*tile)["sprite"]["size"][1]= std::stoi(change);
  }
  if (choice == "number_of_frames") {
    (*tile)["sprite"]["number_of_frames"] = std::stoi(change);
  }
  if (choice == "dt_per_frame") {
    (*tile)["sprite"]["dt_per_frame"] = std::stoi(change);
  }
  if (choice == "blocking") {
    if (change == "true") {
      (*tile)["sprite"]["blocking"] = true;
    }
    if (change == "false") {
      (*tile)["blocking"] = false;
    }
  }
  if (choice == "event_name") {
    (*tile)["event_name"] = change;
  }

  output_json(j, json_filename);
}

void remove_tile(std::string json_filename, int row, int col, int tilesize) {
  std::ifstream file{json_filename};
  ordered_json j = ordered_json::parse(file);
  ordered_json* tile = find_tile_by_location(j["tiles"], (col-1) * tilesize, (row-1) * tilesize);
  if (!tile) {
    throw std::runtime_error("Could not find tile");
  }
  tile->clear();
  output_json(j, json_filename);
}

ordered_json generate_enemy_json(std::string filename, std::vector<std::string> names, std::unordered_map<std::string, std::tuple<int, int>> locations, int tilesize, int scale, int number_of_frames, double dt_per_frame) {
  // Create json, adding tiles and an empty array
  ordered_json j = {
    {"sprites", ordered_json::array()},
    {"physics",
      {
          {"velocity", ordered_json::array({0, 0})},
          {"acceleration", ordered_json::array({0, 0})},
          {"gravity", 0.0},
          {"damping", 0.9},
          {"walk_acceleration", 60.0},
          {"jump_velocity", 0.0},
          {"terminal_velocity", 0.0}
        }
      },
    {"size", ordered_json::array({1, 1})},
    {"health", 10},
    {"max_health", 10},
    {"damage", 0}
  };
  int i = 0;
  for (int k = 0; k < names.size(); ++k) {
    // Add sprite
    std::string name = names.at(k);
    auto& [row, col] = locations[name];
    j["sprites"] += {{"sprite",
      {
            {"name", name},
            {"filename", filename},
            {"location", {row, col}},
            {"size", {tilesize, tilesize}},
            {"scale", scale},
            {"number_of_frames", number_of_frames},
            {"dt_per_frame", dt_per_frame}
      }
    }};
    ++i;
  }
  std::cout << i << " sprite animations generated!\n";
  return j;
}