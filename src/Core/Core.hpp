#pragma once

#include <vector>

#include "Entity.hpp"

namespace core {
class Core {
public:
  void setSprite(const std::vector<game::Entity> &);
  void run(void);

private:
};
} // namespace core
