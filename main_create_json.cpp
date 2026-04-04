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

ordered_json generate_tileset_json(std::string filename, int img_width, int img_height, int tilesize, int scale);
void output_json(ordered_json j, std::string filename);

int main() {
  // ordered_json j = {
  //   {"tiles", ordered_json::array({
  //       {
  //           {"sprite", {
  //               {"name", "border"},
  //               {"filename", "Overworld_Tileset.png"},
  //               {"location", {235, 128}},
  //               {"size", {16, 16}},
  //               {"scale", 4},
  //               {"number_of_frames", 1},
  //               {"dt_per_frame", -1}
  //           }},
  //           {"blocking", true},
  //           {"event_name", ""}
  //       }
  //   })}
  // };

  // std::ofstream file{"output.json"};
  //
  // file << std::setw(4) << j << std::endl;

  ordered_json tileset_json = generate_tileset_json("Overworld_Tileset.png", 288, 208, 16, 4);
  output_json(tileset_json, "output.json");
}

ordered_json generate_tileset_json(std::string filename, int img_width, int img_height, int tilesize, int scale) {
  ordered_json j = {
    {"tiles", ordered_json::array()}
  };
  int i = 0;
  std::string name = filename.substr(0, filename.length() - 4);
  for (int width = 0; width < img_width; width += tilesize) {
    for (int height = 0; height < img_height; height += tilesize) {
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
      }};
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