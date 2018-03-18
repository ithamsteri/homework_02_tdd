//
// File: Pool.h
//

#pragma once

#include <array>
#include <iostream>
#include <vector>

struct Pool {
  // Type aliases
  using octet_type = uint8_t;
  using address_type = std::array<octet_type, 4>;
  using pool_type = std::vector<address_type>;

  // Constructors
  Pool(std::istream &istream = std::cin);

  // Operators
  friend std::ostream &operator<<(std::ostream &, const Pool &);

  // Methods
  void filter(int first, std::ostream &oss = std::cout);
  void filter(int first, int second, std::ostream &oss = std::cout);
  void filter_any(int value, std::ostream &oss = std::cout);

private:
  pool_type _pool;
};
