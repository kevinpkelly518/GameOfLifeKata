#include "Write.hpp"

#include <sstream>

namespace {


std::string write_header(Life::Grid grid) {
  std::stringstream ss;

  ss << "Generation " << grid.get_generation() << std::endl;
  ss << grid.get_rows() << " " << grid.get_columns() << std::endl;

  return ss.str();
}

std::string write_grid(Life::Grid grid) {
  std::stringstream ss;

  for (int row = 0; row < grid.get_rows(); row++) {
    for (int col = 0; col < grid.get_columns(); col++) {
      ss << (grid(row, col).is_alive() ? "*" : ".");
    }

    ss << std::endl;
  }

  return ss.str();
}


}  // end namespace


namespace Life {


std::string write(Grid grid) {
  std::stringstream ss;

  ss << write_header(grid) << write_grid(grid);

  return ss.str();
}


} // end namespace Life