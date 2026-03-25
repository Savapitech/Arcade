#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Graphic/Graphic.hpp"
#include "SFMLGraphicalLib.hpp"

void SFML::openWindow(size_t heigth, size_t width,
                      const std::string &windowName, Event &event) {
  sf::VideoMode video(
      {static_cast<unsigned int>(heigth), static_cast<unsigned int>(width)});
  this->_window.create(video, windowName);
  event.setCloseState(true);
}

void SFML::closeWindow() {
  if (this->_window.isOpen())
    this->_window.close();
}

bool SFML::isOpen() { return this->_window.isOpen(); }

void SFML::initGraphic(const std::vector<game::Entity> &entities) {
  this->_spriteTab.clear();
  this->_textureTab.clear();

  this->_textureTab.reserve(entities.size());
  this->_spriteTab.reserve(entities.size());

  for (auto &entity : entities) {
    this->_textureTab.push_back(sf::Texture(entity.getPath()));
    this->_spriteTab.push_back(sf::Sprite(this->_textureTab.back()));
    this->_spriteTab.back().setPosition(
        {(float)entity.getStartPos().x, (float)entity.getStartPos().y});
  }
}

void SFML::destroyGraphic() {
  this->_textureTab.clear();
  this->_spriteTab.clear();
}

void SFML::drawEntities(const std::vector<game::Entity> &entities) {
  this->_window.clear();
  for (sf::Sprite &sprite : this->_spriteTab)
    this->_window.draw(sprite);
  this->_window.display();
}

void SFML::fillEvent(Event &event) {
  while (const std::optional eventWindow = this->_window.pollEvent()) {
    if (eventWindow->is<sf::Event::Closed>()) {
      this->_window.close();
      event.setCloseState(false);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    event.addKey(core::Keys::A);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
    event.addKey(core::Keys::B);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
    event.addKey(core::Keys::C);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    event.addKey(core::Keys::D);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
    event.addKey(core::Keys::E);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
    event.addKey(core::Keys::F);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
    event.addKey(core::Keys::G);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H))
    event.addKey(core::Keys::H);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
    event.addKey(core::Keys::I);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    event.addKey(core::Keys::J);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    event.addKey(core::Keys::K);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
    event.addKey(core::Keys::L);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
    event.addKey(core::Keys::M);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
    event.addKey(core::Keys::N);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
    event.addKey(core::Keys::O);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    event.addKey(core::Keys::P);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    event.addKey(core::Keys::Q);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    event.addKey(core::Keys::S);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    event.addKey(core::Keys::R);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
    event.addKey(core::Keys::T);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
    event.addKey(core::Keys::U);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
    event.addKey(core::Keys::V);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    event.addKey(core::Keys::W);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    event.addKey(core::Keys::X);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
    event.addKey(core::Keys::Y);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
    event.addKey(core::Keys::Z);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
    event.addKey(core::Keys::Num0);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
    event.addKey(core::Keys::Num1);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
    event.addKey(core::Keys::Num2);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
    event.addKey(core::Keys::Num3);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
    event.addKey(core::Keys::Num4);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
    event.addKey(core::Keys::Num5);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))
    event.addKey(core::Keys::Num6);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))
    event.addKey(core::Keys::Num7);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))
    event.addKey(core::Keys::Num8);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))
    event.addKey(core::Keys::Num9);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    event.addKey(core::Keys::Space);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    event.addKey(core::Keys::Enter);
}

SFML::~SFML() {
  this->_spriteTab.clear();
  this->_textureTab.clear();

  if (this->_window.isOpen())
    this->_window.close();
}

extern "C" graphic::IGraphic *graphicEntryPoint() { return new SFML(); }
