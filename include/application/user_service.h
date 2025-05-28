#pragma once

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

  bool createUser(const cppcrudbp::domain::User &user);
  std::optional<cppcrudbp::domain::User> getUserById(int id);
  std::vector<cppcrudbp::domain::User> getAllUsers();
  bool updateUser(const cppcrudbp::domain::User &user);
  bool deleteUser(int id);

private:
  std::shared_ptr<cppcrudbp::domain::IUserRepository> repository_;
};

} // namespace cppcrudbp::application
