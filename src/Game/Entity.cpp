#include <cstddef>
#include <string>

#include "Entity.hpp"

namespace game {
Entity::Entity(const std::string name, const std::string texturePath,
               const std::string asciiTexture, arc::Vec2 pos, arc::Vec2 boxSize)
    : _name(name), _texturePath(texturePath), _asciiTexture(asciiTexture), _startPos(pos),
      _pos(pos) {}
} // namespace game
