#pragma once

#include "application/user_dto.h"
#include "domain/user.h"
#include "domain/user_repository.h"
#include <memory>
#include <optional>
#include <vector>

namespace cppcrudbp::application {

class UserService {
public:
  explicit UserService(
      std::shared_ptr<cppcrudbp::domain::IUserRepository> repository);

  bool createUser(const application::CreateUserRequest &user);
  std::optional<application::UserResponse> getUserById(int id);
  std::vector<application::UserResponse> getAllUsers();
  bool updateUser(const application::UpdateUserRequest &user);
  bool deleteUser(int id);

private:
  std::shared_ptr<cppcrudbp::domain::IUserRepository> repository_;
};

} // namespace cppcrudbp::application
