#include "../include/Logger.hpp"
#include <iostream>
#include <string>
#include <thread>

int main(int args, char **argv) {
  // check that we have a name to dump
  if (args < 2) {
    std::cout << "No app to read Please add the app and try again\n"
              << std::endl;
    return 1;
  }
  // create a logger object
  logger log(argv[1]);
  // get the messages from the log
  std::vector<std::string> messages = log.read_all();
  for (auto message : messages) {
    std::cout << message << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  // we are done
  return 0;
}

// to run this code use the following command:
// g++ -std=c++11 -o ../bin/Log_Dumper Log_Dumper.cpp Logger.cpp -lsqlite3