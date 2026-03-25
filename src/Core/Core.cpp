#include <filesystem>
#include <memory>

#include "Core.hpp"
#include "Game/Entity.hpp"
#include "Graphic/Graphic.hpp"

#include "Logger/Logger.hpp"

#include "Utils.hpp"

namespace fs = std::filesystem;

core::Core::Core(const std::string &graphicPath)
    : _graphicLibIdx(0), _gameLibIdx(0) {
  std::string path = "./lib/";
  int libIdx = 0;

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.path().extension() != ".so")
      throw std::runtime_error("Failed while loading lib");

    if (entry.path().string() == graphicPath)
      this->_graphicLibIdx = libIdx;
    libIdx++;
    try {
      this->_graphicLoader.push_back(
          std::make_unique<DLLoader<graphic::IGraphic>>(entry.path().string()));
      std::unique_ptr<graphic::IGraphic> graphical = _graphicLoader.back()->getInstance("graphicEntryPoint");
      if (graphical == nullptr)
        throw std::runtime_error("Failed while loading lib");
      this->_graphicalTab.push_back(std::move(graphical));
      this->_graphicLibIdx = 0;
      LOG_DEBUG("Loaded lib [" + entry.path().string() + "]");
      continue;
    } catch (const std::exception &e) {
    try {
      this->_gameLoader.push_back(std::make_unique<DLLoader<game::IGame>>(entry.path().string()));
      this->_gameTab.push_back(_gameLoader.back()->getInstance("gameEntryPoint"));
      this->_graphicLibIdx = 0;
      LOG_DEBUG("Loaded lib [" + entry.path().string() + "]");
    } catch (const std::exception &e) {
      throw std::runtime_error("Failed while loading lib");
      }
    }
  }
}

core::Core::~Core() {
  // this->_graphicalTab.clear();
  // this->gameTab.clear();
}

void core::Core::switchGraphicalLib(Event &ev,
                                    std::vector<game::Entity> &entities) {
  if (utils::containsKey(ev.getKeyStack(), core::Keys::P) == false)
    return;

  this->_graphicalTab[_graphicLibIdx]->destroyGraphic();
  this->_graphicalTab[_graphicLibIdx]->closeWindow();

  _graphicLibIdx++;
  _graphicLibIdx = _graphicLibIdx % this->_graphicalTab.size();

  this->_graphicalTab[_graphicLibIdx]->openWindow(1920, 1080, "arcade", ev);
  this->_graphicalTab[_graphicLibIdx]->initGraphic(entities);
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

  this->_graphicalTab[_graphicLibIdx]->openWindow(1920, 1080, "arcade", event);
  this->_graphicalTab[_graphicLibIdx]->initGraphic(entities);
  while (this->_graphicalTab[_graphicLibIdx]->isOpen()) {
    event.clear();
    this->_graphicalTab[_graphicLibIdx]->fillEvent(event);
    this->_graphicalTab[_graphicLibIdx]->drawEntities(entities);
    /*-- TMP --*/
    this->switchGraphicalLib(event, entities);
    /*-- TMP --*/
  }
}
