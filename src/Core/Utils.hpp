#pragma once

#include <stack>

#include "Keys.hpp"

namespace core {
class Vec2 {
public:
  float x;
  float y;

  Vec2(float x_ = 0.f, float y_ = 0.f) : x(x_), y(y_) {}
};

class Rect {
public:
  float x;
  float y;
  float width;
  float height;

  Rect(float x_ = 0.f, float y_ = 0.f, float w_ = 0.f, float h_ = 0.f)
      : x(x_), y(y_), width(w_), height(h_) {}
};

} // namespace core

namespace utils {
inline bool containsKey(std::stack<core::Keys> &myStack, core::Keys keyToFind) {
  std::stack<core::Keys> tempStack;
  bool found = false;

  while (!myStack.empty()) {
    if (myStack.top() == keyToFind) {
      found = true;
      break;
    }
    tempStack.push(myStack.top());
    myStack.pop();
  }
  while (!tempStack.empty()) {
    myStack.push(tempStack.top());
    tempStack.pop();
  }

  return found;
}
} // namespace utils