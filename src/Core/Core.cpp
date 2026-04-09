#include <chrono>
#include <filesystem>
#include <memory>

#include "Core.hpp"
#include "Database.hpp"
#include "Exceptions.hpp"
#include "Game/Entity.hpp"
#include "Graphic/Graphic.hpp"

#include "Logger/Logger.hpp"

#include "Utils.hpp"

namespace fs = std::filesystem;

core::Core::Core(const std::string &graphicPath)
    : _graphicLibIdx(0), _gameLibIdx(0), _menu(nullptr) {
  std::string path = "./lib/";
  int libIdx = 0;

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.path().extension() != ".so")
      continue;

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
        throw LoadException("Failed while loading lib");
      this->_graphicalTab.push_back(std::move(graphical));
      this->_graphicNames.push_back(entry.path().filename().string());
      LOG_DEBUG("Loaded lib [" + entry.path().string() + "]");
      libIdx++;
      continue;
    } catch (const std::exception &e) {
      try {
        this->_gameLoader.push_back(
            std::make_unique<DLLoader<game::IGame>>(entry.path().string()));
        this->_gameTab.push_back(
            _gameLoader.back()->getInstance("gameEntryPoint"));
        this->_gameNames.push_back(entry.path().filename().string());
        LOG_DEBUG("Loaded lib [" + entry.path().string() + "]");
      } catch (const std::exception &e) {
        throw LoadException("Failed while loading lib: " +
                            std::string(e.what()));
      }
    }
  }
  if (this->_gameTab.size() < 1 || this->_graphicalTab.size() < 1)
    throw LibraryNotFoundException("No game or graphical lib");

  for (size_t i = 0; i < _gameTab.size(); i++)
    if (_gameNames[i].find("arcade_menu.so") != std::string::npos)
      _menu = dynamic_cast<game::IMenu *>(_gameTab[i].get());

  _database = std::make_shared<Database>();
  if (auto db = std::dynamic_pointer_cast<Database>(_database))
    db->load("arcade.db");
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

void core::Core::switchGameLib(Event &ev,
                               const std::vector<game::Entity> &entities) {
  if (utils::containsKey(ev.getKeyStack(), core::Keys::N) == false)
    return;

  do {
    _gameLibIdx = (_gameLibIdx + 1) % this->_gameTab.size();
  } while (_gameNames[_gameLibIdx].find("arcade_menu.so") != std::string::npos);

  auto menuGame = dynamic_cast<game::IGame *>(_menu);
  _gameTab[_gameLibIdx]->setUserName(menuGame ? menuGame->getUserName()
                                              : "Player");
  _gameTab[_gameLibIdx]->initGame(_database);
  this->_graphicalTab[_graphicLibIdx]->initGraphic(
      this->_gameTab[_gameLibIdx]->getEntities());
}

