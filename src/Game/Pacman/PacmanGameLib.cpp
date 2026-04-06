#include "PacmanGameLib.hpp"
#include "Core/Event.hpp"
#include "Core/Keys.hpp"
#include "Core/Utils.hpp"
#include "Game/Entity.hpp"
#include "Game/Game.hpp"
#include "Logger/Logger.hpp"
#include <cstdint>

void PacmanGame::initGame(std::shared_ptr<core::IDatabase> database) {
  this->_database = database;
  std::cout << this->_database->getPlayerGameScore("pacman", "aa").score
            << std::endl;
  _map = {"############################", "#            ##            #",
          "# #### ##### ## ##### #### #", "# #  # #   # ## #   # #  # #",
          "# #### ##### ## ##### #### #", "#                          #",
          "# #### ## ######## ## #### #", "# #### ## ######## ## #### #",
          "#      ##    ##    ##      #", "###### ##### ## ##### ######",
          "     # ##### ## ##### #     ", "     # ##          ## #     ",
          "     # ## ###  ### ## #     ", "###### ## #      # ## ######",
          "          #      #          ", "###### ## #      # ## ######",
          "     # ## ######## ## #     ", "     # ##          ## #     ",
          "     # ## ######## ## #     ", "###### ## ######## ## ######",
          "#            ##            #", "# #### ##### ## ##### #### #",
          "# #### ##### ## ##### #### #", "#    #                #    #",
          "###  # ## ######## ## #  ###", "###  # ## ######## ## #  ###",
          "#      ##    ##    ##      #", "# ########## ## ########## #",
          "# ########## ## ########## #", "#                          #",
          "############################"};

  _entities.clear();
  _texts.clear();
  _ghosts.clear();
  _score = 0;
  _dotsCount = 0;
  _gameOver = false;
  _powerUpTime = 0;
  _currentDir = core::Keys::Space;
  _nextDir = core::Keys::Space;

  game::Entity arena_entity(
      "arena", "assets/Game/Pacman/Arena_Empty.png",
      "\e[0;34m|"
      "########################################################|"
      "##                        ####                        ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##  ##    ##  ##      ##  ####  ##      ##  ##    ##  ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##                                                    ##|"
      "##  ########  ####  ################  ####  ########  ##|"
      "##  ########  ####  ################  ####  ########  ##|"
      "##            ####        ####        ####            ##|"
      "############  ##########  ####  ##########  ############|"
      "          ##  ##########  ####  ##########  ####        |"
      "          ##  ####                    ####  ####        |"
      "          ##  ####  #######  #######  ####  ####        |"
      "############  ####  ###          ###  ####  ############|"
      "                    ###          ###                    |"
      "############  ####  ###          ###  ####  ############|"
      "          ##  ####  ################  ####  ####        |"
      "          ##  ####                    ####  ####        |"
      "          ##  ####  ################  ####  ####        |"
      "############  ####  ################  ####  ############|"
      "##                        ####                        ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##  ########  ##########  ####  ##########  ########  ##|"
      "##      ####                                ####      ##|"
      "######  ####  ####  ################  ####  ####  ######|"
      "######  ####  ####  ################  ####  ####  ######|"
      "##            ####        ####        ####            ##|"
      "##  ####################  ####  ####################  ##|"
      "##  ####################  ####  ####################  ##|"
      "##                                                    ##|"
      "########################################################|",
      core::Vec2(230, 70), core::Vec2(230, 70));
  game::Entity pacman_entity("pacman", "assets/Game/Pacman/Pacman.png",
                             "\e[0;33m|C", core::Vec2(330, 202),
                             core::Vec2(330, 202));
  pacman_entity.setSrcRect(core::Rect(0, 0, 16, 16));
  game::Entity redGhost_entity("red ghost", "assets/Game/Pacman/RedGhost.png",
                               "\e[0;31m|A", core::Vec2(340, 190),
                               core::Vec2(346, 178));
  redGhost_entity.setSrcRect(core::Rect(0, 0, 16, 16));
  game::Entity blueGhost_entity(
      "blue ghost", "assets/Game/Pacman/BlueGhost.png", "\e[0;36m|A",
      core::Vec2(330, 186), core::Vec2(330, 186));
  blueGhost_entity.setSrcRect(core::Rect(0, 0, 16, 16));
  game::Entity orangeGhost_entity(
      "orange ghost", "assets/Game/Pacman/OrangeGhost.png", "\e[0;33m|A",
      core::Vec2(340, 186), core::Vec2(346, 186));
  orangeGhost_entity.setSrcRect(core::Rect(0, 0, 16, 16));
  game::Entity pinkGhost_entity(
      "pink ghost", "assets/Game/Pacman/PinkGhost.png", "\e[0;35m|A",
      core::Vec2(340, 178), core::Vec2(330, 178));
  pinkGhost_entity.setSrcRect(core::Rect(0, 0, 16, 16));

  _entities.push_back(arena_entity);
  _entities.push_back(pacman_entity);
  _entities.push_back(redGhost_entity);
  _entities.push_back(blueGhost_entity);
  _entities.push_back(orangeGhost_entity);
  _entities.push_back(pinkGhost_entity);

  _ghosts.push_back({2, core::Keys::Z});
  _ghosts.push_back({3, core::Keys::D});
  _ghosts.push_back({4, core::Keys::Q});
  _ghosts.push_back({5, core::Keys::Z});

  _score = 0;
  _dotsCount = 0;
  _gameOver = false;

  for (int y = 0; y < 31; ++y) {
    for (int x = 0; x < 28; ++x) {
      if (_map[y][x] == ' ') {
        bool isGhostHouse = (y >= 12 && y <= 16 && x >= 10 && x <= 17);
        bool isOutsideBlocks = (y >= 10 && y <= 19 && (x < 6 || x > 21));

        if (x > 0 && x < 27 && !isGhostHouse && !isOutsideBlocks && y != 14) {
          _dotsCount++;
          if ((x == 1 || x == 26) && (y == 2 || y == 28)) {
            _map[y][x] = '*';
            game::Entity dot(std::string("dot_") + std::to_string(y) + "_" +
                                 std::to_string(x),
                             "assets/Game/Pacman/Character_Sprite_Cheat.png",
                             "\e[0;33m|*",
                             core::Vec2(240 + x * 8 - 6, 76 + y * 8 - 4),
                             core::Vec2(240 + x * 8 - 6, 76 + y * 8 - 4));
            dot.setSrcRect(core::Rect(100, 25, 8, 8));
            _entities.push_back(dot);
            continue;
          }
          _map[y][x] = '.';
          game::Entity dot(std::string("dot_") + std::to_string(y) + "_" +
                               std::to_string(x),
                           "assets/Game/Pacman/Pacman.png", "\e[0;33m|.",
                           core::Vec2(240 + x * 8 - 4, 76 + y * 8 - 4),
                           core::Vec2(240 + x * 8 - 4, 76 + y * 8 - 4));
          dot.setSrcRect(core::Rect(6, 6, 4, 4));
          _entities.push_back(dot);
        }
      }
    }
  }
}

