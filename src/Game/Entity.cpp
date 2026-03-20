#include "Entity.hpp"
#include <cstddef>
#include <string>

namespace game {
Entity::Entity(const std::string name, const std::string path,
               const std::string pathCli, size_t x, size_t y)
    : _name(name), _path(path), _pathCli(pathCli), _startCoord(x, y),
      _curCoord(x, y) {}
} // namespace game