void core::Core::run() {
  Event event;
  this->_state = State::MENU;
  if (!_menu) {
    throw GameNotFoundException(
        "No menu library found (missing arcade_menu.so)");
  }

  std::vector<std::string> validGameNames;
  for (const auto &name : this->_gameNames) {
    if (name.find("arcade_menu.so") == std::string::npos) {
      validGameNames.push_back(name);
    }
  }

  this->_menu->setGraphicNames(this->_graphicNames);
  this->_menu->setGameNames(validGameNames);
  this->_menu->setGraphicIdx(this->_graphicLibIdx);
  this->_menu->setGameIdx(0);

  auto menuGame = dynamic_cast<game::IGame *>(this->_menu);
  if (menuGame)
    menuGame->initGame(_database);

  LOG_DEBUG("Graphic idx [" + std::to_string(_graphicLibIdx) + "]");
  this->_graphicalTab[_graphicLibIdx]->openWindow(1920, 1080, "arcade", event);

  _gameLibIdx = 0;
  while (_gameLibIdx < (int)_gameNames.size() &&
         _gameNames[_gameLibIdx].find("arcade_menu.so") != std::string::npos) {
    _gameLibIdx++;
  }
  if (_gameLibIdx >= (int)_gameNames.size())
    _gameLibIdx = 0;

  this->_gameTab[_gameLibIdx]->setUserName(menuGame ? menuGame->getUserName()
                                                    : "Player");
  this->_gameTab[_gameLibIdx]->initGame(_database);
  this->_graphicalTab[_graphicLibIdx]->initGraphic(
      menuGame ? menuGame->getEntities()
               : this->_gameTab[_gameLibIdx]->getEntities());

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

      std::vector<core::Keys> keysToProcess;
      while (!event.getKeyStack().empty()) {
        keysToProcess.push_back(event.getKeyStack().top());
        event.getKeyStack().pop();
      }

      for (auto it = keysToProcess.rbegin(); it != keysToProcess.rend(); ++it) {
        core::Keys k = *it;
        if (k == core::Keys::E) {
          event.setCloseState(false);
        } else if (k == core::Keys::M) {
          _state = (_state == State::GAME) ? State::MENU : State::GAME;
          if (_state == State::GAME) {
            _gameTab[_gameLibIdx]->setUserName(
                menuGame ? menuGame->getUserName() : "Player");
            _gameTab[_gameLibIdx]->initGame(_database);
          }
          this->_graphicalTab[_graphicLibIdx]->initGraphic(
              _state == State::MENU ? menuGame->getEntities()
                                    : _gameTab[_gameLibIdx]->getEntities());
        } else if (k == core::Keys::R) {
          _gameTab[_gameLibIdx]->setUserName(menuGame ? menuGame->getUserName()
                                                      : "Player");
          _gameTab[_gameLibIdx]->initGame(_database);
          if (_state == State::GAME)
            this->_graphicalTab[_graphicLibIdx]->initGraphic(
                _gameTab[_gameLibIdx]->getEntities());
        } else if (k == core::Keys::Enter && _state == State::MENU) {
          _state = State::GAME;
          std::string selGame = _menu->getSelectedGame();
          std::string selGraphic = _menu->getSelectedGraphic();

          for (size_t i = 0; i < _gameNames.size(); i++)
            if (_gameNames[i] == selGame)
              _gameLibIdx = i;

          int newIdx = _graphicLibIdx;
          for (size_t i = 0; i < _graphicNames.size(); i++)
            if (_graphicNames[i] == selGraphic)
              newIdx = i;

          if (newIdx != _graphicLibIdx) {
            this->_graphicalTab[_graphicLibIdx]->destroyGraphic();
            this->_graphicalTab[_graphicLibIdx]->closeWindow();
            _graphicLibIdx = newIdx;
            this->_graphicalTab[_graphicLibIdx]->openWindow(1920, 1080,
                                                            "arcade", event);
          }

          this->_gameTab[_gameLibIdx]->setUserName(
              menuGame ? menuGame->getUserName() : "Player");
          this->_gameTab[_gameLibIdx]->initGame(_database);
          this->_graphicalTab[_graphicLibIdx]->initGraphic(
              this->_gameTab[_gameLibIdx]->getEntities());
        } else {
          event.addKey(k);
        }
      }

      if (_state == State::MENU)
        menuGame->simulateGame(event);
      else
        this->_gameTab[_gameLibIdx]->simulateGame(event);

      this->switchGameLib(event, _state == State::MENU
                                     ? menuGame->getEntities()
                                     : _gameTab[_gameLibIdx]->getEntities());
      this->switchGraphicalLib(
          event, _state == State::MENU ? menuGame->getEntities()
                                       : _gameTab[_gameLibIdx]->getEntities());
    }

    while (timeSinceLastUpdateGraphic >= timePerTickGraphic) {
      timeSinceLastUpdateGraphic -= timePerTickGraphic;

      if (_state == State::MENU) {
        this->_graphicalTab[_graphicLibIdx]->drawEntities(
            menuGame->getEntities(), menuGame->getTexts());
      } else {
        this->_graphicalTab[_graphicLibIdx]->drawEntities(
            _gameTab[_gameLibIdx]->getEntities(),
            _gameTab[_gameLibIdx]->getTexts());
      }
    }
  }
  this->_graphicalTab[_graphicLibIdx]->destroyGraphic();
  this->_graphicalTab[_graphicLibIdx]->closeWindow();

  if (auto db = std::dynamic_pointer_cast<Database>(_database))
    db->save("arcade.db");
}
