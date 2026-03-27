#include <chrono>
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

    if (entry.path().string().find(graphicPath) != std::string::npos) {
      LOG_DEBUG("First Lib:[" + entry.path().string() + " == " + graphicPath +
                "]");
      this->_graphicLibIdx = libIdx;
    }

    try {
      this->_graphicLoader.push_back(
          std::make_unique<DLLoader<graphic::IGraphic>>(entry.path().string()));
      std::unique_ptr<graphic::IGraphic> graphical =
          _graphicLoader.back()->getInstance("graphicEntryPoint");
      if (graphical == nullptr)
        throw std::runtime_error("Failed while loading lib");
      this->_graphicalTab.push_back(std::move(graphical));
      LOG_DEBUG("Loaded lib [" + entry.path().string() + "]");
      libIdx++;
      continue;
    } catch (const std::exception &e) {
      try {
        this->_gameLoader.push_back(
            std::make_unique<DLLoader<game::IGame>>(entry.path().string()));
        this->_gameTab.push_back(
            _gameLoader.back()->getInstance("gameEntryPoint"));
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
                                    const std::vector<game::Entity> &entities) {
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

  LOG_DEBUG("Graphic idx [" + std::to_string(_graphicLibIdx) + "]");
  this->_graphicalTab[_graphicLibIdx]->openWindow(1920, 1080, "arcade", event);
  this->_gameTab[_gameLibIdx]->initGame();
  this->_graphicalTab[_graphicLibIdx]->initGraphic(
      this->_gameTab[_gameLibIdx]->getEntities());

  auto lastTime = std::chrono::steady_clock::now();
  auto timeSinceLastUpdate = std::chrono::duration<double, std::milli>::zero();
  auto timeSinceLastUpdateGraphic =
      std::chrono::duration<double, std::milli>::zero();
  const auto timePerTick =
      std::chrono::duration<double, std::milli>(TIME_PER_TICK);
  const auto timePerTickGraphic =
      std::chrono::duration<double, std::milli>(TIME_PER_TICK_GRAPHIC);

  while (this->_graphicalTab[_graphicLibIdx]->isOpen()) {
    auto currentTime = std::chrono::steady_clock::now();
    timeSinceLastUpdate += currentTime - lastTime;
    timeSinceLastUpdateGraphic += currentTime - lastTime;
    lastTime = currentTime;

    while (timeSinceLastUpdate >= timePerTick) {
      timeSinceLastUpdate -= timePerTick;

      event.clear();
      this->_graphicalTab[_graphicLibIdx]->fillEvent(event);

      this->_gameTab[_gameLibIdx]->simulateGame(event);

      /*-- TMP --*/
      this->switchGraphicalLib(event,
                               this->_gameTab[_gameLibIdx]->getEntities());
      /*-- TMP --*/
    }

    while (timeSinceLastUpdateGraphic >= timePerTickGraphic) {
      timeSinceLastUpdateGraphic -= timePerTickGraphic;
      this->_graphicalTab[_graphicLibIdx]->drawEntities(
          this->_gameTab[_gameLibIdx]->getEntities());
    }
  }
  this->_graphicalTab[_graphicLibIdx]->destroyGraphic();
  this->_graphicalTab[_graphicLibIdx]->closeWindow();
}
