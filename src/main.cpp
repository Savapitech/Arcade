#include <iostream>
#include <ostream>

#include "Graphic.hpp"
#include "Loader.hpp"
#include "Logger.hpp"

#define SUCCESS 0;
#define FAILURE 84;

int main(int ac, char **av) {
  if (ac != 2)
    return std::cerr << "Usage ./arcade lib.so" << std::endl, FAILURE;

  DLLoader<graphic::IGraphic> loader("./lib/arcade_sfml.so");
  {
    std::unique_ptr<graphic::IGraphic> a = loader.getInstance("entryPoint");

    Event ev;

    a->openWindow(1920, 1080, "Super", ev);
    while (a->isOpen())
      a->fillEvent(ev);

    try {
      LOG_ERROR("arcade in progress");
    } catch (const std::exception &e) {
      return std::cerr << e.what() << std::endl, FAILURE
    }
  }
  return SUCCESS;
}