bool PacmanGame::isColliding(core::Vec2 pos) const {
  float offsetX = 230;
  float offsetY = 70;
  float blockSize = 8;

  core::Vec2 logicalPos = {pos.x + 2.75f, pos.y + 4};

  int left = (logicalPos.x - offsetX + 2) / blockSize;
  int right = (logicalPos.x - offsetX + 5) / blockSize;
  int top = (logicalPos.y - offsetY + 2) / blockSize;
  int bottom = (logicalPos.y - offsetY + 5) / blockSize;

  if (left < 0 || right >= 28 || top < 0 || bottom >= 31) {
    if (top >= 13 && bottom <= 15)
      return false;
    return true;
  }

  if (_map[top][left] == '#' || _map[top][right] == '#' ||
      _map[bottom][left] == '#' || _map[bottom][right] == '#')
    return true;
  return false;
}

void PacmanGame::movePacman(Event &e) {
  std::stack<core::Keys> keys = e.getKeyStack();
  while (!keys.empty()) {
    core::Keys k = keys.top();
    keys.pop();
    if (k == core::Keys::Z || k == core::Keys::Q || k == core::Keys::S ||
        k == core::Keys::D)
      _nextDir = k;
  }

  auto getNextPos = [](core::Vec2 pos, core::Keys dir) {
    core::Vec2 newPos = pos;
    float speed = 4;
    switch (dir) {
    case core::Keys::Z:
      newPos.y -= speed;
      break;
    case core::Keys::Q:
      newPos.x -= speed;
      break;
    case core::Keys::S:
      newPos.y += speed;
      break;
    case core::Keys::D:
      newPos.x += speed;
      break;
    default:
      break;
    }
    return newPos;
  };

  core::Vec2 currentPos = _entities[1].getPos();

  if (currentPos.x < 230.0f - 12.0f) {
    _entities[1].setPos({230.0f + 27.0f * 8.0f, currentPos.y});
    return;
  } else if (currentPos.x > 230.0f + 27.0f * 8.0f) {
    _entities[1].setPos({230.0f - 8.0f, currentPos.y});
    return;
  }

  if (_nextDir != core::Keys::Space) {
    core::Vec2 nextPosAttempt = getNextPos(currentPos, _nextDir);
    if (!isColliding(nextPosAttempt)) {
      _currentDir = _nextDir;

      switch (_currentDir) {
      case core::Keys::Z:
        _entities[1].setSrcRect(core::Rect(0, 32, 16, 16));
        break;
      case core::Keys::S:
        _entities[1].setSrcRect(core::Rect(0, 48, 16, 16));
        break;
      case core::Keys::Q:
        _entities[1].setSrcRect(core::Rect(0, 16, 16, 16));
        break;
      case core::Keys::D:
        _entities[1].setSrcRect(core::Rect(0, 0, 16, 16));
        break;
      default:
        break;
      }

      _entities[1].setPos(nextPosAttempt);
      return;
    }
  }

  if (_currentDir) {
    core::Vec2 forwardPos = getNextPos(currentPos, _currentDir);
    if (!isColliding(forwardPos))
      _entities[1].setPos(forwardPos);
  }
}

