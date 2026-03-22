#include <SFML/Graphics.hpp>
#include <memory>

#include "SFMLGraphicalLib.hpp"

#include "../Graphic.hpp"

void SFML::openWindow(size_t heigth, size_t width, const std::string &windowName)
{
    sf::VideoMode video({heigth, width});
    this->_window.create(video, windowName);
}

void SFML::closeWindow() {
    if (this->_window.isOpen())
        this->_window.close();
}

bool SFML::isOpen() {
    return this->_window.isOpen();
}

void SFML::initGraphic(const std::vector<game::Entity>& entities) 
{
    for (auto &entity : entities){
        this->_textureTab.push_back(sf::Texture(entity.getPath()));
        this->_spriteTab.push_back(sf::Sprite(this->_textureTab.back()));
        this->_spriteTab.end()->setPosition({entity.getStartPos().x, entity.getStartPos().y});
    }
}

void SFML::drawEntities(const std::vector<game::Entity>& entities)
{
    for (sf::Sprite &sprite : this->_spriteTab)
        this->_window.draw(sprite);
}

int main(void)
{
    std::unique_ptr<graphic::IGraphic> sfml = std::make_unique<SFML>();
    sfml->openWindow(1920, 1080, "sfml");
    while (sfml->isOpen())
    {

    }
    
    return 0;
}