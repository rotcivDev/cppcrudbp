#pragma once

#include "domain/user.h"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace cppcrudbp::application {

/**
 * @brief DTO for creating a new User.
 * Used as input to the UserService.
 */
struct CreateUserRequest {
  std::string name;
  std::string email;
};

/**
 * @brief DTO for updating an existing User.
 * Used as input to the UserService.
 */
struct UpdateUserRequest {
  int id;
  std::string name;
  std::string email;
};

/**
 * @brief DTO for representing User data in responses.
 * Used as output from the UserService to the Presentation layer.
 */
struct UserResponse {
  int id;
  std::string name;
  std::string email;
};

/**
 * @brief Helper function to convert a Domain::Entities::User to a UserResponse
 * DTO.
 * @param user The User entity to convert.
 * @return A UserResponse DTO.
 */
inline UserResponse toUserResponse(const cppcrudbp::domain::User &user) {
  // Ensure the user has an ID before converting to DTO for response
  if (!user.id) {
    // This should ideally not happen if the entity is coming from a 'saved'
    // state
    throw std::runtime_error(
        "Cannot convert User to UserResponse: User ID is not set.");
  }
  return UserResponse{user.id, user.name, user.email};
}

} // namespace cppcrudbp::application