void PacmanGame::resetPositions() {
  _entities[1].setPos({330, 202});
  _nextDir = core::Keys::Space;
  _currentDir = core::Keys::Space;

  _entities[2].setPath(_entities[2].getBasePath());
  _entities[2].setPos({346, 178}); // Red Ghost
  _entities[3].setPath(_entities[3].getBasePath());
  _entities[3].setPos({330, 186}); // Blue Ghost
  _entities[4].setPath(_entities[4].getBasePath());
  _entities[4].setPos({346, 186}); // Orange Ghost
  _entities[5].setPath(_entities[5].getBasePath());
  _entities[5].setPos({330, 178}); // Pink Ghost

  _ghosts[0].currentDir = core::Keys::Z;
  _ghosts[0].living = true;
  _ghosts[1].currentDir = core::Keys::D;
  _ghosts[1].living = true;
  _ghosts[2].currentDir = core::Keys::Q;
  _ghosts[2].living = true;
  _ghosts[3].currentDir = core::Keys::Z;
  _ghosts[3].living = true;
}

void PacmanGame::eatenGhosts(GhostState &ghost) {
  core::Vec2 homePos = _entities[ghost.entityIdx].getStartPos();
  core::Vec2 homeLogical = {homePos.x + 2.75f, homePos.y + 4};
  int homeX = (homeLogical.x - 230 + 2) / 8;
  int homeY = (homeLogical.y - 70 + 2) / 8;
  _entities[ghost.entityIdx].setPath("assets/Game/Pacman/Dead_Ghost.png");

  core::Vec2 ghostPos = _entities[ghost.entityIdx].getPos();
  core::Vec2 gLogical = {ghostPos.x + 2.75f, ghostPos.y + 4};

  if (ghostPos.x < 230.0f - 12.0f) {
    _entities[ghost.entityIdx].setPos({230.0f + 27.0f * 8.0f, ghostPos.y});
    return;
  } else if (ghostPos.x > 230.0f + 27.0f * 8.0f) {
    _entities[ghost.entityIdx].setPos({230.0f - 8.0f, ghostPos.y});
    return;
  }

  if (std::abs(homeLogical.x - gLogical.x) < 12 &&
      std::abs(homeLogical.y - gLogical.y) < 12) {
    ghost.living = true;
    _entities[ghost.entityIdx].setPath(
        _entities[ghost.entityIdx].getBasePath());
    return;
  }

  bool isAligned =
      (((int)gLogical.x - 230) % 8 == 0 && ((int)gLogical.y - 70) % 8 == 0);

  if (!isAligned) {
    int dx = std::abs((int)gLogical.x - 230) % 8;
    int dy = std::abs((int)gLogical.y - 70) % 8;
    isAligned = (dx <= 1 && dy <= 1);
  }

  if (isAligned) {
    int gx = (gLogical.x - 230) / 8;
    int gy = (gLogical.y - 70) / 8;

    std::vector<core::Keys> validDirs;
    std::vector<core::Vec2> nextCells;

    auto checkDir = [&](core::Keys dir, int nx, int ny, core::Keys opp) {
      if (nx >= 0 && nx < 28 && ny >= 0 && ny < 31) {
        if (ghost.currentDir != opp && _map[ny][nx] != '#') {
          validDirs.push_back(dir);
          nextCells.push_back({(float)nx, (float)ny});
        }
      }
    };

    checkDir(core::Keys::Z, gx, gy - 1, core::Keys::S);
    checkDir(core::Keys::S, gx, gy + 1, core::Keys::Z);
    checkDir(core::Keys::Q, gx - 1, gy, core::Keys::D);
    checkDir(core::Keys::D, gx + 1, gy, core::Keys::Q);

    if (validDirs.empty()) {
      if (ghost.currentDir == core::Keys::Z)
        ghost.currentDir = core::Keys::S;
      else if (ghost.currentDir == core::Keys::S)
        ghost.currentDir = core::Keys::Z;
      else if (ghost.currentDir == core::Keys::Q)
        ghost.currentDir = core::Keys::D;
      else if (ghost.currentDir == core::Keys::D)
        ghost.currentDir = core::Keys::Q;
    } else {
      float minDist = 9999999.0f;
      core::Keys bestDir = validDirs[0];

      for (size_t k = 0; k < validDirs.size(); ++k) {
        float dx = nextCells[k].x - homeX;
        float dy = nextCells[k].y - homeY;
        float dist = dx * dx + dy * dy;

        dist += (rand() % 10);
        if (dist < minDist) {
          minDist = dist;
          bestDir = validDirs[k];
        }
      }
      ghost.currentDir = bestDir;
    }
  }

  float speed = 3;
  if (ghost.currentDir == core::Keys::Z) {
    ghostPos.y -= speed;
    _entities[ghost.entityIdx].setSrcRect(core::Rect(32, 0, 16, 16));
  }
  if (ghost.currentDir == core::Keys::S) {
    ghostPos.y += speed;
    _entities[ghost.entityIdx].setSrcRect(core::Rect(48, 0, 16, 16));
  }
  if (ghost.currentDir == core::Keys::Q) {
    ghostPos.x -= speed;
    _entities[ghost.entityIdx].setSrcRect(core::Rect(16, 0, 16, 16));
  }
  if (ghost.currentDir == core::Keys::D) {
    _entities[ghost.entityIdx].setSrcRect(core::Rect(0, 0, 16, 16));
    ghostPos.x += speed;
  }
  _entities[ghost.entityIdx].setPos(ghostPos);
}

