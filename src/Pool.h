//
// File: Pool.h
//

#pragma once

#include <array>
#include <iostream>
#include <set>

// IP address type
using octet_type = uint8_t;
using address_type = std::array<octet_type, 4>;
std::ostream &operator<<(std::ostream &ostream, const address_type &addr);

// IP address pool
struct Pool {
  // Constructors
  Pool(std::istream &iss = std::cin);

  // Operators
  friend std::ostream &operator<<(std::ostream &, const Pool &);

  // Methods
  bool filter(address_type::const_iterator) { return true; }
  template <typename Octet, typename... Octets>
  bool filter(address_type::const_iterator iter, Octet octet,
                        Octets... octets) {
    return (*iter == octet) ? filter(++iter, octets...) : false;
  }

  template <typename... Octets>
  void filter(std::ostream &oss, Octets... octets) {
    for (const auto &addr : _pool)
      if (filter(addr.cbegin(), octets...))
        oss << addr << '\n';
  }

  void filter_any(std::ostream &, int);

private:
  std::multiset<address_type, std::greater<address_type>> _pool;
};
