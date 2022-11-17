#include "../include/Log_message.hpp"
#include "../include/Logger.hpp"
#include <csignal>
#include <iostream>
#include <thread>

int main(int args, char **argv) {
  // check that we have at least one message to log
  if (args < 2) {
    std::cout << "No message to log...add message in the following format: \n"
              << "message1 message2 message3" << std::endl;
    return 1;
  }
  // create a logger object
  logger log(argv[0]);
  // create a vector of messages
  std::vector<std::string> messages;
  // add the messages to the vector
  for (int i = 1; i < args; i++) {
    messages.push_back(argv[i]);
  }
  // loop forever
  while (true) {
    // randomly select a message
    int index = rand() % messages.size();
    // write the message to the log
    log.write(messages[index]);
    // sleep for a random period of time
    int sleep_time = rand() % 10;
    // create a signal handler to catch the user pressing Ctrl+C
    signal(SIGINT, [](int signum) {
      std::cout << "Shutting down" << std::endl;
      exit(0);
    });
    std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
  }
  return 0;
}
// to compile this code use the following command:
// g++ -std=c++11 -o ./bin/Log_Generator ./src/Log_Generator.cpp ./lib/Logger.cpp -lsqlite3