//
// File: main.cpp
//

#include "Pool.h"
#include <cstdlib>

int main(int, char *[]) {
  try {
    Pool pool{};

    std::cout << pool;
    pool.filter(std::cout, 1);
    pool.filter(std::cout, 46, 70);
    pool.filter_any(std::cout, 46);
  } catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}