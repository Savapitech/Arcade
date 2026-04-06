#pragma once

#include "Game/Game.hpp"

#define POWERUPTIME 520

struct GhostState {
  size_t entityIdx;
  core::Keys currentDir;
};

class Snake : public game::AGame {
private:
  short int _dirState;

  core::Vec2 _fruitPos;
  std::vector<core::Vec2> _snakeTail;
  size_t _tailPoolStartIndex;

  std::vector<std::string> _map;
  bool checkCollision(core::Vec2 nextPos);
  void handleSnake(core::Keys key);
  void spawnFruit();
  void updateSnakeTail();

public:
  void initGame(std::shared_ptr<core::IDatabase> database) override;
  void simulateGame(Event &e) override;
};
