#pragma once

#include <string>

#include "Core/Utils.hpp"

namespace game {

class IEntity {
public:
  virtual core::Vec2 getPos() const = 0;
  virtual const core::Vec2 getStartPos() const = 0;
  virtual const std::string getName() const = 0;
  virtual const std::string getPath() const = 0;
  virtual const std::string getBasePath() const = 0;
  virtual const std::string getAsciitexture() const = 0;
  virtual const core::Vec2 getHitbox() const = 0;
  virtual void setX(float x) = 0;
  virtual void setY(float y) = 0;
  virtual void setPos(float x, float y) = 0;
  virtual void setPos(core::Vec2 pos) = 0;
  virtual bool isHidden() const = 0;
  virtual void setHidden(bool hidden) = 0;
  virtual core::Rect getSrcRect() const = 0;
  virtual void setSrcRect(core::Rect rect) = 0;
  virtual void setAsciitexture(const std::string &ascii) = 0;
  virtual void setPath(const std::string &path) = 0;
  virtual ~IEntity() = default;
};
} // namespace game
