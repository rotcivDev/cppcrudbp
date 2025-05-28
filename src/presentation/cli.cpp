#include "presentation/cli.h"
#include "domain/domain_exception.h" // Include custom exceptions
#include <iostream>
#include <limits> // For numeric_limits
#include <regex>  // For basic email validation (example)
#include <sstream>

// --- Simple JSON Simulation (replace with nlohmann/json or similar) ---
// This is a very crude simulation for demonstration purposes.
// In a real project, you would use a robust JSON parsing library.
namespace {
// Helper to extract a value from a simple "key": "value" JSON string
std::string extractJsonValue(const std::string &json, const std::string &key) {
  std::string search_key = "\"" + key + "\":\"";
  size_t start_pos = json.find(search_key);
  if (start_pos == std::string::npos) {
    return ""; // Key not found
  }
  start_pos += search_key.length();
  size_t end_pos = json.find("\"", start_pos);
  if (end_pos == std::string::npos) {
    return ""; // Malformed JSON
  }
  return json.substr(start_pos, end_pos - start_pos);
}

// Helper to extract an int value from a simple "key": number JSON string
std::optional<int> extractJsonIntValue(const std::string &json,
                                       const std::string &key) {
  std::string search_key = "\"" + key + "\":";
  size_t start_pos = json.find(search_key);
  if (start_pos == std::string::npos) {
    return std::nullopt; // Key not found
  }
  start_pos += search_key.length();
  size_t end_pos =
      json.find_first_of(",}", start_pos); // Find comma or closing brace
  if (end_pos == std::string::npos) {
    return std::nullopt; // Malformed JSON
  }
  std::string num_str = json.substr(start_pos, end_pos - start_pos);
  try {
    return std::stoi(num_str);
  } catch (const std::exception &) {
    return std::nullopt; // Not a valid integer
  }
}

} // anonymous namespace

namespace cppcrudbp::cli {

CliAdapter::CliAdapter(
    std::unique_ptr<cppcrudbp::application::UserService> userService)
    : userService_(std::move(userService)) {
  if (!userService_) {
    throw std::invalid_argument("UserService cannot be null.");
  }
}

void CliAdapter::run() {
  std::string commandLine;
  showHelp();
  std::cout << "\nEnter command (type 'help' for options, 'exit' to quit):"
            << std::endl;

  while (true) {
    std::cout << "> ";
    std::getline(std::cin, commandLine);

    // Clear potential error flags and ignore remaining characters in the buffer
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "Input error. Please try again." << std::endl;
      continue;
    }

    if (commandLine == "exit") {
      std::cout << "Exiting CLI. Goodbye!" << std::endl;
      break;
    } else if (commandLine == "help") {
      showHelp();
    } else {
      processCommand(commandLine);
    }
  }
}

void CliAdapter::showHelp() const {
  std::cout << "\n--- Available Commands ---" << std::endl;
  std::cout << "  create <json_data>          - Create a new user. Example: "
               "create {\"name\":\"Alice\",\"email\":\"alice@example.com\"}"
            << std::endl;
  std::cout
      << "  get <id>                    - Get a user by ID. Example: get 1"
      << std::endl;
  std::cout << "  get-all                     - Get all users." << std::endl;
  std::cout << "  update <id> <json_data>     - Update an existing user. "
               "Example: update 1 {\"name\":\"Alice "
               "Updated\",\"email\":\"alice.updated@example.com\"}"
            << std::endl;
  std::cout << "  delete <id>                 - Delete a user by ID. Example: "
               "delete 1"
            << std::endl;
  std::cout << "  help                        - Show this help message."
            << std::endl;
  std::cout << "  exit                        - Exit the application."
            << std::endl;
  std::cout << "--------------------------" << std::endl;
}

void CliAdapter::processCommand(const std::string &commandLine) {
  std::stringstream ss(commandLine);
  std::string command;
  ss >> command;

  std::vector<std::string> args;
  std::string arg;
  // Read remaining arguments, handling potential JSON string
  while (ss >> std::ws &&
         std::getline(ss, arg, '{')) { // Read until '{' to capture JSON
    if (!arg.empty()) {
      std::stringstream arg_ss(arg);
      std::string token;
      while (arg_ss >> token) {
        args.push_back(token);
      }
    }
    if (ss.good()) { // If '{' was found, put it back and read the rest as JSON
      std::string json_part =
          "{" + std::string(std::istreambuf_iterator<char>(ss), {});
      args.push_back(json_part);
      break; // Stop processing arguments, the rest is JSON
    }
  }

  try {
    if (command == "create") {
      handleCreateUser(args);
    } else if (command == "get") {
      handleGetUserById(args);
    } else if (command == "get-all") {
      handleGetAllUsers();
    } else if (command == "update") {
      handleUpdateUser(args);
    } else if (command == "delete") {
      handleDeleteUser(args);
    } else {
      std::cout << "Unknown command: '" << command
                << "'. Type 'help' for options." << std::endl;
    }
  } catch (const cppcrudbp::domain::DomainException &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cerr << "Input Error: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
  }
}

