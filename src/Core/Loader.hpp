#pragma once

#include <memory>

#include "IGame.hpp"

namespace core {
class DLLoader {
public:
  std::unique_ptr<game::IGame> DLLoader();
};
} // namespace core
