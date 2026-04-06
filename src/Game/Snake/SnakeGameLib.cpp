#include "SnakeGameLib.hpp"
#include "Core/Event.hpp"
#include "Core/Keys.hpp"
#include "Core/Utils.hpp"
#include "Game/Entity.hpp"
#include "Game/Game.hpp"
#include "SnakeGameLib.hpp"

#define SNAKE 0
#define FRUIT 1

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

void Snake::initGame(std::shared_ptr<core::IDatabase> database) {
  this->_database = database;
  this->_entities.clear();

  _map = {"############################", "#                          #",
          "#                          #", "#                          #",
          "#                          #", "#                          #",
          "#                          #", "#                          #",
          "#                          #", "#                          #",
          "#                          #", "#                          #",
          "#                          #", "#                          #",
          "#                          #", "############################"};
  game::Entity SnakeHead("snake_head", "assets/Game/Snake/apple.png",
                         "\e[0;34m|@", core::Vec2(250, 90),
                         core::Vec2(240, 80));
  game::Entity fruit("fruit", "assets/Game/Snake/apple.png", "\e[0;31m|@",
                     core::Vec2(250, 90), core::Vec2(240, 80));

  SnakeHead.setHidden(false);
  this->_entities.push_back(SnakeHead);
  this->_entities.push_back(fruit);

  this->_dirState = RIGHT;

  float startX = 230.0f;
  float startY = 70.0f;
  float tileSize = 16.0f;

  for (size_t y = 0; y < _map.size(); ++y) {
    for (size_t x = 0; x < _map[y].size(); ++x) {
      if (_map[y][x] == '#') {
        float posX = startX + (x * tileSize);
        float posY = startY + (y * tileSize);
        game::Entity brick("arena", "assets/Game/Snake/brick.jpg", "\e[0;34m|#",
                           core::Vec2(posX, posY), core::Vec2(posX, posY));
        this->_entities.push_back(brick);
      }
    }
  }
  this->_tailPoolStartIndex = this->_entities.size();
  int maxSnakeSize = 100;

  for (int i = 0; i < maxSnakeSize; ++i) {
    game::Entity tailSegment("tail", "assets/Game/Snake/apple.png",
                             "\e[0;32m|o", core::Vec2(-100, -100),
                             core::Vec2(-100, -100));
    tailSegment.setHidden(true);
    this->_entities.push_back(tailSegment);
  }

  _score = 0;
  _snakeTail.clear();
  _dirState = RIGHT;
  uint32_t best =
      _database ? _database->getPlayerGameScore("snake", _userName).score : 0;
  _texts.clear();
  _texts.push_back(game::Text("player", "Player: " + _userName, "", {230, 45}));
  _texts.push_back(game::Text("score", "Score: 0", "", {430, 45}));
  _texts.push_back(
      game::Text("best", "Best: " + std::to_string(best), "", {630, 45}));
}
void Snake::simulateGame(Event &e) {

  std::stack<core::Keys> keys = e.getKeyStack();
  if (keys.empty()) {
    handleSnake(core::Keys::L);
    return;
  }

  bool use = false;

  while (!keys.empty()) {
    core::Keys currentKey = keys.top();
    keys.pop();
    if (use == false)
      this->handleSnake(currentKey);
    use = true;
  }
  this->spawnFruit();
}

void Snake::handleSnake(core::Keys key) {
  core::Vec2 previousHeadPos = this->_entities[SNAKE].getPos();
  core::Vec2 pos = previousHeadPos;

  float speed = 8.0f;
  switch (key) {
  case core::Keys::Z:
    this->_dirState = UP;
    break;
  case core::Keys::S:
    this->_dirState = DOWN;
    break;
  case core::Keys::Q:
    this->_dirState = LEFT;
    break;
  case core::Keys::D:
    this->_dirState = RIGHT;
    break;
  default:
    break;
  }

  switch (this->_dirState) {
  case UP:
    pos.y -= speed;
    break;
  case DOWN:
    pos.y += speed;
    break;
  case LEFT:
    pos.x -= speed;
    break;
  case RIGHT:
    pos.x += speed;
    break;
  default:
    break;
  }

  if (checkCollision(pos) == true) {
    this->_dirState = RIGHT;
    this->_entities[SNAKE].setPos(core::Vec2(250, 90));
    this->_snakeTail.clear();
  } else {
    this->_entities[SNAKE].setPos(pos);
    if (!this->_snakeTail.empty()) {
      for (int i = this->_snakeTail.size() - 1; i > 0; --i) {
        this->_snakeTail[i] = this->_snakeTail[i - 1];
      }
      this->_snakeTail[0] = previousHeadPos;
    }
  }
  this->updateSnakeTail();
}

