#include "Entity.hpp"
#include <cstddef>
#include <string>

namespace game {
    entity::entity(std::string name, std::string path, size_t x, size_t y) 
    : _name(name),  _path(path), _start_x(x), _start_y(y) {
      _cur_x = x;
      _cur_y = y; 
    }
}
