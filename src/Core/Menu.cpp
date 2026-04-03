#include "Menu.hpp"
#include "Core/Keys.hpp"

namespace core {

Menu::Menu(const std::vector<std::string> &graphics,
           const std::vector<std::string> &games)
    : _graphicNames(graphics), _gameNames(games), _selectedGraphic(0),
      _selectedGame(0), _userName("Player") {}

void Menu::initGame() {
  this->_running = true;
  buildTexts();
}

void Menu::buildTexts() {
  this->_texts.clear();
  this->_entities.clear();

  this->_texts.push_back(game::Text("title", "ARCADE MENU", "", {200, 50}));
  this->_texts.push_back(game::Text("name_label", "Name:", "", {200, 100}));
  this->_texts.push_back(
      game::Text("name_val", _userName + "_", "", {300, 100}));

  this->_texts.push_back(game::Text("games_title", "GAMES", "", {200, 150}));

  for (size_t i = 0; i < _gameNames.size(); i++) {
    std::string prefix = ((int)i == _selectedGame) ? "> " : "  ";
    this->_texts.push_back(game::Text("game_" + std::to_string(i),
                                      prefix + _gameNames[i], "",
                                      {200, 180.0f + i * 30.0f}));
  }
}

void Menu::simulateGame(Event &ev) {
  if (!this->_running)
    return;

  auto keysOriginal = ev.getKeyStack();
  std::stack<core::Keys> filter;

  while (!ev.getKeyStack().empty()) {
    core::Keys key = ev.getKeyStack().top();
    ev.getKeyStack().pop();

    if (key >= core::Keys::A && key <= core::Keys::Z && key != core::Keys::Z &&
        key != core::Keys::S) {
      if (_userName.length() < 12) {
        _userName += (char)('A' + (key - core::Keys::A));
      }
    } else if (key == core::Keys::Space && !_userName.empty()) {
      _userName.pop_back();
    } else if (key == core::Keys::Num8 || key == core::Keys::Z) {
      if (_selectedGame > 0)
        _selectedGame--;
    } else if (key == core::Keys::Num2 || key == core::Keys::S) {
      if (_selectedGame < (int)_gameNames.size() - 1)
        _selectedGame++;
    } else {
      filter.push(key);
    }
  }

  while (!filter.empty()) {
    ev.addKey(filter.top());
    filter.pop();
  }

  buildTexts();
}

std::string Menu::getSelectedGame() const {
  if (_gameNames.empty())
    return "";
  return _gameNames[_selectedGame];
}

std::string Menu::getSelectedGraphic() const {
  if (_graphicNames.empty())
    return "";
  return _graphicNames[_selectedGraphic];
}

void Menu::setGraphicIdx(int idx) { _selectedGraphic = idx; }
void Menu::setGameIdx(int idx) { _selectedGame = idx; }

} // namespace core
