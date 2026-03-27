#include "Core/Core.hpp"
#include "Logger/Logger.hpp"

#define SUCCESS 0;
#define FAILURE 84;

int main(int ac, char **av) {
  if (ac != 2)
    return LOG_ERROR("Usage ./arcade lib.so"), FAILURE;

  LOG_INFO("Arcade, loading lib...");
  try {
    core::Core core(av[1]);

    core.run();
  } catch (const std::exception &e) {
    LOG_FATAL("Error [" + std::string(e.what()) + "]");
  }
  return SUCCESS;
}
