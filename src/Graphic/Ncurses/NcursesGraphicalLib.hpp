#pragma once

#include <ncurses.h>
#include <string>

#include "Core/Utils.hpp"
#include "Graphic/Graphic.hpp"

#define CHAR_Y_SIZE 16
#define CHAR_X_SIZE 8

class NcursesData {
private:
  std::string _asciiTexture;
  core::Vec2 _pos;
  core::Vec2 _hitbox;

public:
  NcursesData(const std::string &ascii, core::Vec2 pos, core::Vec2 hitbox);
  const std::string getAsciiTexture() const { return _asciiTexture; }
  const core::Vec2 getPos() const { return _pos; }
  const core::Vec2 getHitbox() const { return _hitbox; }
  void setPos(core::Vec2 newPos) { _pos = newPos; }
  void setAsciiTexture(std::string texture) { _asciiTexture = texture; }
  void setHitbox(core::Vec2 hitbox) { _hitbox = hitbox; }
};

class Ncurses : public graphic::IGraphic {
private:
  bool _isopen = false;
  std::vector<NcursesData> _dataTab;

public:
  void openWindow(size_t heigth, size_t width, const std::string &windowName,
                  Event &event) override;
  void closeWindow() override;
  bool isOpen() override;

  void initGraphic(const std::vector<game::Entity> &) override;
  void drawEntities(const std::vector<game::Entity> &) override;
  void fillEvent(Event &event) override;
  void destroyGraphic() override;
};