void CliAdapter::handleCreateUser(const std::vector<std::string> &args) {
  if (args.empty()) {
    throw std::invalid_argument("Usage: create <json_data>");
  }
  std::string jsonBody =
      args[0]; // Assuming JSON is the first (and only) arg for simplicity
  cppcrudbp::application::CreateUserRequest request =
      parseCreateUserRequest(jsonBody);
  cppcrudbp::application::UserResponse response =
      userService_->createUser(request);
  std::cout << "User created: " << serializeUserResponse(response) << std::endl;
}

void CliAdapter::handleGetUserById(const std::vector<std::string> &args) {
  if (args.empty()) {
    throw std::invalid_argument("Usage: get <id>");
  }
  int id = std::stoi(args[0]);
  cppcrudbp::application::UserResponse response = userService_->getUserById(id);
  std::cout << "User found: " << serializeUserResponse(response) << std::endl;
}

void CliAdapter::handleGetAllUsers() {
  std::vector<cppcrudbp::application::UserResponse> responses =
      userService_->getAllUsers();
  if (responses.empty()) {
    std::cout << "No users found." << std::endl;
  } else {
    std::cout << "All users: " << serializeUserResponses(responses)
              << std::endl;
  }
}

void CliAdapter::handleUpdateUser(const std::vector<std::string> &args) {
  if (args.size() < 2) {
    throw std::invalid_argument("Usage: update <id> <json_data>");
  }
  int id = std::stoi(args[0]);
  std::string jsonBody = args[1]; // Assuming JSON is the second arg
  cppcrudbp::application::UpdateUserRequest request =
      parseUpdateUserRequest(jsonBody, id);
  cppcrudbp::application::UserResponse response =
      userService_->updateUser(request);
  std::cout << "User updated: " << serializeUserResponse(response) << std::endl;
}

void CliAdapter::handleDeleteUser(const std::vector<std::string> &args) {
  if (args.empty()) {
    throw std::invalid_argument("Usage: delete <id>");
  }
  int id = std::stoi(args[0]);
  bool deleted = userService_->deleteUser(id);
  if (deleted) {
    std::cout << "User with ID " << id << " deleted successfully." << std::endl;
  } else {
    std::cout << "User with ID " << id << " not found." << std::endl;
  }
}

// --- Helper for JSON simulation (copied from HttpUserController.cpp for
// consistency) ---
cppcrudbp::application::CreateUserRequest
CliAdapter::parseCreateUserRequest(const std::string &json) {
  cppcrudbp::application::CreateUserRequest request;
  request.name = extractJsonValue(json, "name");
  request.email = extractJsonValue(json, "email");

  if (request.name.empty() || request.email.empty()) {
    throw std::invalid_argument(
        "Name and email are required in JSON for user creation.");
  }
  std::regex email_regex(R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)");
  if (!std::regex_match(request.email, email_regex)) {
    throw std::invalid_argument("Invalid email format.");
  }
  return request;
}

cppcrudbp::application::UpdateUserRequest
CliAdapter::parseUpdateUserRequest(const std::string &json, int id) {
  cppcrudbp::application::UpdateUserRequest request;
  request.id = id;
  request.name = extractJsonValue(json, "name");
  request.email = extractJsonValue(json, "email");

  if (request.name.empty() || request.email.empty()) {
    throw std::invalid_argument(
        "Name and email are required in JSON for user update.");
  }
  std::regex email_regex(R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)");
  if (!std::regex_match(request.email, email_regex)) {
    throw std::invalid_argument("Invalid email format.");
  }
  return request;
}

std::string CliAdapter::serializeUserResponse(
    const cppcrudbp::application::UserResponse &response) {
  std::stringstream ss;
  ss << "{\"id\":" << response.id << ",\"name\":\"" << response.name
     << "\",\"email\":\"" << response.email << "\"}";
  return ss.str();
}

std::string CliAdapter::serializeUserResponses(
    const std::vector<cppcrudbp::application::UserResponse> &responses) {
  std::stringstream ss;
  ss << "[";
  for (size_t i = 0; i < responses.size(); ++i) {
    ss << serializeUserResponse(responses[i]);
    if (i < responses.size() - 1) {
      ss << ",";
    }
  }
  ss << "]";
  return ss.str();
}

} // namespace cppcrudbp::cli
