#pragma once

#include "application/user_dto.h"
#include "application/user_service.h"
#include <optional>
#include <string>
#include <vector>

namespace cppcrudbp::cli {

/**
 * @brief CLI Adapter for interacting with the User Service.
 *
 * This class provides a command-line interface for CRUD operations on users.
 * It parses commands and arguments from stdin and prints results to stdout.
 */
class CliAdapter {
public:
  /**
   * @brief Constructor for CliAdapter.
   * @param userService A unique_ptr to a UserService instance.
   * This demonstrates dependency injection.
   */
  explicit CliAdapter(
      std::shared_ptr<cppcrudbp::application::UserService> userService);

  /**
   * @brief Starts the CLI application loop.
   * Continuously reads commands from stdin until 'exit' is entered.
   */
  void run();

private:
  std::shared_ptr<cppcrudbp::application::UserService> userService_;

  /**
   * @brief Displays the available commands to the user.
   */
  void showHelp() const;

  /**
   * @brief Processes a single command entered by the user.
   * @param commandLine The full command line string entered by the user.
   */
  void processCommand(const std::string &commandLine);

  // --- Command Handlers ---
  void handleCreateUser(const std::vector<std::string> &args);
  void handleGetUserById(const std::vector<std::string> &args);
  void handleGetAllUsers();
  void handleUpdateUser(const std::vector<std::string> &args);
  void handleDeleteUser(const std::vector<std::string> &args);

  // --- Helper for JSON simulation (same as in HttpUserController) ---
  // In a real CLI, you might prompt for fields or use a proper JSON parser.
  cppcrudbp::application::CreateUserRequest
  parseCreateUserRequest(const std::string &json);
  cppcrudbp::application::UpdateUserRequest
  parseUpdateUserRequest(const std::string &json, int id);
  std::string serializeUserResponse(
      const std::optional<application::UserResponse> &response);
  std::string serializeUserResponses(
      const std::vector<cppcrudbp::application::UserResponse> &responses);
};
} // namespace cppcrudbp::cli