void PacmanGame::moveGhosts() {
  core::Vec2 pacmanPos = _entities[1].getPos();
  core::Vec2 pacLogical = {pacmanPos.x + 2.75f, pacmanPos.y + 4};
  int pacX = (pacLogical.x - 230 + 2) / 8;
  int pacY = (pacLogical.y - 70 + 2) / 8;

  for (auto &ghost : _ghosts) {
    if (!ghost.living) {
      eatenGhosts(ghost);
      continue;
    }
    core::Vec2 ghostPos = _entities[ghost.entityIdx].getPos();
    core::Vec2 gLogical = {ghostPos.x + 2.75f, ghostPos.y + 4};

    if (ghostPos.x < 230.0f - 12.0f) {
      _entities[ghost.entityIdx].setPos({230.0f + 27.0f * 8.0f, ghostPos.y});
      continue;
    } else if (ghostPos.x > 230.0f + 27.0f * 8.0f) {
      _entities[ghost.entityIdx].setPos({230.0f - 8.0f, ghostPos.y});
      continue;
    }

    if (std::abs(pacLogical.x - gLogical.x) < 6 &&
        std::abs(pacLogical.y - gLogical.y) < 6) {
      _gameOver = true;
      LOG_INFO("GAME OVER PacMan");
      resetPositions();
      return;
    }

    bool isAligned =
        (((int)gLogical.x - 230) % 8 == 0 && ((int)gLogical.y - 70) % 8 == 0);

    if (!isAligned) {
      int dx = std::abs((int)gLogical.x - 230) % 8;
      int dy = std::abs((int)gLogical.y - 70) % 8;
      isAligned = (dx <= 1 && dy <= 1);
    }

    if (isAligned) {
      int gx = (gLogical.x - 230) / 8;
      int gy = (gLogical.y - 70) / 8;

      std::vector<core::Keys> validDirs;
      std::vector<core::Vec2> nextCells;

      auto checkDir = [&](core::Keys dir, int nx, int ny, core::Keys opp) {
        if (nx >= 0 && nx < 28 && ny >= 0 && ny < 31) {
          if (ghost.currentDir != opp && _map[ny][nx] != '#') {
            validDirs.push_back(dir);
            nextCells.push_back({(float)nx, (float)ny});
          }
        }
      };

      checkDir(core::Keys::Z, gx, gy - 1, core::Keys::S);
      checkDir(core::Keys::S, gx, gy + 1, core::Keys::Z);
      checkDir(core::Keys::Q, gx - 1, gy, core::Keys::D);
      checkDir(core::Keys::D, gx + 1, gy, core::Keys::Q);

      if (validDirs.empty()) {
        if (ghost.currentDir == core::Keys::Z)
          ghost.currentDir = core::Keys::S;
        else if (ghost.currentDir == core::Keys::S)
          ghost.currentDir = core::Keys::Z;
        else if (ghost.currentDir == core::Keys::Q)
          ghost.currentDir = core::Keys::D;
        else if (ghost.currentDir == core::Keys::D)
          ghost.currentDir = core::Keys::Q;
      } else {
        float minDist = 9999999.0f;
        core::Keys bestDir = validDirs[0];

        for (size_t k = 0; k < validDirs.size(); ++k) {
          float dx = nextCells[k].x - pacX;
          float dy = nextCells[k].y - pacY;
          float dist = dx * dx + dy * dy;

          dist += (rand() % 10);
          if (dist < minDist) {
            minDist = dist;
            bestDir = validDirs[k];
          }
        }
        ghost.currentDir = bestDir;
      }
    }

    float speed = 2;
    if (ghost.currentDir == core::Keys::Z) {
      ghostPos.y -= speed;
      _entities[ghost.entityIdx].setSrcRect(core::Rect(64, 0, 16, 16));
    }
    if (ghost.currentDir == core::Keys::S) {
      ghostPos.y += speed;
      _entities[ghost.entityIdx].setSrcRect(core::Rect(96, 0, 16, 16));
    }
    if (ghost.currentDir == core::Keys::Q) {
      ghostPos.x -= speed;
      _entities[ghost.entityIdx].setSrcRect(core::Rect(32, 0, 16, 16));
    }
    if (ghost.currentDir == core::Keys::D) {
      _entities[ghost.entityIdx].setSrcRect(core::Rect(0, 0, 16, 16));
      ghostPos.x += speed;
    }
    _entities[ghost.entityIdx].setPos(ghostPos);
  }
}

