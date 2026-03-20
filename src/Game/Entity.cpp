#include "Entity.hpp"

#include <cstddef>
#include <string>

namespace game {
Entity::Entity(const std::string name, const std::string path,
               const std::string pathCli, arc::Vec2 coord, arc::Vec2 boxSize)
    : _name(name), _path(path), _pathCli(pathCli), _startCoord(x, y),
      _curCoord(x, y) {}
} // namespace game
