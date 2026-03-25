#pragma once

#include <cstdint>
#include <stack>

#include "Keys.hpp"
#include "Utils.hpp"

/*Macro non-blocking or blocking mouse update*/
#define MNOBLOCK 1 << 0
#define MNBLOCK 1 << 1

class IEvent {
public:
  virtual void clear(void) = 0;
  virtual const core::Vec2 getMouseCoord() = 0;
  virtual void updateMouseCoord(core::Vec2) = 0;
  virtual bool isClicked() = 0;
  virtual bool updateClicked() = 0;
  virtual bool MouseUpdateMode(std::uint8_t) = 0;
  virtual bool getCloseState() = 0;
  virtual void setCloseState(bool state) = 0;
  virtual std::stack<core::Keys> &getKeyStack() = 0;
  virtual void addKey(core::Keys key) = 0;
  virtual ~IEvent() = default;
};
