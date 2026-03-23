#pragma once

#include <ncurses.h>

#include "../Graphic.hpp"

class Ncurses : public graphic::IGraphic {
private:
  bool _isopen = false;

public:
  void openWindow(size_t heigth, size_t width, const std::string &windowName,
                  Event &event) override;
  void closeWindow() override;
  bool isOpen() override;

  void initGraphic(const std::vector<game::Entity> &) override {};
  void drawEntities(const std::vector<game::Entity> &) override {};
  void fillEvent(Event &event) override;
};
