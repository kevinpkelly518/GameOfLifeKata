#include "doctest.h"

#include "Cell.hpp"
#include "Grid.hpp"
#include "Write.hpp"

TEST_CASE("Single Cell") {
  Life::Grid grid(1, 1);
  
  SUBCASE("Default Generation 1") {
    CHECK(Life::write(grid) ==
      "Generation 1\n"
      "1 1\n"
      ".\n"
    );
  }

  SUBCASE("Set Generation") {
    grid.set_generation(2);

    CHECK(Life::write(grid) == 
      "Generation 2\n"
      "1 1\n"
      ".\n"
    );
  }

  SUBCASE("Set Alive") {
    grid(0, 0).set_state(new Life::AliveState());

    CHECK(Life::write(grid) ==
      "Generation 1\n"
      "1 1\n"
      "*\n"
    );
  }
}

TEST_CASE("Multiple Cells") {
  Life::Grid grid(2, 2);

  CHECK(Life::write(grid) ==
    "Generation 1\n"
    "2 2\n"
    "..\n"
    "..\n"
  );
}