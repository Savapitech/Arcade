#include "NcursesGraphicalLib.hpp"
#include "Core/Utils.hpp"

#include <map>
#include <ncurses.h>
#include <string>

void custom_print(core::Vec2 pos, std::string asciiTexture) {
  int y = static_cast<int>(pos.y) / CHAR_Y_SIZE;
  int x = static_cast<int>(pos.x) / CHAR_X_SIZE;
  size_t sep = 0;

  while ((sep = asciiTexture.find("|")) != std::string::npos) {
    mvprintw(y, x, "%s", asciiTexture.substr(0, sep).c_str());
    asciiTexture.erase(0, sep + 1);
    y++;
  }

  if (!asciiTexture.empty()) {
    mvprintw(y, x, "%s", asciiTexture.c_str());
  }
}

void myPrintw(core::Vec2 pos, std::string asciiTexture) {
  static const std::map<std::string, int> mapColors{
      {"\e[0;30m", 8}, {"\e[0;31m", 1}, {"\e[0;32m", 2}, {"\e[0;33m", 3},
      {"\e[0;34m", 4}, {"\e[0;35m", 5}, {"\e[0;36m", 6}, {"\e[0;37m", 7},
  };

  auto sep = asciiTexture.find("|");
  std::string color = asciiTexture.substr(0, sep);
  asciiTexture.erase(0, sep + 1);
  auto it = mapColors.find(color);
  if (it != mapColors.end()) {
    attron(COLOR_PAIR(it->second));
    auto linebreak = asciiTexture.find("|");
    if (linebreak != std::string::npos)
      custom_print(pos, asciiTexture);
    else
      mvprintw(((int)pos.y / CHAR_Y_SIZE), ((int)pos.x / CHAR_X_SIZE), "%s",
               asciiTexture.c_str());
    attroff(COLOR_PAIR(it->second));
  }
}

NcursesData::NcursesData(const std::string &ascii, core::Vec2 pos,
                         core::Vec2 hitbox)
    : _asciiTexture(ascii), _pos(pos), _hitbox(hitbox) {}

void Ncurses::openWindow(size_t heigth, size_t width,
                         const std::string &windowName, Event &event) {
  (void)windowName;
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  start_color();
  init_pair(8, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  resizeterm(heigth, width);
  curs_set(0);
  refresh();
  this->_isopen = true;
  event.setCloseState(true);
}

void Ncurses::closeWindow() {
  this->_isopen = false;
  endwin();
}

void Ncurses::initGraphic(const std::vector<game::Entity> &entities) {
  this->_dataTab.clear();

  for (auto &entity : entities) {
    this->_dataTab.push_back(NcursesData(
        entity.getAsciitexture(), entity.getStartPos(), entity.getHitbox()));
  }
}

void Ncurses::destroyGraphic() { this->_dataTab.clear(); }

void Ncurses::drawEntities(const std::vector<game::Entity> &entities) {
  erase();
  this->_dataTab.clear();
  for (auto &entity : entities)
    this->_dataTab.push_back(NcursesData(entity.getAsciitexture(),
                                         entity.getPos(), entity.getHitbox()));

  for (NcursesData &data : this->_dataTab)
    myPrintw(data.getPos(), data.getAsciiTexture());
  refresh();
}

bool Ncurses::isOpen() { return this->_isopen; }

void Ncurses::fillEvent(Event &event) {
  static const std::map<int, core::Keys> mapKey = {
      {'a', core::Keys::A},     {'b', core::Keys::B},
      {'c', core::Keys::C},     {'d', core::Keys::D},
      {'e', core::Keys::E},     {'f', core::Keys::F},
      {'g', core::Keys::G},     {'h', core::Keys::H},
      {'i', core::Keys::I},     {'j', core::Keys::J},
      {'k', core::Keys::K},     {'l', core::Keys::L},
      {'m', core::Keys::M},     {'n', core::Keys::N},
      {'o', core::Keys::O},     {'p', core::Keys::P},
      {'q', core::Keys::Q},     {'r', core::Keys::R},
      {'s', core::Keys::S},     {'t', core::Keys::T},
      {'u', core::Keys::U},     {'v', core::Keys::V},
      {'w', core::Keys::W},     {'x', core::Keys::X},
      {'y', core::Keys::Y},     {'z', core::Keys::Z},
      {'0', core::Keys::Num0},  {'1', core::Keys::Num1},
      {'2', core::Keys::Num2},  {'3', core::Keys::Num3},
      {'4', core::Keys::Num4},  {'5', core::Keys::Num5},
      {'6', core::Keys::Num6},  {'7', core::Keys::Num7},
      {'8', core::Keys::Num8},  {'9', core::Keys::Num9},
      {' ', core::Keys::Space}, {'\n', core::Keys::Enter},
  };

  nodelay(stdscr, TRUE);
  int ch = getch();

  auto it = mapKey.find(ch);
  if (it != mapKey.end())
    for (int i = 0; i < 16; i++)
      event.addKey(it->second);

  if (ch == 27)
    closeWindow();
}

extern "C" graphic::IGraphic *graphicEntryPoint() { return new Ncurses(); }
