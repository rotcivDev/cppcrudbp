#pragma once

#include <pqxx/pqxx>
#include <string>

namespace cppcrudbp::common {

class DBConnection {
public:
  explicit DBConnection(const std::string &connection_string);
  ~DBConnection();

  [[nodiscard]] pqxx::connection* getConnection() const;
  void disconnect(); // Explicitly disconnects the database

private:
  std::string connection_string_;
  pqxx::connection *conn_;
};

} // namespace cppcrudbp::common
