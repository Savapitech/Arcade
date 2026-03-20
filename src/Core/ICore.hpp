#pragma once

#include <vector>
#include "Entity.hpp"

namespace core {
  class Icore{
      public:
        virtual const std::vector<game::entity> &get() const = 0;
        virtual void setSprite(const std::vector<game::entity> &) = 0;
  };
} //namespace core
