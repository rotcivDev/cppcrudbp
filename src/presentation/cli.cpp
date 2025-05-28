#include "presentation/cli.h"
#include <iomanip>
#include <iostream>

namespace cppcrudbp {
namespace cli {

void CLI::run(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "No command provided. Entering interactive mode...\n";
    interactive();
    return;
  }

  std::string command = argv[1];
  std::vector<std::string> args;
  for (int i = 2; i < argc; ++i) {
    args.emplace_back(argv[i]);
  }
}

void CLI::interactive() {
  std::cout << "cpp crud boilerplate CLI - Interactive Mode\n";
  std::cout << "Type 'help' for available commands. Type 'exit' to quit.\n";

  std::string line;
  while (true) {
    std::cout << "> ";
    if (!std::getline(std::cin, line)) {
      break; // EOF or input error
    }

    if (line.empty()) {
      continue;
    }

    std::vector<std::string> tokens = parseCommandLine(line);
    if (tokens.empty()) {
      continue;
    }

    std::string command = tokens[0];
    tokens.erase(tokens.begin()); // Remove the command from the arguments

    if (command == "exit" || command == "quit") {
      break;
    }
  }
}

std::vector<std::string> CLI::parseCommandLine(const std::string &line) {
  std::istringstream stream(line);
  std::string token;
  std::vector<std::string> tokens;

  while (stream >> std::quoted(token)) {
    tokens.push_back(token);
  }

  return tokens;
}

} // namespace cli
} // namespace cppcrudbp
