//
// File: main.cpp
//

#include "Pool.h"

int main(int, char *[]) {
  Pool pool{};

  std::cout << pool;
  pool.filter(1);
  pool.filter(46, 70);
  pool.filter(46);
}