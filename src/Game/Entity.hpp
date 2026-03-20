#pragma once

#include <cstddef>
#include <string>
#include "../Core/Utils.hpp"

namespace game {
    
    class entity {
      private:
        const std::string _name;
        const std::string _path;
        const arc::Vec2 _startCoord;
        arc::Vec2 _curCoord;
      public:
        entity(std::string name, std::string path, size_t x, size_t y);
        const float get_curx() const { return _curCoord.x; }
        const float get_cury() const { return _curCoord.y; }
        const float get_startx() const { return _startCoord.x; }
        const float get_starty() const { return _startCoord.y; }
        const std::string get_name() const { return _name; }
        const std::string get_path() const { return _path; }
        void set_curx(float x) { _curCoord.x = x; } 
        void set_cury(float y) { _curCoord.y = y; }  
    };
}
