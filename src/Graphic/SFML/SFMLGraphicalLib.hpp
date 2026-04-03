#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Graphic/Graphic.hpp"

class SFML : public graphic::IGraphic {
private:
  sf::RenderWindow _window;

  std::vector<sf::Sprite> _spriteTab;
  std::vector<sf::Texture> _textureTab;
  sf::Font _font;

public:
  void openWindow(size_t heigth, size_t width, const std::string &windowName,
                  Event &event) override;
  void closeWindow() override;
  bool isOpen() override;

  void initGraphic(const std::vector<game::Entity> &) override;
  void drawEntities(const std::vector<game::Entity> &,
                    const std::vector<game::Text> &) override;
  void fillEvent(Event &event) override;
  virtual void destroyGraphic() override;

  ~SFML() override;
};
