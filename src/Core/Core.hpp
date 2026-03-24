#pragma once

#include <memory>
#include <vector>

#include "../Game/Game.hpp"
#include "../Graphic/Graphic.hpp"
#include "Loader.hpp"
#include "Entity.hpp"
#include "Loader.hpp"

namespace core {
class Core {
public:
  Core(const std::string &gamePath);
  ~Core();
  void setSprite(const std::vector<game::Entity> &);
  void run();

private:
  
  std::vector<std::unique_ptr<DLLoader<graphic::IGraphic>>> graphicLoader;
  std::vector<std::unique_ptr<graphic::IGraphic>> graphicalTab;
  std::vector<std::shared_ptr<DLLoader<graphic::IGraphic>>> _graphLoadersTab;
  int graphicLibIdx = 0;

  std::vector<std::unique_ptr<game::IGame>> gameTab;
  int gameLibIdx = 0;
};
} // namespace core

/*
    vector de unique wptr IGraphical et un IGame en unique ptr
    <- LIB GRAPHICAL ->
    il faut que le core puisse reprendre la main sur les menus pour les jeux
    IL Faut donc que la class Graphical est une méthode dédié a la pause
*/
