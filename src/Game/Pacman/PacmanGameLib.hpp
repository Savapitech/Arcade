#pragma once

#include "Game/Game.hpp"

#define POWERUPTIME 200

struct GhostState {
  size_t entityIdx;
  core::Keys currentDir;
  bool living = true;
};

class PacmanGame : public game::AGame {
private:
  std::vector<std::string> _map;
  core::Keys _currentDir = core::Keys::Space;
  core::Keys _nextDir = core::Keys::Space;

  int _score = 0;
  int _dotsCount = 0;
  bool _gameOver = false;
  int _powerUpTime = 0;

  std::vector<GhostState> _ghosts;

  bool isColliding(core::Vec2 pos) const;
  void movePacman(Event &e);
  void moveGhosts();
  void fearedGhosts();
  void eatenGhosts(GhostState &ghost);
  void resetPositions();

public:
  void initGame() override;
  void simulateGame(Event &e) override;
};
