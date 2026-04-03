#include "Text.hpp"

namespace game {

Text::Text(const std::string name, const std::string text,
           const std::string pathCli, core::Vec2 pos)
    : _name(name), _text(text), _startPos(pos), _pos(pos), _hidden(false) {
  (void)pathCli;
}

} // namespace game
