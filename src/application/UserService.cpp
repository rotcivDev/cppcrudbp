#include "application/user_dto.h"
#include "application/user_service.h"

namespace cppcrudbp::application {

UserService::UserService(
    std::shared_ptr<cppcrudbp::domain::IUserRepository> repository)
    : repository_(std::move(repository)) {}

bool UserService::createUser(const application::CreateUserRequest &user) {
  return repository_->createUser(user);
}

std::optional<application::UserResponse> UserService::getUserById(int id) {
  return repository_->getUserById(id);
}

std::vector<application::UserResponse> UserService::getAllUsers() {
  return repository_->getAllUsers();
}

bool UserService::updateUser(const application::UpdateUserRequest &user) {
  domain::User usr_;
  usr_.id = user.id;
  usr_.email = user.email;
  usr_.name = user.name;
  return repository_->updateUser(usr_);
}

bool UserService::deleteUser(int id) { return repository_->deleteUser(id); }

} // namespace cppcrudbp::application
