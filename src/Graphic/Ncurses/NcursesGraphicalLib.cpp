#include <iostream>
#include <map>
#include <ncurses.h>
#include <ostream>

#include "NcursesGraphicalLib.hpp"

void Ncurses::openWindow(size_t heigth, size_t width,
                         const std::string &windowName, Event &event) {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  // resizeterm(heigth, width);
  std::cout << "\033]0;" << windowName << std::flush;
  curs_set(0);
  refresh();
  this->_isopen = true;
  event.setCloseState(true);
}

void Ncurses::closeWindow() {
  this->_isopen = false;
  endwin();
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
    event.addKey(it->second);

  if (ch == 27)
    closeWindow();
}

extern "C" graphic::IGraphic *entryPoint() { return new Ncurses(); }
