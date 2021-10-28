#include "doctest.h"

#include "Exception.hpp"
#include "Parse.hpp"

#include <string>
#include <vector>


namespace {


std::vector<std::string> generation_exceptions{
  {
    ""
  },
  {
    "1 1\n"
  },
  {
    "Generation a\n"
    "1 1\n"
    ".\n"
  },
  {
    "Generation 1a\n"
    "1 1\n"
    ".\n"
  },
  {
    "Generationa1\n"
    "1 1\n"
    ".\n"
  }
};

std::vector<std::string> size_exceptions{
  {
    "Generation 1\n"
  },
  {
    "Generation 1\n"
    "a 1\n"
    ".\n"
  },
  {
    "Generation 1\n"
    "1 a\n"
    ".\n"
  },
  {
    "Generation 1\n"
    "1 1 a\n"
    ".\n"
  },
  {
    "Generation 1\n"
    "1a1\n"
    ".\n"
  }
};

std::vector<std::string> grid_exceptions{
  {
    "Generation 1\n"
    "1 1\n"
  },
  {
    "Generation 1\n"
    "1 1\n"
    "a\n"
  },
  {
    "Generation 1\n"
    "1 2\n"
    ".a\n"
  },
  {
    "Generation 1\n"
    "1 2\n"
    ".\n"
  },
  {
    "Generation 1\n"
    "2 1\n"
    ".\n"
  },
  {
    "Generation 1\n"
    "1 1\n"
    "..\n"
  }
  ,
  {
    "Generation 1\n"
    "1 1\n"
    ".\n"
    ".\n"
  }
};


} // end namespace


TEST_CASE("Generation") {
  SUBCASE("Generation Number") {
    const auto grid = Life::parse(
      "Generation 2\n"
      "1 1\n"
      ".\n"
    );

    CHECK(grid.get_generation() == 2);
  }

  SUBCASE("Generation Double Digits") {
    const auto grid = Life::parse(
      "Generation 10\n"
      "1 1\n"
      ".\n"
    );

    CHECK(grid.get_generation() == 10);
  }

  SUBCASE("Exceptions") {
    for (const auto& generation : generation_exceptions) {
      CHECK_THROWS_AS(Life::parse(generation), Life::ParseGenerationException);
    }
  }
}

TEST_CASE("Size") {
  SUBCASE("Grid Size 1") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "1 1\n"
      ".\n"
    );

    CHECK(grid.get_rows() == 1);
    CHECK(grid.get_columns() == 1);
  }

  SUBCASE("Grid Size 2") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "2 1\n"
      ".\n"
      ".\n"
    );

    CHECK(grid.get_rows() == 2);
    CHECK(grid.get_columns() == 1);
  }

  SUBCASE("Grid Size 2") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "1 2\n"
      "..\n"
    );

    CHECK(grid.get_rows() == 1);
    CHECK(grid.get_columns() == 2);
  }

  SUBCASE("Grid Size 4") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "2 2\n"
      "..\n"
      "..\n"
    );

    CHECK(grid.get_rows() == 2);
    CHECK(grid.get_columns() == 2);
  }

  SUBCASE("Size Double Digits") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "1 10\n"
      "..........\n"
    );

    CHECK(grid.get_rows() == 1);
    CHECK(grid.get_columns() == 10);
  }

  SUBCASE("Exceptions") {
    for (const auto& size : size_exceptions) {
      CHECK_THROWS_AS(Life::parse(size), Life::ParseSizeException);
    }
  }
}

TEST_CASE("Grid") {
  SUBCASE("Single Dead") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "1 1\n"
      ".\n"
    );

    CHECK(!grid(0, 0).is_alive());
  }

  SUBCASE("Single Alive") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "1 1\n"
      "*\n"
    );

    CHECK(grid(0, 0).is_alive());
  }

  SUBCASE("Two Columns") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "1 2\n"
      ".*\n"
    );
    
    CHECK(!grid(0, 0).is_alive());
    CHECK(grid(0, 1).is_alive());
  }

  SUBCASE("Two Rows") {
    const auto grid = Life::parse(
      "Generation 1\n"
      "2 1\n"
      ".\n"
      "*\n"
    );
    
    CHECK(!grid(0, 0).is_alive());
    CHECK(grid(1, 0).is_alive());
  }

  SUBCASE("Exceptions") {
    for (const auto& grid : grid_exceptions) {
      CHECK_THROWS_AS(Life::parse(grid), Life::ParseGridException);
    }
  }
}