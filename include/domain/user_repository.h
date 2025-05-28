#pragma once

#include "user.h"
#include <optional>
#include <vector>

namespace cppcrudbp::domain {

class IUserRepository {
public:
  virtual ~IUserRepository() = default;

  virtual bool createUser(const User &user) = 0;
  virtual std::optional<User> getUserById(int id) = 0;
  virtual std::vector<User> getAllUsers() = 0;
  virtual bool updateUser(const User &user) = 0;
  virtual bool deleteUser(int id) = 0;
};

} // namespace cppcrudbp::domain
