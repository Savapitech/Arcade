#pragma once

#include <vector>
#include "Entity.hpp"

namespace arc {
  class Core{
      public:
        const std::vector<game::entity> &get() const;
        void setSprite(const std::vector<game::entity> &);
  };
} //namespace core
