#include "application/user_service.h"
#include "common/db_connection.h"
#include "infrastructure/postgre_user_repository.h"
#include "presentation/cli.h"
#include <iostream>
#include <memory>

int main(const int argc, char *argv[]) {
  try {
    // Create dependencies
    auto db_connection = std::make_shared<cppcrudbp::common::DBConnection>(
        "postgresql://user:pass@127.0.0.1:5432/cppcrudbp");
    auto user_repository =
        std::make_shared<cppcrudbp::infrastructure::PostgreUserRepository>(
            db_connection);
    auto user_service =
        std::make_shared<cppcrudbp::application::UserService>(user_repository);
    const auto cli = std::make_shared<cppcrudbp::cli::CliAdapter>(user_service);

    cli->run();

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
