#include "common/db_connection.h"
#include "presentation/cli.h"
#include <iostream>
#include <memory>

int main(const int argc, char *argv[]) {
  try {
    // Create dependencies
    auto db_connection = std::make_shared<cppcrudbp::common::DBConnection>(
        "postgresql://user:pass@pgdb:5432/cppcrudbp");

    const auto cli = std::make_shared<cppcrudbp::cli::CLI>();

    // Run the CLI
    if (argc > 1) {
      cli->run(argc, argv);
    } else {
      cli->interactive();
    }

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
