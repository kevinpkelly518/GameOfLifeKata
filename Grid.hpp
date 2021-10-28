#pragma once

#include "Cell.hpp"

#include <vector>


namespace Life {


class Grid {
public:
  Grid(int rows, int cols);

  void update();
  int size() const;
  int get_generation() const;
  void set_generation(int generation);
  int get_rows() const;
  int get_columns() const;

  Cell& operator()(int row, int col);
  const Cell& operator()(int row, int col) const;

private:
  bool valid_row(int row) const;
  bool valid_column(int col) const;
  void add_live_neighbor(int row, int col);

  const int rows;
  const int cols;
  std::vector<Cell> cells;
  int generation;
};


} // end namespace Life
