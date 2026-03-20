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
    };
}
