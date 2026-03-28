#pragma once

#include "Game/Game.hpp"

class PacmanGame : public game::AGame {
private:
  std::vector<std::string> _map;
  core::Keys _currentDir = core::Keys::Space;
  core::Keys _nextDir = core::Keys::Space;

  bool isColliding(core::Vec2 pos) const;
  void movePacman(Event &e);

public:
  void initGame() override;
  void simulateGame(Event &e) override;
};
