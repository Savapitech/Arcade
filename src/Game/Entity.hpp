#pragma once

#include <cstddef>
#include <string>

namespace game {
    class entity {
      private:
        std::string _name;
        std::string _path;
        size_t _start_x;
        size_t _start_y;
        size_t _cur_x;
        size_t _cur_y;
      public:
        entity(std::string name, std::string path, size_t x, size_t y);
        const size_t get_curx() const { return _cur_x; }
        const size_t get_cury() const { return _cur_y; }
        const size_t get_startx() const { return _start_x; }
        const size_t get_starty() const { return _start_y; }
        const std::string get_name() const { return _name; }
        const std::string get_path() const { return _path; }
        void set_curx(size_t x) { _cur_x = x; } 
        void set_cury(size_t y) { _cur_y = y; } 
        void set_startx(size_t x) { _start_x = x; } 
        void set_starty(size_t y) { _start_y = y; } 
    };
}
