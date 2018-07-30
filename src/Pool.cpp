//
// File: Pool.cpp
//

#include "Pool.h"
#include <algorithm>
#include <limits>

std::ostream &operator<<(std::ostream &ostream, const address_type &addr) {
  for (auto iter = addr.cbegin(); iter != addr.cend(); iter++) {
    if (iter != addr.cbegin())
      ostream << '.';
    ostream << static_cast<unsigned>(*iter);
  }

  return ostream;
}

std::ostream &operator<<(std::ostream &ostream, const Pool &pool) {
  for (const auto &addr : pool._pool)
    ostream << addr << '\n';

  return ostream;
}

Pool::Pool(std::istream &iss) {
  for (std::string line; std::getline(iss, line);) {
    auto start = line.cbegin();
    address_type addr{};

    for (auto i = address_type::size_type{0}; i < addr.size(); ++i) {
      auto iter = start;
      while (iter != line.cend() && *iter != '.' && *iter != '\t')
        iter++;

      if (iter != line.cend() && !(*iter == '\t' && (i < addr.size() - 1))) {
        auto value = std::stoi(std::string(start, iter++));
        if (value < std::numeric_limits<octet_type>::max() &&
            value > std::numeric_limits<octet_type>::min()) {
          addr[i] = static_cast<octet_type>(value);
          start = iter;
          continue;
        }
      }
      throw std::runtime_error("Not correct IP address in input data.");
    }

    _pool.insert(addr);
  }
}

void Pool::filter_any(std::ostream &oss, int value) {
  for (const auto &addr : _pool)
    for (const auto &octet : addr)
      if (octet == value) {
        oss << addr << '\n';
        break;
      }
}
