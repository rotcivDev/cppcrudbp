#include "application/user_dto.h"
#include "domain/user.h"
#include "infrastructure/postgre_user_repository.h"
#include <iostream>
#include <vector>

#include "common/db_connection.h"

namespace cppcrudbp::infrastructure {
PostgreUserRepository::PostgreUserRepository(
    const std::shared_ptr<cppcrudbp::common::DBConnection> &conn)
    : db_connection_(conn) {}

bool PostgreUserRepository::createUser(
    const application::CreateUserRequest &user) {
  try {
    const auto conn = db_connection_->getConnection();
    pqxx::work txn(*conn);
    txn.exec_params("INSERT INTO users (name, email) VALUES ($1, $2)",
                    user.name, user.email);
    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error creating user: " << e.what() << '\n';
    return false;
  }
}

std::optional<application::UserResponse>
PostgreUserRepository::getUserById(int id) {
  try {
    const auto conn = db_connection_->getConnection();
    pqxx::work txn(*conn);
    pqxx::result res =
        txn.exec_params("SELECT id, name, email FROM users WHERE id = $1", id);

    if (res.empty())
      return std::nullopt;

    const auto &row = res[0];
    application::UserResponse user;
    user.id = row["id"].as<int>();
    user.name = row["name"].as<std::string>();
    user.email = row["email"].as<std::string>();
    return user;
  } catch (const std::exception &e) {
    std::cerr << "Error fetching user: " << e.what() << '\n';
    return std::nullopt;
  }
}

std::vector<application::UserResponse> PostgreUserRepository::getAllUsers() {
  std::vector<application::UserResponse> users;
  try {
    const auto conn = db_connection_->getConnection();
    pqxx::work txn(*conn);
    pqxx::result res = txn.exec("SELECT id, name, email FROM users");

    for (const auto &row : res) {
      application::UserResponse user;
      user.id = row["id"].as<int>();
      user.name = row["name"].as<std::string>();
      user.email = row["email"].as<std::string>();
      users.push_back(user);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error retrieving users: " << e.what() << '\n';
  }
  return users;
}

bool PostgreUserRepository::updateUser(const domain::User &user) {
  try {
    const auto conn = db_connection_->getConnection();
    pqxx::work txn(*conn);
    txn.exec_params("UPDATE users SET name = $1, email = $2 WHERE id = $3",
                    user.name, user.email, user.id);
    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error updating user: " << e.what() << '\n';
    return false;
  }
}

bool PostgreUserRepository::deleteUser(int id) {
  try {
    const auto conn = db_connection_->getConnection();
    pqxx::work txn(*conn);
    txn.exec_params("DELETE FROM users WHERE id = $1", id);
    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error deleting user: " << e.what() << '\n';
    return false;
  }
}

} // namespace cppcrudbp::infrastructure
