  #include <iostream>
#include <ostream>

  #define SUCCESS 0;
  #define FAILURE 84;

int main(int ac, char **av) {
  if (ac != 2)
    return std::cerr << "Usage ./arcade lib.so" << std::endl, FAILURE;

  try {
    std::cout << "arcade in implementation" << std::endl; 
  } catch (const std::exception &e) {
      return std::cerr << e.what() << std::endl, FAILURE
  }
  return SUCCESS;
}
