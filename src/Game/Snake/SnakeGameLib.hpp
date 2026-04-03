#pragma once

#include "Game/Game.hpp"

#define POWERUPTIME 520

struct GhostState {
  size_t entityIdx;
  core::Keys currentDir;
};

class Snake : public game::AGame {
private:
  std::vector<std::string> _map;

public:
  void initGame() override;
  void simulateGame(Event &e) override;
};