void Snake::spawnFruit() {
  if (!(std::abs(_entities[SNAKE].getPos().x - _entities[FRUIT].getPos().x) <=
            20.f &&
        std::abs(_entities[SNAKE].getPos().y - _entities[FRUIT].getPos().y) <=
            20.f))
    return;

  bool positionValide = false;
  float newX = 0.0f;
  float newY = 0.0f;

  float startX = 240.0f;
  float startY = 80.0f;
  float tileSize = 8.0f;
  int mapWidth = 28;
  int mapHeight = 16;

  while (!positionValide) {
    int gridX = (std::rand() % (mapWidth - 2)) + 1;
    int gridY = (std::rand() % (mapHeight - 2)) + 1;

    newX = startX + (gridX * tileSize);
    newY = startY + (gridY * tileSize);

    positionValide = true;

    for (size_t i = 0; i < _entities.size(); ++i) {
      if (i == FRUIT)
        continue;

      if (_entities[i].getPos().x == newX && _entities[i].getPos().y == newY) {
        positionValide = false;
        break;
      }
    }
  }
  _entities[FRUIT].setPos(core::Vec2(newX, newY));

  _score += 10;
  if (_database && (std::uint32_t)_score >
                       _database->getPlayerGameScore("snake", _userName).score)
    _database->setPlayerScore("snake", _userName, _score);
  for (auto &t : _texts) {
    if (t.getName() == "score")
      t.setContent("Score: " + std::to_string(_score));
    if (t.getName() == "best") {
      uint32_t best =
          _database ? _database->getPlayerGameScore("snake", _userName).score
                    : 0;
      t.setContent("Best: " + std::to_string(best));
    }
  }

  core::Vec2 newTailPos;
  if (this->_snakeTail.empty())
    newTailPos = _entities[SNAKE].getPos();
  else
    newTailPos = this->_snakeTail.back();

  this->_snakeTail.push_back(newTailPos);
}

void Snake::updateSnakeTail() {
  size_t maxSnakeSize = 100;

  for (size_t i = 0; i < maxSnakeSize; ++i) {
    size_t entityIndex = this->_tailPoolStartIndex + i;
    if (entityIndex >= this->_entities.size())
      break;

    if (i < this->_snakeTail.size()) {
      this->_entities[entityIndex].setPos(this->_snakeTail[i]);
      this->_entities[entityIndex].setHidden(false);
    } else {
      this->_entities[entityIndex].setHidden(true);
      this->_entities[entityIndex].setPos(core::Vec2(-100.0f, -100.0f));
    }
  }
}

bool Snake::checkCollision(core::Vec2 nextPos) {
  float startX = 230.0f;
  float startY = 70.0f;
  float tileSize = 16.0f;

  size_t gridX =
      static_cast<size_t>((nextPos.x - startX + (tileSize / 2)) / tileSize);
  size_t gridY =
      static_cast<size_t>((nextPos.y - startY + (tileSize / 2)) / tileSize);

  if (gridY <= 0 || gridY > _map.size() || gridX <= 0 ||
      gridX > _map[gridY].size()) {
    return true;
  }

  if (_map[gridY][gridX] == '#') {
    return true;
  }
  for (size_t entityIndex = this->_tailPoolStartIndex;
       entityIndex < this->_entities.size(); entityIndex++) {
    if (this->_entities[SNAKE].getPos().x ==
            this->_entities[entityIndex].getPos().x &&
        this->_entities[SNAKE].getPos().y ==
            this->_entities[entityIndex].getPos().y)
      return true;
  }
  return false;
}

extern "C" game::IGame *gameEntryPoint() { return new Snake(); }
