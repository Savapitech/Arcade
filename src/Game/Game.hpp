#pragma once

#include <vector>

#include "Entity.hpp"
#include "Text.hpp"

namespace game {

class IGame {
public:
  virtual const std::vector<Entity> &getEntities() const = 0;
  virtual void initGame() = 0;
  virtual void stopGame() = 0;
};

class AGame : public IGame {
protected:
  bool _running = false;
  size_t _tick;
  std::vector<game::Entity> _entities;
  std::vector<game::Text> _texts;

public:
  const std::vector<game::Entity> &getEntities() const { return _entities; }
  const std::vector<game::Text> &getText() const { return _texts; }
  void stopGame() { _running = false; }
};
} // namespace game
