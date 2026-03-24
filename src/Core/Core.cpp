#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

#include "../Game/Entity.hpp"
#include "Core.hpp"
#include "Graphic.hpp"
#include "Loader.hpp"

#include "Logger.hpp"

#include "Utils.hpp"


namespace fs = std::filesystem;

core::Core::Core(const std::string &graphicPath) : 
  graphicLibIdx(0),
  gameLibIdx(0)
  {
  std::string path = "./lib/";
  int libIdx = 0;

  for (const auto &entry : fs::directory_iterator(path)) {
     std::cout << "Lib: " << entry.path().string() << std::endl;
    if (entry.path().extension() != ".so")
      throw std::runtime_error("Failed while loading lib");

    if (entry.path().string() == graphicPath) {
      this->graphicLibIdx = libIdx;
      LOG_INFO("Graphic:" + std::to_string(this->graphicLibIdx) + "<" + entry.path().string() + ">");
    }
    libIdx++;
    try {
      this->graphicLoader.push_back(
          std::make_unique<DLLoader<graphic::IGraphic>>(entry.path().string()));
      this->graphicalTab.push_back(
          graphicLoader.back()->getInstance("graphicEntryPoint"));
      this->graphicLibIdx = 0;
      LOG_INFO("Load graphic tab");
      continue;
    } catch (const std::exception &e) {
    }
    /*
    try {
      DLLoader<game::IGame> loader(entry.path().string());
      LOG_INFO("Load game tab");
      this->gameTab.push_back(loader.getInstance("gameEntryPoint"));
    } catch (const std::exception &e) {
      throw std::runtime_error("Failed while loading lib");
    }

    //std::cout << entry.path().string() << std::endl;*/
  }
}

core::Core::~Core() {
  // this->graphicalTab.clear();
  // this->gameTab.clear();
}

void core::Core::switchGraphicalLib(Event &ev)
{
  if (utils::containsKey(ev.getKeyStack(), core::Keys::P) == false)
    return;

  this->graphicalTab[graphicLibIdx]->closeWindow();

  graphicLibIdx++;
  graphicLibIdx = graphicLibIdx % this->graphicalTab.size();

  this->graphicalTab[graphicLibIdx]->openWindow(1920, 1080, "arcade", ev);
}

void core::Core::run() {
  Event event;
  game::Entity entiti("pacman", "assets/Game/Pacman/Arena_full.png",
                      "\e[0;33m|C", core::Vec2(100, 100), core::Vec2(10, 10));
  game::Entity entitie(
      "pacmon", "assets/Game/Pacman/Arena_Empty.png",
      "\e[0;34m|"
      "########################################################|"
      "##                        ####                        ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##  ##    ##  ##      ##  ####  ##      ##  ##    ##  ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##                                                    ##|"
      "##  ########  ####  ################  ####  ########  ##|"
      "##  ########  ####  ################  ####  ########  ##|"
      "##            ####        ####        ####            ##|"
      "############  ##########  ####  ##########  ############|"
      "          ##  ##########  ####  ##########  ####        |"
      "          ##  ####                    ####  ####        |"
      "          ##  ####  ########  ######  ####  ####        |"
      "############  ####  ####          ##  ####  ############|"
      "                    ####          ##                    |"
      "############  ####  ####          ##  ####  ############|"
      "          ##  ####  ################  ####  ####        |"
      "          ##  ####                    ####  ####        |"
      "          ##  ####  ################  ####  ####        |"
      "############  ####  ################  ####  ############|"
      "##                        ####                        ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##      ####                                ####      ##|"
      "######  ####  ####  ################  ####  ####  ######|"
      "######  ####  ####  ################  ####  ####  ######|"
      "##            ####        ####        ####            ##|"
      "##  ####################  ####  ####################  ##|"
      "##  ####################  ####  ####################  ##|"
      "##                                                    ##|"
      "########################################################|",
      core::Vec2(10, 10), core::Vec2(10, 10));
  std::vector<game::Entity> entities;
  entities.push_back(entiti);
  entities.push_back(entitie);

  this->graphicalTab[graphicLibIdx]->openWindow(1920, 1080, "arcade", event);
  this->graphicalTab[graphicLibIdx]->initGraphic(entities);
  while (this->graphicalTab[graphicLibIdx]->isOpen()) {
    this->graphicalTab[graphicLibIdx]->fillEvent(event);
    this->switchGraphicalLib(event);
    this->graphicalTab[graphicLibIdx]->drawEntities(entities);
    /*-- TMP --*/
    event.clear();
    /*-- TMP --*/
  }
}
