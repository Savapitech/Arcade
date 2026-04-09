#pragma once

#include "Game/Game.hpp"
#include <string>
#include <vector>

namespace game {
class IMenu {
public:
  virtual ~IMenu() = default;
  virtual std::string getSelectedGame() const = 0;
  virtual std::string getSelectedGraphic() const = 0;
  virtual void setGraphicIdx(int idx) = 0;
  virtual void setGameIdx(int idx) = 0;
  virtual void setGraphicNames(const std::vector<std::string> &names) = 0;
  virtual void setGameNames(const std::vector<std::string> &names) = 0;
};
} // namespace game