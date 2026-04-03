#include "Minesweeper.hpp"
#include "Core/Core.hpp"
#include "Core/Keys.hpp"
#include "Core/Utils.hpp"
#include "Logger/Logger.hpp"

void MinesweeperGame::initGame() {
  _map = {
    "11111b1000",
    "1b11122110",
    "11111b1000",
    "011b221000",
    "1222211100",
    "1b1011b200",
    "1110112b10",
    "01112b2100",
    "01b1121100",
    "011011b100"
  };
  _cursorPos = core::Vec2(0, 0);

  int x = 0;
  int y = 0;

  while (y < MAP_SIZE) {
    while(x < MAP_SIZE) {
       game::Entity hidden_entity(std::string("case_") + std::to_string(y) + "_" +
                                 std::to_string(x), "assets/Game/Minesweeper/Ms_sprites.png", "\e[0;33m|[]", core::Vec2(260 + x * RECT_SIZE, 70 + y * RECT_SIZE),           core::Vec2(260 + x * RECT_SIZE, 70 + y * RECT_SIZE));
          hidden_entity.setSrcRect(RECT_HIDDEN);
        _entities.push_back(hidden_entity);
        x++;
    }
    y++;
    x = 0;
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
        if (_cursorPos.y < MAP_SIZE)
          _cursorPos.y++;
        break;
  
      case core::Keys::Q:
        if (_cursorPos.x > 0)
          _cursorPos.x--;
        break;

      case core::Keys::D:
        if (_cursorPos.x < MAP_SIZE)
          _cursorPos.x++;
        break;

      default:
        return;
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
  caseName = "case_" + std::to_string(_cursorPos.y) + "_" + std::to_string(_cursorPos.x);
    for (auto &ent : _entities) {
      if (ent.getName() == caseName) {
        ent.setSrcRect(RECT_HIDDEN);
        break;
      }
    }
}

void MinesweeperGame::simulateGame(Event &e) {
  updateCursor(e);
  return; 
}



extern "C" game::IGame *gameEntryPoint() { return new MinesweeperGame(); }
