#include "domain/user.h"
#include "infrastructure/postgre_user_repository.h"
#include <iostream>
#include <vector>

namespace cppcrudbp::infrastructure {
PostgreUserRepository::PostgreUserRepository(
    std::shared_ptr<pqxx::connection> conn)
    : connection_(std::move(conn)) {}

bool PostgreUserRepository::createUser(const domain::User &user) {
  try {
    pqxx::work txn(*connection_);
    txn.exec_params("INSERT INTO users (name, email) VALUES ($1, $2)",
                    user.name, user.email);
    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error creating user: " << e.what() << '\n';
    return false;
  }
}

std::optional<domain::User> PostgreUserRepository::getUserById(int id) {
  try {
    pqxx::work txn(*connection_);
    pqxx::result res =
        txn.exec_params("SELECT id, name, email FROM users WHERE id = $1", id);

    if (res.empty())
      return std::nullopt;

    const auto &row = res[0];
    domain::User user;
    user.id = row["id"].as<int>();
    user.name = row["name"].as<std::string>();
    user.email = row["email"].as<std::string>();
    return user;
  } catch (const std::exception &e) {
    std::cerr << "Error fetching user: " << e.what() << '\n';
    return std::nullopt;
  }
}

std::vector<domain::User> PostgreUserRepository::getAllUsers() {
  std::vector<domain::User> users;
  try {
    pqxx::work txn(*connection_);
    pqxx::result res = txn.exec("SELECT id, name, email FROM users");

    for (const auto &row : res) {
      domain::User user;
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
    pqxx::work txn(*connection_);
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
    pqxx::work txn(*connection_);
    txn.exec_params("DELETE FROM users WHERE id = $1", id);
    txn.commit();
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Error deleting user: " << e.what() << '\n';
    return false;
  }
}

} // namespace cppcrudbp::infrastructure
