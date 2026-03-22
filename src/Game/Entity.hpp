#pragma once

#include "../Core/Utils.hpp"
#include <cstddef>
#include <string>

namespace game {

class Entity {
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
  core::Vec2 getPos() const { return _pos; }
  float getStartX() const { return _startPos.x; }
  float getStartY() const { return _startPos.y; }
  const std::string getName() const { return _name; }
  const std::string getPath() const { return _texturePath; }
  void setX(float x) { _pos.x = x; }
  void setY(float y) { _pos.y = y; }
  void setPos(float x, float y) {
    _pos.x = x;
    _pos.y = y;
  }
  void setPos(core::Vec2 pos) { _pos = pos; }
  bool isHidden() { return _hidden; }
  void setHidden(bool hidden) { _hidden = hidden; }
};
} // namespace game
