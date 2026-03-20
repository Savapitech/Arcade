#pragma once

#include <memory>

#include "IGame.hpp"

class GameLoader {
public:
  std::unique_ptr<game::IGame> gameLoader();
};
