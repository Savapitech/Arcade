#include <filesystem>
#include <iostream>

#include "Core.hpp"
#include "Graphic.hpp"
#include "Loader.hpp"

namespace fs = std::filesystem;

core::Core::Core(const std::string &graphicPath) {
  std::string path = "./lib/";

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.path().string() == graphicPath) {
      std::cout << "true" << std::endl;
    }
    try {
      DLLoader<graphic::IGraphic> loader(entry.path().string());
      this->graphicalTab.push_back(loader.getInstance("graphicalEntryPoint"));
    } catch (const std::exception &e) {
    }
    try {
      DLLoader<game::IGame> loader(entry.path().string());
      this->gameTab.push_back(loader.getInstance("gameEntryPoint"));
    } catch (const std::exception &e) {
      throw std::runtime_error("Failed while loading lib");
    }

    std::cout << entry.path().string() << std::endl;
  }
}

void core::Core::run() {
  Event event;

  // while (this->graphicalTab[this->graphicLibIdx]->) {
  //   /* code */
  // }
}