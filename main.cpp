#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "Parse.hpp"
#include "Write.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
  doctest::Context context;

  context.applyCommandLine(argc, argv);

  int test_result = context.run();

  if (context.shouldExit()) {
    return test_result;
  }

  int client_result = 0;

  std::string file_name;
  std::cout << "Enter file: ";
  std::cin >> file_name;

  std::ifstream file(file_name);

  std::stringstream buffer;
  buffer << file.rdbuf();

  int generation_count = 1;
  std::cout << "Enter number of generations to calculate: ";
  std::cin >> generation_count;

  for (int count = 0; count < generation_count; count++) {
    auto grid = Life::parse(buffer.str());

    grid.tick();

    const auto next_generation = Life::write(grid);
    std::cout << next_generation << std::endl;

    buffer.str("");
    buffer.clear();
    buffer << next_generation;

    sleep(1);
  }

  return test_result + client_result;
}