#include "PacmanGameLib.hpp"
#include "Core/Event.hpp"
#include "Core/Keys.hpp"
#include "Core/Utils.hpp"
#include "Game/Entity.hpp"
#include "Game/Game.hpp"

void PacmanGame::initGame() {
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
                               "\e[0;31m|A", core::Vec2(346, 178),
                               core::Vec2(346, 178));
  game::Entity blueGhost_entity(
      "blue ghost", "assets/Game/Pacman/BlueGhost.png", "\e[0;36m|A",
      core::Vec2(330, 186), core::Vec2(330, 186));
  game::Entity orangeGhost_entity(
      "orange ghost", "assets/Game/Pacman/OrangeGhost.png", "\e[0;33m|A",
      core::Vec2(346, 186), core::Vec2(346, 186));
  game::Entity pinkGhost_entity(
      "pink ghost", "assets/Game/Pacman/PinkGhost.png", "\e[0;35m|A",
      core::Vec2(330, 178), core::Vec2(330, 178));

  _entities.push_back(arena_entity);
  _entities.push_back(pacman_entity);
  _entities.push_back(redGhost_entity);
  _entities.push_back(blueGhost_entity);
  _entities.push_back(orangeGhost_entity);
  _entities.push_back(pinkGhost_entity);
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

  if (left < 0 || right >= 28 || top < 0 || bottom >= 31)
    return true;

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

  if (_nextDir) {
    core::Vec2 nextPosAttempt = getNextPos(currentPos, _nextDir);
    if (!isColliding(nextPosAttempt)) {
      _currentDir = _nextDir;
      _entities[1].setPos(nextPosAttempt);
      return;
    }
  }

  if (_currentDir) {
    core::Vec2 forwardPos = getNextPos(currentPos, _currentDir);
    if (!isColliding(forwardPos))
      _entities[1].setPos(forwardPos);
  }

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
}

static void moveGhosts(std::vector<game::Entity> &entities) {}

void PacmanGame::simulateGame(Event &e) {
  movePacman(e);
  moveGhosts(this->_entities);
}

extern "C" game::IGame *gameEntryPoint() { return new PacmanGame(); }
