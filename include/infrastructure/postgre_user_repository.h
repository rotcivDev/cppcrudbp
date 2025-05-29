#pragma once

#include "application/user_dto.h"
#include "domain/user.h"
#include "domain/user_repository.h"
#include <memory>
#include <pqxx/pqxx>

#include "common/db_connection.h"

namespace cppcrudbp::infrastructure {

class PostgreUserRepository : public cppcrudbp::domain::IUserRepository {
public:
  explicit PostgreUserRepository(
      const std::shared_ptr<cppcrudbp::common::DBConnection> &conn);
  bool createUser(const application::CreateUserRequest &user) override;
  std::optional<application::UserResponse> getUserById(int id) override;
  std::vector<application::UserResponse> getAllUsers() override;
  bool updateUser(const cppcrudbp::domain::User &user) override;
  bool deleteUser(int id) override;

private:
  std::shared_ptr<common::DBConnection> db_connection_;
};

} // namespace cppcrudbp::infrastructure
