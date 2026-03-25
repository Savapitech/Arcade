#pragma once

#include "IEntity.hpp"

namespace game {

class Entity : public IEntity {
private:
  const std::string _name;
  const std::string _texturePath;
  const std::string _asciiTexture;
  const core::Vec2 _startPos;
  const core::Vec2 _hitBoxSize;

  core::Vec2 _pos;
  bool _hidden;

public:
  Entity(const std::string name, const std::string path,
         const std::string pathCli, core::Vec2 coord, core::Vec2 boxSize);
  core::Vec2 getPos() const override { return _pos; }
  const core::Vec2 getStartPos() const override { return _startPos; }
  const std::string getName() const override { return _name; }
  const std::string getPath() const override { return _texturePath; }
  const std::string getAsciitexture() const override { return _asciiTexture; }
  const core::Vec2 getHitbox() const override { return _hitBoxSize; }
  void setX(float x) override { _pos.x = x; }
  void setY(float y) override { _pos.y = y; }
  void setPos(float x, float y) override {
    _pos.x = x;
    _pos.y = y;
  }
  void setPos(core::Vec2 pos) override { _pos = pos; }
  bool isHidden() override { return _hidden; }
  void setHidden(bool hidden) override { _hidden = hidden; }
};
} // namespace game
