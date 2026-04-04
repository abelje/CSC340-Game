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
void edit_tile(std::string json_filename, int row, int col, std::string choice, std::string change);
void remove_tile(std::string json_filename, int row, int col);

int main(int argc, char* argv[]) {
  // ordered_json tileset_json = generate_tileset_json("Overworld_Tileset.png", 288, 208, 16, 4);
  // output_json(tileset_json, "output.json");
  // edit_tile("output.json", 0, 0, "name", "Hello World!");
  // remove_tile("output.json", 0, 0);
}

void parse_args(int argc, char* argv[]) {
  if (argc >= 2) {
    std::string cmd = argv[1];

    // variables
    std::string filename = "output.json";

    std::string img_filename = "";
    int img_width = -1, img_height = -1, tilesize = -1, scale = -1;
    bool blocking = false;

    for (int i = 2; i < argc; ++i) {
      std::string arg = argv[i];
      if (arg == "-o" && i + 1 < argc) {
        // Select output file
        filename = argv[i + 1];
      }
      if (cmd == "-g") {
        if (argv[i] == "--filename" && i + 1 < argc) {
          img_filename = argv[i + 1];
        }
        if (argv[i] == "--width" && i+1 < argc) {
          img_width = std::stoi(argv[i+1]);
          std::cout << img_width << std::endl;
        }
        if (argv[i] == "--height" && i+1 < argc) {
          img_height = std::stoi(argv[i+1]);
        }
        if (argv[i] == "--tilesize" && i+1 < argc) {
          tilesize = std::stoi(argv[i+1]);
        }
        if (argv[i] == "--scale" && i+1 < argc) {
          scale = std::stoi(argv[i+1]);
        }
        if (argv[i] == "--blocking" && i+1 < argc) {
          if (argv[i+1] == "true") {
            blocking = true;
          }
        }
      }
    }
    if (cmd == "-g") {
      ordered_json tileset = generate_tileset_json(img_filename, img_width, img_height, tilesize, scale, blocking);
      output_json(tileset, filename);
    }
    // if (argv[1] == "-g") {
    //   // generate tileset
    //   // look for filename, img_width, img_height, tilesize, scale, OPTIONAL: blocking
    // }
    // if (argv[1] == "-e") {
    //   // edit tile
    //   // look for json_filename, row, col, choice, change
    // }
    // if (argv[1] == "-r") {
    //   // remove tile
    //   // look for json_filename, row, col
    // }
  }
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

void edit_tile(std::string json_filename, int row, int col, std::string choice, std::string change) {
  std::ifstream file{json_filename};
  ordered_json j = ordered_json::parse(file);
  ordered_json* tile = find_tile_by_location(j["tiles"], row, col);
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

void remove_tile(std::string json_filename, int row, int col) {
  std::ifstream file{json_filename};
  ordered_json j = ordered_json::parse(file);
  ordered_json* tile = find_tile_by_location(j["tiles"], row, col);
  if (!tile) {
    throw std::runtime_error("Could not find tile");
  }
  tile->clear();
  output_json(j, json_filename);
}