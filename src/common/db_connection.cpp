#include "common/db_connection.h"
#include <stdexcept>
#include <string>

namespace cppcrudbp::common {

DBConnection::DBConnection(const std::string &connection_string)
    : connection_string_(connection_string), conn_(nullptr) {
  try {
    conn_ = new pqxx::connection(connection_string_);
    if (!conn_->is_open()) {
      throw std::runtime_error("Failed to open database connection.");
    }
  } catch (const std::exception &e) {
    throw std::runtime_error(std::string("DBConnection error: ") + e.what());
  }
}

DBConnection::~DBConnection() {
  if (conn_) {
    // conn_->disconnect();
    delete conn_;
    conn_ = nullptr;
  }
}

pqxx::connection *DBConnection::getConnection() const { return conn_; }

} // namespace cppcrudbp
