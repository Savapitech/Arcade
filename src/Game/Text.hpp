#pragma once
#include "Utils.hpp"
#include "string"


namespace game 
{
    class Text 
    {
        private:
            std::string _text;
            const arc::Vec2 _startCoord;
            arc::Vec2 _curCoord;
          public:
            Text(const std::string name, const std::string path, const std::string pathCli, size_t x, size_t y);
            float getCurx() const { return _curCoord.x; }
            float getCury() const { return _curCoord.y; }
            float getStartx() const { return _startCoord.x; }
            float getStarty() const { return _startCoord.y; }
            const std::string getText() const { return _text; }
            void setCurx(float x) { _curCoord.x = x; } 
            void setCury(float y) { _curCoord.y = y; }
            void setCurCoord(float x, float y) {
              _curCoord.x = x;
              _curCoord.y = y;
            }
            void setCurCoord(arc::Vec2 pos) { _curCoord = pos; }
    };
}