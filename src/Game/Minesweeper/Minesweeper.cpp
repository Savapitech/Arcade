#include "Minesweeper.hpp"
#include "Core/Core.hpp"
#include "Core/Keys.hpp"
#include "Core/Utils.hpp"
#include "Logger/Logger.hpp"

void MinesweeperGame::initGame() {
  _map = {"11111b1000", "1b11122110", "11111b1000", "011b221000", "1222211100",
          "1b1011b200", "1110112b10", "01112b2100", "01b1121100", "011011b100"};
  _cursorPos = core::Vec2(0, 0);

  for (int y = 0; y < MAP_SIZE; y++) {
    for (int x = 0; x < MAP_SIZE; x++) {
      game::Entity hidden_entity(
          std::string("case_") + std::to_string(y) + "_" + std::to_string(x),
          "assets/Game/Minesweeper/Ms_sprites.png", "\e[0;33m|[]",
          core::Vec2(260 + x * RECT_SIZE, 70 + y * RECT_SIZE),
          core::Vec2(260 + x * RECT_SIZE, 70 + y * RECT_SIZE));
      hidden_entity.setSrcRect(RECT_HIDDEN);
      _entities.push_back(hidden_entity);
    }
  }
  std::string caseName = "case_0_0";
  for (auto &ent : _entities) {
    if (ent.getName() == caseName) {
      ent.setSrcRect(RECT_ACTUAL);
      break;
    }
  }
}

void MinesweeperGame::updateCursor(Event &e) {
  core::Vec2 oldPos = _cursorPos;
  std::stack<core::Keys> keys = e.getKeyStack();
  while (!keys.empty()) {
    core::Keys k = keys.top();
    keys.pop();
    switch (k) {
    case core::Keys::Z:
      if (_cursorPos.y > 0)
        _cursorPos.y--;
      break;

    case core::Keys::S:
      if (_cursorPos.y < MAP_SIZE - 1)
        _cursorPos.y++;
      break;

    case core::Keys::Q:
      if (_cursorPos.x > 0)
        _cursorPos.x--;
      break;

    case core::Keys::D:
      if (_cursorPos.x < MAP_SIZE - 1)
        _cursorPos.x++;
      break;

    default:
      break;
    }
  }
  std::string caseName =
      "case_" + std::to_string(oldPos.y) + "_" + std::to_string(oldPos.x);
  for (auto &ent : _entities) {
    if (ent.getName() == caseName) {
      ent.setSrcRect(RECT_HIDDEN);
      break;
    }
  }
  caseName = "case_" + std::to_string(_cursorPos.y) + "_" +
             std::to_string(_cursorPos.x);
  for (auto &ent : _entities) {
    if (ent.getName() == caseName) {
      ent.setSrcRect(RECT_ACTUAL);
      break;
    }
  }
}

void MinesweeperGame::simulateGame(Event &e) {
  updateCursor(e);
  return;
}

extern "C" game::IGame *gameEntryPoint() { return new MinesweeperGame(); }
