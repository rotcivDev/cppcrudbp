#pragma once

#include <memory>
#include <string>
#include <vector>

namespace cppcrudbp {
namespace cli {

class CLI {
public:
  void run(int argc, char *argv[]);
  void interactive();

private:
  std::vector<std::string> parseCommandLine(const std::string &line);
};

} // namespace cli
} // namespace cppcrudbp
