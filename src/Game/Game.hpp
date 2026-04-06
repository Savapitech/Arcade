#pragma once

#include <memory>

#include "Core/Event.hpp"
#include "Core/IDatabase.hpp"
#include "Entity.hpp"
#include "Text.hpp"

namespace game {

class IGame {
public:
  virtual const std::vector<Entity> &getEntities() const = 0;
  virtual const std::vector<Text> &getTexts() const = 0;
  virtual void initGame(std::shared_ptr<core::IDatabase> database) = 0;
  virtual void simulateGame(Event &ev) = 0;
  virtual void stopGame() = 0;
  virtual const std::string &getUserName() const = 0;
  virtual void setUserName(const std::string &name) = 0;
  virtual ~IGame() = default;
};

class AGame : public IGame {
protected:
  bool _running = false;
  size_t _tick;
  std::vector<game::Entity> _entities;
  std::vector<game::Text> _texts;
  std::shared_ptr<core::IDatabase> _database;
  std::string _userName = "Player";

public:
  AGame() = default;
  const std::vector<game::Entity> &getEntities() const override {
    return _entities;
  }
  const std::vector<game::Text> &getTexts() const override { return _texts; }
  void stopGame() override { _running = false; }
  const std::string &getUserName() const override { return _userName; }
  void setUserName(const std::string &name) override { _userName = name; }
};
} // namespace game
