#pragma once

#include <vector>

#include "Core/Event.hpp"
#include "Game/Entity.hpp"
#include "Game/Text.hpp"

namespace graphic {
class IGraphic {
public:
  virtual void openWindow(size_t heigth, size_t width,
                          const std::string &windowName, Event &event) = 0;
  virtual void closeWindow() = 0;
  virtual bool isOpen() = 0;

  virtual void initGraphic(const std::vector<game::Entity> &) = 0;
  virtual void destroyGraphic() = 0;
  virtual void drawEntities(const std::vector<game::Entity> &,
                            const std::vector<game::Text> &) = 0;
  virtual void fillEvent(Event &event) = 0;

  virtual ~IGraphic() = default;
};
} // namespace graphic
