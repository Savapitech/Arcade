#pragma once

#include "Game/Game.hpp"
#include "Game/Game.hpp"

class PacmanGame : public game::AGame {
public:
  void initGame() override;
  void simulateGame(Event &e) override {};
};
