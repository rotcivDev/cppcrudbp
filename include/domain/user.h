#pragma once

#include <string>

namespace cppcrudbp::domain {

struct User {
  int id;
  std::string name;
  std::string email;
};

} // namespace cppcrudbp::domain
