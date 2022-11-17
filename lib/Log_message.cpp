#include "../include/Log_message.hpp"

log_message::log_message(std::string message, std::string timestamp) {
  // open a connection to the database
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open("Log.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    exit(1);
  }
  // log the message
  std::string sql = "INSERT INTO Log_Generator (MESSAGE,TIMESTAMP) "
                    "VALUES ('" +
                    message + "', '" + timestamp + "');";
  rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
}
// The destructor closes the log file.
log_message::~log_message() {
  // close the database
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  sqlite3_close(db);
}
// The get_message() method returns the log message.
std::string log_message::get_message() {
  // open a connection to the database
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open("Log.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    exit(1);
  }
  // create a table
  std::string sql = "SELECT MESSAGE FROM Log_Generator;";
  rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return "message";
}
// The get_timestamp() method returns the timestamp for the log message.
void log_message::get_timestamp() {
  // open a connection to the database
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open("Log.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    exit(1);
  }
  // create a table
  std::string sql = "SELECT TIMESTAMP FROM Log_Generator;";
  rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
}
// The get_timestamp_string() method returns the timestamp for the log message
// as a string.
std::string log_message::get_timestamp_string() {
  // open a connection to the database
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open("Log.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    exit(1);
  }
  // create a table
  std::string sql = "SELECT TIMESTAMP FROM Log_Generator;";
  rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return sql;
}
