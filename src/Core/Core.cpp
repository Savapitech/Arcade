#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

#include "Core.hpp"
#include "Game/Entity.hpp"
#include "Graphic.hpp"
#include "Loader.hpp"

#include "Logger.hpp"

#include "Utils.hpp"

namespace fs = std::filesystem;

core::Core::Core(const std::string &graphicPath)
    : graphicLibIdx(0), gameLibIdx(0) {
  std::string path = "./lib/";
  int libIdx = 0;

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.path().extension() != ".so")
      throw std::runtime_error("Failed while loading lib");

    if (entry.path().string() == graphicPath)
      this->graphicLibIdx = libIdx;
    libIdx++;
    try {
      this->graphicLoader.push_back(
          std::make_unique<DLLoader<graphic::IGraphic>>(entry.path().string()));
      this->graphicalTab.push_back(
          graphicLoader.back()->getInstance("graphicEntryPoint"));
      this->graphicLibIdx = 0;
      LOG_DEBUG("Loaded lib [" + entry.path().string() + "]");
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

void core::Core::switchGraphicalLib(Event &ev,
                                    std::vector<game::Entity> &entities) {
  if (utils::containsKey(ev.getKeyStack(), core::Keys::P) == false)
    return;

  this->graphicalTab[graphicLibIdx]->destroyGraphic();
  this->graphicalTab[graphicLibIdx]->closeWindow();

  graphicLibIdx++;
  graphicLibIdx = graphicLibIdx % this->graphicalTab.size();

  this->graphicalTab[graphicLibIdx]->openWindow(1920, 1080, "arcade", ev);
  this->graphicalTab[graphicLibIdx]->initGraphic(entities);
}

void core::Core::run() {
  Event event;
  game::Entity arena_entity(
      "arena", "assets/Game/Pacman/Arena_Empty.png",
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
      "          ##  ####  #######  #######  ####  ####        |"
      "############  ####  ###          ###  ####  ############|"
      "                    ###          ###                    |"
      "############  ####  ###          ###  ####  ############|"
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
      core::Vec2(230, 70), core::Vec2(230, 70));
  game::Entity pacman_entity("pacman", "assets/Game/Pacman/Pacman.png",
                             "\e[0;33m|C", core::Vec2(340, 200),
                             core::Vec2(340, 200));
  game::Entity redGhost_entity("pacman", "assets/Game/Pacman/RedGhost.png",
                               "\e[0;31m|A", core::Vec2(350, 190),
                               core::Vec2(350, 190));
  game::Entity blueGhost_entity("pacman", "assets/Game/Pacman/BlueGhost.png",
                                "\e[0;36m|A", core::Vec2(330, 190),
                                core::Vec2(330, 190));
  game::Entity orangeGhost_entity(
      "pacman", "assets/Game/Pacman/OrangeGhost.png", "\e[0;33m|A",
      core::Vec2(350, 170), core::Vec2(350, 170));
  game::Entity pinkGhost_entity("pacman", "assets/Game/Pacman/PinkGhost.png",
                                "\e[0;35m|A", core::Vec2(330, 170),
                                core::Vec2(330, 170));

  std::vector<game::Entity> entities;
  entities.push_back(arena_entity);
  entities.push_back(pacman_entity);
  entities.push_back(redGhost_entity);
  entities.push_back(blueGhost_entity);
  entities.push_back(orangeGhost_entity);
  entities.push_back(pinkGhost_entity);

  this->graphicalTab[graphicLibIdx]->openWindow(1920, 1080, "arcade", event);
  this->graphicalTab[graphicLibIdx]->initGraphic(entities);
  while (this->graphicalTab[graphicLibIdx]->isOpen()) {
    event.clear();
    this->graphicalTab[graphicLibIdx]->fillEvent(event);
    this->graphicalTab[graphicLibIdx]->drawEntities(entities);
    /*-- TMP --*/
    this->switchGraphicalLib(event, entities);
    /*-- TMP --*/
  }
}
