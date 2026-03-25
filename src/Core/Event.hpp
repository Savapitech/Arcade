#pragma once

#include "Core/Utils.hpp"
#include "IEvent.hpp"

class Event : public IEvent {
private:
  core::Vec2 mouseCoord;
  std::stack<core::Keys> keyStack;
  bool close = false;

public:
  Event() { close = false; }
  void clear(void) override {
    while (!keyStack.empty())
      keyStack.pop();
  }
  const core::Vec2 getMouseCoord() override { return mouseCoord; }
  void updateMouseCoord(core::Vec2) override {}
  bool isClicked() override { return true; }
  bool updateClicked() override { return true; }
  bool MouseUpdateMode(std::uint8_t) override { return true; }
  bool getCloseState() override { return close; }
  void setCloseState(bool state) override { close = state; }
  std::stack<core::Keys> &getKeyStack() override { return keyStack; }
  void addKey(core::Keys key) override { keyStack.push(key); }
};
