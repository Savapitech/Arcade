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
  const arc::Vec2 _startPos;
  arc::Vec2 _pos;

  bool _hidden;

public:
  Entity(const std::string name, const std::string path,
         const std::string pathCli, size_t x, size_t y);
  arc::Vec2 getPos() const { return _pos; }
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
  void setCurCoord(arc::Vec2 pos) { _pos = pos; }
  bool isHidden() { return _hidden; }
  void setHidden(bool hidden) { _hidden = hidden; }
};
} // namespace game
