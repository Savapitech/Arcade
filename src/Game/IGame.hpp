#pragma once

#include <vector>
#include "Entity.hpp"
#include "Text.hpp"

namespace game {

  class IGame {
    public:
      virtual const std::vector<Entity> &get() const = 0;
  };

  class AGame : public IGame{
      protected:
          std::vector<game::Entity> _entity;
          std::vector<game::Text> _texts;
      public:
          const std::vector<game::Entity> &get() const {return _entity;}
  };
}
