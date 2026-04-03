#include "Core/Event.hpp"
#include "Core/Keys.hpp"
#include "Core/Utils.hpp"
#include "Game/Entity.hpp"
#include "Game/Game.hpp"
#include "Logger/Logger.hpp"
#include "SnakeGameLib.hpp"

void Snake::initGame() 
{
    _map = {"############################",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "#                          #",
            "############################"};
    float startX = 230.0f;
    float startY = 70.0f;  
    float tileSize = 20.0f; 
    for (size_t y = 0; y < _map.size(); ++y) {
        for (size_t x = 0; x < _map[y].size(); ++x) {
            if (_map[y][x] == '#') {
                float posX = startX + (x * tileSize);
                float posY = startY + (y * tileSize);
                game::Entity brick("arena", "assets/Game/Snake/brick.jpg",
                                   "\e[0;34m|"
                                   "#",
                                   core::Vec2(posX, posY), 
                                   core::Vec2(posX, posY)); 
                this->_entities.push_back(brick);
            }
        }
    }
}

void Snake::simulateGame(Event &e)
{

}

extern "C" game::IGame *gameEntryPoint() { return new Snake(); }