void PacmanGame::fearedGhosts() {
  core::Vec2 pacmanPos = _entities[1].getPos();
  core::Vec2 pacLogical = {pacmanPos.x + 2.75f, pacmanPos.y + 4};
  int pacX = (pacLogical.x - 230 + 2) / 8;
  int pacY = (pacLogical.y - 70 + 2) / 8;

  for (auto &ghost : _ghosts) {
    if (!ghost.living) {
      eatenGhosts(ghost);
      continue;
    }
    _entities[ghost.entityIdx].setPath("assets/Game/Pacman/Feared_Ghost.png");
    _entities[ghost.entityIdx].setSrcRect(core::Rect(0, 0, 16, 16));
    core::Vec2 ghostPos = _entities[ghost.entityIdx].getPos();
    core::Vec2 gLogical = {ghostPos.x + 2.75f, ghostPos.y + 4};

    if (ghostPos.x < 230.0f - 12.0f) {
      _entities[ghost.entityIdx].setPos({230.0f + 27.0f * 8.0f, ghostPos.y});
      continue;
    } else if (ghostPos.x > 230.0f + 27.0f * 8.0f) {
      _entities[ghost.entityIdx].setPos({230.0f - 8.0f, ghostPos.y});
      continue;
    }

    if (std::abs(pacLogical.x - gLogical.x) < 6 &&
        std::abs(pacLogical.y - gLogical.y) < 6) {
      ghost.living = false;
    }

    bool isAligned =
        (((int)gLogical.x - 230) % 8 == 0 && ((int)gLogical.y - 70) % 8 == 0);

    if (!isAligned) {
      int dx = std::abs((int)gLogical.x - 230) % 8;
      int dy = std::abs((int)gLogical.y - 70) % 8;
      isAligned = (dx <= 1 && dy <= 1);
    }

    if (isAligned) {
      int gx = (gLogical.x - 230) / 8;
      int gy = (gLogical.y - 70) / 8;

      std::vector<core::Keys> validDirs;
      std::vector<core::Vec2> nextCells;

      auto checkDir = [&](core::Keys dir, int nx, int ny, core::Keys opp) {
        if (nx >= 0 && nx < 28 && ny >= 0 && ny < 31) {
          if (ghost.currentDir != opp && _map[ny][nx] != '#') {
            validDirs.push_back(dir);
            nextCells.push_back({(float)nx, (float)ny});
          }
        }
      };

      checkDir(core::Keys::Z, gx, gy - 1, core::Keys::S);
      checkDir(core::Keys::S, gx, gy + 1, core::Keys::Z);
      checkDir(core::Keys::Q, gx - 1, gy, core::Keys::D);
      checkDir(core::Keys::D, gx + 1, gy, core::Keys::Q);

      if (validDirs.empty()) {
        if (ghost.currentDir == core::Keys::Z)
          ghost.currentDir = core::Keys::S;
        else if (ghost.currentDir == core::Keys::S)
          ghost.currentDir = core::Keys::Z;
        else if (ghost.currentDir == core::Keys::Q)
          ghost.currentDir = core::Keys::D;
        else if (ghost.currentDir == core::Keys::D)
          ghost.currentDir = core::Keys::Q;
      } else {
        float maxDist = -1.0f;
        core::Keys bestDir = validDirs[0];

        for (size_t k = 0; k < validDirs.size(); ++k) {
          float dx = nextCells[k].x - pacX;
          float dy = nextCells[k].y - pacY;
          float dist = dx * dx + dy * dy;

          dist += (rand() % 10);
          if (dist > maxDist) {
            maxDist = dist;
            bestDir = validDirs[k];
          }
        }
        ghost.currentDir = bestDir;
      }
    }

    float speed = 1;
    if (ghost.currentDir == core::Keys::Z)
      ghostPos.y -= speed;
    if (ghost.currentDir == core::Keys::S)
      ghostPos.y += speed;
    if (ghost.currentDir == core::Keys::Q)
      ghostPos.x -= speed;
    if (ghost.currentDir == core::Keys::D)
      ghostPos.x += speed;
    _entities[ghost.entityIdx].setPos(ghostPos);
  }
}

