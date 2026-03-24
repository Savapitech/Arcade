#include <filesystem>
#include <iostream>

#include "Core.hpp"
#include "Graphic.hpp"
#include "Loader.hpp"

#include "Logger.hpp"

#include <memory>

namespace fs = std::filesystem;

core::Core::Core(const std::string &graphicPath) {
  std::string path = "./lib/";

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.path().extension() != ".so")
      throw std::runtime_error("Failed while loading lib");
    if (entry.path().string() == graphicPath) {
    }
    try {
      this->graphicLoader.push_back(std::make_unique<DLLoader<graphic::IGraphic>>(entry.path().string()));
      this->graphicalTab.push_back(graphicLoader.back()->getInstance("graphicEntryPoint"));
      this->graphicLibIdx = 0;
      LOG_INFO("Load graphic tab");
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

core::Core::~Core() 
{
  //this->graphicalTab.clear();
  //this->gameTab.clear();
}

void core::Core::run() {
  Event event;

  this->graphicalTab[graphicLibIdx]->openWindow(1920, 1080, "arcade", event);
  while (this->graphicalTab[graphicLibIdx]->isOpen()) {
    this->graphicalTab[graphicLibIdx]->fillEvent(event);
  }
}