#pragma once

#include "Core/Utils.hpp"
#include "Game/Game.hpp"

#define MAP_SIZE 10
#define RECT_SIZE 96
#define RECT_1 (core::Rect((RECT_SIZE * 3), 0, RECT_SIZE, RECT_SIZE))
#define RECT_2 (core::Rect((RECT_SIZE * 3), RECT_SIZE, RECT_SIZE, RECT_SIZE))
#define RECT_3                                                                 \
  (core::Rect((RECT_SIZE * 3), (RECT_SIZE * 2), RECT_SIZE, RECT_SIZE))
#define RECT_4                                                                 \
  (core::Rect((RECT_SIZE * 3), (RECT_SIZE * 3), RECT_SIZE, RECT_SIZE))
#define RECT_5 (core::Rect((RECT_SIZE * 4), 0, RECT_SIZE, RECT_SIZE))
#define RECT_6                                                                 \
  (core::Rect((RECT_SIZE * 4), (RECT_SIZE * 1), RECT_SIZE, RECT_SIZE))
#define RECT_7                                                                 \
  (core::Rect((RECT_SIZE * 4), (RECT_SIZE * 2), RECT_SIZE, RECT_SIZE))
#define RECT_8                                                                 \
  (core::Rect((RECT_SIZE * 4), (RECT_SIZE * 3), RECT_SIZE, RECT_SIZE))
#define RECT_SHOWN                                                             \
  (core::Rect((RECT_SIZE * 2), (RECT_SIZE * 3), RECT_SIZE, RECT_SIZE))
#define RECT_HIDDEN                                                            \
  (core::Rect((RECT_SIZE * 3), (RECT_SIZE * 2), RECT_SIZE, RECT_SIZE))
#define RECT_ACTUAL                                                            \
  (core::Rect((RECT_SIZE * 0), (RECT_SIZE * 0), RECT_SIZE, RECT_SIZE))

class MinesweeperGame : public game::AGame {
private:
  std::vector<std::string> _map;
  int _score = 0;
  core::Vec2 _cursorPos;
  bool checkCaseIsBomb(int y, int x);
  void updateCursor(Event &e);

public:
  void initGame() override;
  void simulateGame(Event &e) override;
};
