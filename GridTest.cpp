#include "doctest.h"

#include "Exception.hpp"
#include "Grid.hpp"

#include <string>

TEST_CASE("Grid Invalid Index") {
  Life::Grid grid(1, 1);

  CHECK_THROWS_AS(grid(-1, 0), Life::InvalidIndexException);
  CHECK_THROWS_AS(grid(0, -1), Life::InvalidIndexException);
  CHECK_THROWS_AS(grid(1, 0), Life::InvalidIndexException);
  CHECK_THROWS_AS(grid(0, 1), Life::InvalidIndexException);
}

TEST_CASE("Default All Dead") {
  Life::Grid grid(2, 2);

  CHECK(!grid(0, 0).is_alive());
  CHECK(!grid(0, 1).is_alive());
  CHECK(!grid(1, 0).is_alive());
  CHECK(!grid(1, 1).is_alive());
}

TEST_CASE("Grid Update Live Neighbors") {
  Life::Grid grid(2, 2);
  grid(0, 0).set_state(new Life::AliveState());

  grid.update();

  CHECK(grid(0, 0).get_live_neighbors_count() == 0);
  CHECK(grid(0, 1).get_live_neighbors_count() == 1);
  CHECK(grid(1, 0).get_live_neighbors_count() == 1);
  CHECK(grid(1, 1).get_live_neighbors_count() == 1);
}
