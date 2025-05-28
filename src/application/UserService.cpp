#include "application/user_service.h"

namespace cppcrudbp::application {

UserService::UserService(
    std::shared_ptr<cppcrudbp::domain::IUserRepository> repository)
    : repository_(std::move(repository)) {}

bool UserService::createUser(const cppcrudbp::domain::User &user) {
  return repository_->createUser(user);
}

std::optional<cppcrudbp::domain::User> UserService::getUserById(int id) {
  return repository_->getUserById(id);
}

std::vector<cppcrudbp::domain::User> UserService::getAllUsers() {
  return repository_->getAllUsers();
}

bool UserService::updateUser(const cppcrudbp::domain::User &user) {
  return repository_->updateUser(user);
}

bool UserService::deleteUser(int id) { return repository_->deleteUser(id); }

} // namespace cppcrudbp::application
