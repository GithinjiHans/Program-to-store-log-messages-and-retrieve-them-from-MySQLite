#include <iostream>
#include <sqlite3.h>
#include <vector>
#include "../include/Logger.hpp"

logger::logger(std::string app_name) {
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
  std::string sql = "CREATE TABLE Log_Generator("
                    "MESSAGE           VARCHAR(255)    NOT NULL,"
                    "TIMESTAMP         VARCHAR(255)   NOT NULL);";
  rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
}
// The destructor closes the log file.
logger::~logger() {
  // close the database
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  rc = sqlite3_open("Log.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    exit(1);
  }
  sqlite3_close(db);
}

void logger::write(std::string message) {
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
  // insert a row
  std::string sql = "INSERT INTO Log_Generator (MESSAGE,TIMESTAMP) "
                    "VALUES ('" +
                    message + "', datetime('now'));";
  rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
}

std::vector<std::string> logger::read_all() {
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
  // read all rows
  std::string sql = "SELECT * from Log_Generator;";
  std::vector<std::string> messages;
  rc = sqlite3_exec(
      db, sql.c_str(),
      [](void *data, int argc, char **argv, char **azColName) {
        std::vector<std::string> *messages = (std::vector<std::string> *)data;
        std::string message;
        for (int i = 0; i < argc; i++) {
          message += azColName[i];
          message += ": ";
          message += argv[i] ? argv[i] : "NULL";
          message += "";
        }
        messages->push_back(message);
        return 0;
      },
      &messages, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return messages;
}
