#pragma once

#include "application/user_dto.h"
#include "user.h"
#include <optional>
#include <vector>

namespace cppcrudbp::domain {

class IUserRepository {
public:
  virtual ~IUserRepository() = default;

  virtual bool createUser(const application::CreateUserRequest &user) = 0;
  virtual std::optional<application::UserResponse> getUserById(int id) = 0;
  virtual std::vector<application::UserResponse> getAllUsers() = 0;
  virtual bool updateUser(const User &user) = 0;
  virtual bool deleteUser(int id) = 0;
};

} // namespace cppcrudbp::domain
