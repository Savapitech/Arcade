#pragma once

#include <vector>

#include "../Game/Entity.hpp"

namespace graphic {
  class IGraphic {
    public:
      virtual void openWindow(size_t heigth, size_t width, const std::string &windowName) = 0;
      virtual void closeWindow() = 0;
      virtual bool isOpen() = 0;

      virtual void initGraphic(const std::vector<game::Entity> &) = 0;
      virtual void drawEntities(const std::vector<game::Entity> &) = 0;
  };
} // namespace graphic
