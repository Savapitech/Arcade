#pragma once

#include <vector>
#include "Entity.hpp"

namespace game {

  class IGame {
      private:
        std::vector<game::entity> _entites; 
  };
} //namespace game
