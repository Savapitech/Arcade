#include "Entity.hpp"
#include <cstddef>
#include <string>

namespace game {
    entity::entity(std::string name, std::string path, size_t x, size_t y) 
    : _name(name),  _path(path), _startCoord(x, y), _curCoord(x, y) {}
}
