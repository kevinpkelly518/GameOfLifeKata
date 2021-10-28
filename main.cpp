#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "Parse.hpp"
#include "Write.hpp"

#include <fstream>
#include <iostream>
#include <sstream>


namespace {




} // end namespace


int main(int argc, char** argv) {
  doctest::Context context;

  context.applyCommandLine(argc, argv);

  int test_result = context.run();

  if (context.shouldExit()) {
    return test_result;
  }

  int client_result = 0;

  std::ifstream file("Grids/kata");
  std::stringstream buffer;
  buffer << file.rdbuf();

  auto grid = Life::parse(buffer.str());
  grid.tick();
  std::cout << Life::write(grid) << std::endl;

  return test_result + client_result;
}