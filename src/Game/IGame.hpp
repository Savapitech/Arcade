#pragma once

#include <vector>
#include "Entity.hpp"
#include "Text.hpp"

namespace game {

  class IGame {
  };

  class AGame {
    protected:
       std::vector<game::Entity> _entites;
       std::vector<game::Text> _texts;
  }
}
