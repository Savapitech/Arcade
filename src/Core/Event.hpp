#pragma once

#include <cstdint>
#include <stack>

#include "Keys.hpp"
#include "Utils.hpp"

/*Macro non-blocking or blocking mouse update*/
#define MNOBLOCK 1 << 0
#define MNBLOCK 1 << 1

class Event {
private:
  core::Vec2 mouseCoord;
  std::stack<core::Keys> keyStack;
  bool close = false;

public:
  const core::Vec2 getMouseCoord();
  void updateMouseCoord(core::Vec2);
  bool isClicked();
  bool updateClicked();
  bool MouseUpdateMode(std::uint8_t);
  bool getCloseState() { return close; }
  void setCloseState(bool state) { close = state; }
  std::stack<core::Keys> &getKeyStack() { return keyStack; }
  void addKey(core::Keys key) { keyStack.push(key); }
};
