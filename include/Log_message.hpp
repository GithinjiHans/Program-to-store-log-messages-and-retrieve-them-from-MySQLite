#include <iostream>
#include <sqlite3.h>

class log_message {
public:
  log_message(std::string message, std::string timestamp);
  ~log_message();
  std::string get_message();
  void get_timestamp();
  std::string get_timestamp_string();
};
