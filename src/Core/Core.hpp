#pragma once

#include <memory>
#include <vector>

#include "Core/Database.hpp"
#include "Game/Entity.hpp"
#include "Game/Game.hpp"
#include "Graphic/Graphic.hpp"
#include "Loader.hpp"
#include "Menu.hpp"

#define TIME_PER_TICK 50.0
#define TIME_PER_TICK_GRAPHIC 16.67

namespace core {
enum class State { MENU, GAME };

class Core {
public:
  Core(const std::string &gamePath);
  ~Core() = default;
  void setSprite(const std::vector<game::Entity> &);
  void switchGraphicalLib(Event &ev, const std::vector<game::Entity> &entities);
  void run();

private:
  std::vector<std::unique_ptr<DLLoader<graphic::IGraphic>>> _graphicLoader;
  std::vector<std::unique_ptr<graphic::IGraphic>> _graphicalTab;
  std::vector<std::string> _graphicNames;
  int _graphicLibIdx;

  std::vector<std::unique_ptr<DLLoader<game::IGame>>> _gameLoader;
  std::vector<std::unique_ptr<game::IGame>> _gameTab;
  std::vector<std::string> _gameNames;
  int _gameLibIdx;

  std::unique_ptr<core::Menu> _menu;
  State _state;

  std::shared_ptr<IDatabase> _database;
};
} // namespace core

/*
    vector de unique wptr IGraphical et un IGame en unique ptr
    <- LIB GRAPHICAL ->
    il faut que le core puisse reprendre la main sur les menus pour les jeux
    IL Faut donc que la class Graphical est une méthode dédié a la pause
*/
