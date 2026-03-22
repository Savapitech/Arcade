#include <iostream>
#include <ostream>

#include "Loader.hpp"
#include "Graphic.hpp"

#define SUCCESS 0;
#define FAILURE 84;

int main(int ac, char **av) 
{
  if (ac != 2)
    return std::cerr << "Usage ./arcade lib.so" << std::endl, FAILURE;

  DLLoader<graphic::IGraphic> loader("./sfml.so");

  graphic::IGraphic *a = loader.getInstance("entryPoint");

  Event ev;

  a->openWindow(1920, 1080, "Super", ev);
  while (a->isOpen())
  {
    a->fillEvent(ev);
  }
  
  

  try {
    std::cout << "arcade in progress" << std::endl;
  } catch (const std::exception &e) {
    return std::cerr << e.what() << std::endl, FAILURE
  }
  
  return SUCCESS;
}
