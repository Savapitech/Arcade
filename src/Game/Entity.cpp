#include <string>

#include "Entity.hpp"

namespace game {
Entity::Entity(const std::string name, const std::string texturePath,
               const std::string asciiTexture, core::Vec2 pos,
               core::Vec2 boxSize)
    : _name(name), _texturePath(texturePath), _basePath(texturePath),
      _asciiTexture(asciiTexture), _startPos(pos), _pos(pos) {}
} // namespace game
