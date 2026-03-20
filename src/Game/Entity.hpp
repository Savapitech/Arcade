#pragma once

#include <cstddef>
#include <string>
#include "../Core/Utils.hpp"

namespace game {
    
    class Entity {
      private:
        const std::string _name;
        const std::string _path;
        const std::string _pathCli;
        const arc::Vec2 _startCoord;
        arc::Vec2 _curCoord;

        bool _hidden;
      public:
        Entity(const std::string name, const std::string path, const std::string pathCli, size_t x, size_t y);
        float getCurx() const { return _curCoord.x; }
        float getCury() const { return _curCoord.y; }
        float getStartx() const { return _startCoord.x; }
        float getStarty() const { return _startCoord.y; }
        const std::string getPame() const { return _name; }
        const std::string getPath() const { return _path; }
        void setCurx(float x) { _curCoord.x = x; } 
        void setCury(float y) { _curCoord.y = y; }
        void setCurCoord(float x, float y) {
          _curCoord.x = x;
          _curCoord.y = y;
        }
        void setCurCoord(arc::Vec2 pos) { _curCoord = pos; }
        bool isHidden(){return _hidden;}
        void setHidden(bool hidden){ _hidden = hidden;}
    };
}
