#include "PacmanGameLib.hpp"
#include "Core/Event.hpp"
#include "Core/Keys.hpp"
#include "Core/Utils.hpp"
#include "Game/Entity.hpp"
#include "Game/Game.hpp"

void PacmanGame::initGame() {
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
                             "\e[0;33m|C", core::Vec2(340, 200),
                             core::Vec2(340, 200));
  game::Entity redGhost_entity("red ghost", "assets/Game/Pacman/RedGhost.png",
                               "\e[0;31m|A", core::Vec2(350, 190),
                               core::Vec2(350, 190));
  game::Entity blueGhost_entity(
      "blue ghost", "assets/Game/Pacman/BlueGhost.png", "\e[0;36m|A",
      core::Vec2(330, 190), core::Vec2(330, 190));
  game::Entity orangeGhost_entity(
      "orange ghost", "assets/Game/Pacman/OrangeGhost.png", "\e[0;33m|A",
      core::Vec2(350, 170), core::Vec2(350, 170));
  game::Entity pinkGhost_entity(
      "pink ghost", "assets/Game/Pacman/PinkGhost.png", "\e[0;35m|A",
      core::Vec2(330, 170), core::Vec2(330, 170));

  _entities.push_back(arena_entity);
  _entities.push_back(pacman_entity);
  _entities.push_back(redGhost_entity);
  _entities.push_back(blueGhost_entity);
  _entities.push_back(orangeGhost_entity);
  _entities.push_back(pinkGhost_entity);
}

static void movePacman(Event &e, game::Entity &pacman) {
  std::stack<core::Keys> keys = e.getKeyStack();
  while (!keys.empty()) {
    core::Vec2 newPos = pacman.getPos();

    switch (keys.top()) {
    case core::Keys::Z:
      newPos.y -= 1;
      break;
    case core::Keys::Q:
      newPos.x -= 1;
      break;
    case core::Keys::S:
      newPos.y += 1;
      break;
    case core::Keys::D:
      newPos.x += 1;
      break;
    default:
      break;
    }
    pacman.setPos(newPos);
    keys.pop();
  }
}

static void moveGhosts(std::vector<game::Entity> &entities) {
  int i = 0;
  core::Vec2 pacmanPos = entities[1].getPos();
  for (auto &entity : entities) {
    if (i >= 2) {
      core::Vec2 newPos = entity.getPos();
      if (newPos.x > pacmanPos.x)
        newPos.x -= 0.5;
      else
        newPos.x += 0.5;
      if (newPos.y > pacmanPos.y)
        newPos.y -= 0.5;
      else
        newPos.y += 0.5;
      entity.setPos(newPos);
    }
    i++;
  }
}

void PacmanGame::simulateGame(Event &e) {
  movePacman(e, this->_entities[1]);
  moveGhosts(this->_entities);
}

extern "C" game::IGame *gameEntryPoint() { return new PacmanGame(); }
