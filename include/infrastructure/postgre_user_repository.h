#pragma once

#include "domain/user.h"
#include "domain/user_repository.h"
#include <memory>
#include <pqxx/pqxx>

namespace cppcrudbp::infrastructure {

class PostgreUserRepository : public cppcrudbp::domain::IUserRepository {
public:
  explicit PostgreUserRepository(std::shared_ptr<pqxx::connection> conn);
  bool createUser(const cppcrudbp::domain::User &user) override;
  std::optional<cppcrudbp::domain::User> getUserById(int id) override;
  std::vector<cppcrudbp::domain::User> getAllUsers() override;
  bool updateUser(const cppcrudbp::domain::User &user) override;
  bool deleteUser(int id) override;

private:
  std::shared_ptr<pqxx::connection> connection_;
};

} // namespace cppcrudbp::infrastructure
