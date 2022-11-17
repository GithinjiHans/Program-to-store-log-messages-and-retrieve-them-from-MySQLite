#include <iostream>
#include <sqlite3.h>
#include <vector>

class logger {
  private:
 std::string  app_name;
public:
  logger(std::string app_name);
  ~logger();
  void write(std::string message);
  std::vector<std::string> read_all();
};
