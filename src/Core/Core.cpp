#include <filesystem>
#include <iostream>

#include "Core.hpp"
#include "Graphic.hpp"
#include "Loader.hpp"

#include "Logger.hpp"

namespace fs = std::filesystem;

core::Core::Core(const std::string &graphicPath) {
  std::string path = "./lib/";

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.path().string() == graphicPath) {
      std::cout << "true" << std::endl;
    }
    try {
      auto loader = std::make_shared<DLLoader<graphic::IGraphic>>(entry.path().string());
      this->graphicalTab.push_back(loader->getInstance("graphicEntryPoint"));
      this->_graphLoadersTab.push_back(loader);
      LOG_INFO("Load graphic tab");
      this->graphicLibIdx = 0;
      continue;
    } catch (const std::exception &e) {
    }
    //try {
    //  DLLoader<game::IGame> loader(entry.path().string());
    //  LOG_INFO("Load game tab");
    //  this->gameTab.push_back(loader.getInstance("gameEntryPoint"));
    //} catch (const std::exception &e) {
    //  throw std::runtime_error("Failed while loading lib");
    //}

    std::cout << entry.path().string() << std::endl;
  }
}

void core::Core::run() {
  Event event;

  this->graphicalTab[0]->openWindow(1920, 1080, "arcade", event);
  while (this->graphicalTab[0]->isOpen()) {
    this->graphicalTab[0]->fillEvent(event);
  }
}