void PacmanGame::simulateGame(Event &e) {
  movePacman(e);
  int last_time = _powerUpTime;
  if (_powerUpTime > 0) {
    _powerUpTime--;
    fearedGhosts();
  } else
    moveGhosts();
  if (last_time == 1 && _powerUpTime == 0) {
    for (auto &ghost : _ghosts)
      _entities[ghost.entityIdx].setPath(
          _entities[ghost.entityIdx].getBasePath());
  }

  core::Vec2 pacLogical = {_entities[1].getPos().x + 2,
                           _entities[1].getPos().y + 2};
  int pacX = (pacLogical.x - 230 + 2) / 8;
  int pacY = (pacLogical.y - 70 + 2) / 8;

  if (pacX >= 0 && pacX < 28 && pacY >= 0 && pacY < 31 &&
      _map[pacY][pacX] == '*') {
    _powerUpTime = POWERUPTIME;
    _map[pacY][pacX] = ' ';
    _dotsCount--;

    std::string dotName =
        "dot_" + std::to_string(pacY) + "_" + std::to_string(pacX);
    for (auto &ent : _entities) {
      if (ent.getName() == dotName) {
        ent.setPos({-1000, -1000});
        break;
      }
    }

    if (_dotsCount == 0) {
      LOG_INFO("WIN Pacman");
      resetPositions();
      _map.clear();
      initGame(this->_database);
    }
  }

  if (pacX >= 0 && pacX < 28 && pacY >= 0 && pacY < 31 &&
      _map[pacY][pacX] == '.') {
    _map[pacY][pacX] = ' ';
    _score += 10;
    if ((std::uint32_t)_score >
        _database->getPlayerGameScore("pacman", "aa").score)
      _database->setPlayerScore("pacman", "aa", _score);
    _dotsCount--;

    std::string dotName =
        "dot_" + std::to_string(pacY) + "_" + std::to_string(pacX);
    for (auto &ent : _entities) {
      if (ent.getName() == dotName) {
        ent.setPos({-1000, -1000});
        break;
      }
    }

    if (_dotsCount == 0) {
      LOG_INFO("WIN Pacman");
      resetPositions();
      _map.clear();
      initGame(this->_database);
    }
  }
}

extern "C" game::IGame *gameEntryPoint() { return new PacmanGame(); }
