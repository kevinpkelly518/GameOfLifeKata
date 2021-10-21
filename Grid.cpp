#include "Grid.hpp"

#include "Exception.hpp"


namespace Life {


Grid::Grid(int rows, int cols) : rows(rows), cols(cols), generation(1) {
  for (int i = 0; i < rows * cols; i++) {
    cells.emplace_back(Cell(new DeadState()));
  }
}

void Grid::update() {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (cells[col + cols * row].is_alive()) {
        add_live_neighbor(row - 1, col - 1);
        add_live_neighbor(row - 1, col);
        add_live_neighbor(row - 1, col + 1);
        add_live_neighbor(row, col - 1);
        add_live_neighbor(row, col + 1);
        add_live_neighbor(row + 1, col - 1);
        add_live_neighbor(row + 1, col);
        add_live_neighbor(row + 1, col + 1);
      }
    }
  }
}

int Grid::get_generation() const {
  return generation;
}

void Grid::set_generation(int g) {
  generation = g;
}

int Grid::get_rows() const {
  return rows;
}

int Grid::get_columns() const {
  return cols;
}

int Grid::size() const {
  return cells.size();
}

Cell& Grid::operator()(int row, int col) {
  if (!valid_row(row) || !valid_column(col)) {
    throw InvalidIndexException();
  }

  return cells[col + cols * row];
}

const Cell& Grid::operator()(int row, int col) const {
  if (!valid_row(row) || !valid_column(col)) {
    throw InvalidIndexException();
  }

  return cells[col + cols * row];
}

bool Grid::valid_row(int row) const {
  return row >= 0 && row < rows;
}

bool Grid::valid_column(int col) const {
  return col >= 0 && col < cols;
}

void Grid::add_live_neighbor(int row, int col) {
  try {
    (*this)(row, col).add_live_neighbor();
  } catch (const InvalidIndexException& e) {
    return;
  }
}


} // end namespace Life
