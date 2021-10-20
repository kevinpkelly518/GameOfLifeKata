#include "doctest.h"

#include "Cell.hpp"

#include <memory>

TEST_CASE("Live State Transitions") {
  Life::Cell cell(new Life::AliveState());

  SUBCASE("Next generation survives") {
    SUBCASE("Two live neighbors") {
      cell.add_live_neighbor();
      cell.add_live_neighbor();
    }

    SUBCASE("Three live neighbors") {
      cell.add_live_neighbor();
      cell.add_live_neighbor();
      cell.add_live_neighbor();
    }

    cell.tick();
    CHECK(cell.is_alive());
  }

  SUBCASE("Next generation dies") {
    SUBCASE("Default all neighbors are dead") {}

    SUBCASE("One live neighbor") {
      cell.add_live_neighbor();
    }

    SUBCASE("Four live neighbors") {
      cell.add_live_neighbor();
      cell.add_live_neighbor();
      cell.add_live_neighbor();
      cell.add_live_neighbor();
    }

    cell.tick();
    CHECK(!cell.is_alive());
  }
}

TEST_CASE("Dead State Transitions") {
  Life::Cell cell(new Life::DeadState());
  
  SUBCASE("Next generation lives") {
    cell.add_live_neighbor();
    cell.add_live_neighbor();
    cell.add_live_neighbor();
    cell.tick();
    CHECK(cell.is_alive());
  }

  SUBCASE("Next generation dies") {
    SUBCASE("Default all neighbors are dead") {}

    SUBCASE("One live neighbor") {
      cell.add_live_neighbor();
    }

    SUBCASE("Two live neighbors") {
      cell.add_live_neighbor();
      cell.add_live_neighbor();
    }

    SUBCASE("Four live neighbors") {
      cell.add_live_neighbor();
      cell.add_live_neighbor();
      cell.add_live_neighbor();
      cell.add_live_neighbor();
    }

    cell.tick();
    CHECK(!cell.is_alive());
  }
}
