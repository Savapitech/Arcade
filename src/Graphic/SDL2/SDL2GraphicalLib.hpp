#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <vector>

#include "Graphic/Graphic.hpp"

class SDL2 : public graphic::IGraphic {
private:
  SDL_Window *_window = nullptr;
  SDL_Renderer *_renderer = nullptr;
  bool _isOpened = false;
  TTF_Font *_font = nullptr;

  std::vector<SDL_Texture *> _textureTab;
  std::vector<SDL_Rect> _rectTab;

  core::Keys convertSDLKey(SDL_Keycode keycode) const;

public:
  void openWindow(size_t heigth, size_t width, const std::string &windowName,
                  Event &event) override;
  void closeWindow() override;
  bool isOpen() override;

  void initGraphic(const std::vector<game::Entity> &) override;
  void drawEntities(const std::vector<game::Entity> &,
                    const std::vector<game::Text> &) override;
  void fillEvent(Event &event) override;
  void destroyGraphic() override;

  ~SDL2() override;
};
