#include <iostream>
#include <ostream>

#include "Core.hpp"
#include "Logger.hpp"

#define SUCCESS 0;
#define FAILURE 84;

int main(int ac, char **av) {
  if (ac != 2)
    return LOG_ERROR("Usage ./arcade lib.so"), FAILURE;

  try {
    core::Core core(av[1]);

    core.run();

    try {
    } catch (const std::exception &e) {
      return std::cerr << e.what() << std::endl, FAILURE
    }
  } catch (const std::exception &e) {
    LOG_FATAL(e.what());
  }
  return SUCCESS;
}
