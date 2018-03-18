//
// File: Pool.h
//

#pragma once

#include <array>
#include <iostream>
#include <set>

struct Pool {
  // Type aliases
  using octet_type = uint8_t;
  using address_type = std::array<octet_type, 4>;
  using pool_type = std::multiset<address_type, std::greater<address_type>>;

  // Constructors
  Pool(std::istream &iss = std::cin, std::ostream &oss = std::cout);

  // Operators
  friend std::ostream &operator<<(std::ostream &, const Pool &);

  // Methods
  void filter(int first);
  void filter(int first, int second);
  void filter_any(int value);

private:
  pool_type _pool;
  std::ostream &_oss;
};
