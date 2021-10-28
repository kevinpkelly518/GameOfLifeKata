#include "Parse.hpp"

#include "Cell.hpp"
#include "Exception.hpp"
#include "Grid.hpp"

#include <algorithm>
#include <sstream>
#include <utility>


namespace {


struct Header {
  const int generation;
  const int rows;
  const int cols;
};

template<typename Exception>
int str_to_int(const std::string& str) {
  try {
    return std::stoi(str);
  } catch (const std::invalid_argument& e) {
    throw Exception();
  }
}

int parse_generation(const std::string& line) {
  if (line.substr(0, 11) != "Generation ") {
    throw Life::ParseGenerationException();
  }

  const std::string generation = line.substr(11);

  if (!std::all_of(generation.begin(), generation.end(), ::isdigit)) {
    throw Life::ParseGenerationException();
  }

  return str_to_int<Life::ParseGenerationException>(generation);
}

bool invalid_size(const std::string& line) {
  return line.size() != 3 || line[1] != ' ';
}

std::pair<int, int> parse_size(const std::string& line) {
  const std::string row = line.substr(0, line.find(" "));

  if (!std::all_of(row.begin(), row.end(), ::isdigit)) {
    throw Life::ParseSizeException();
  }

  const std::string col = line.substr(line.find(" ") + 1);

  if (!std::all_of(col.begin(), col.end(), ::isdigit)) {
    throw Life::ParseSizeException();
  }

  return std::make_pair(
    str_to_int<Life::ParseSizeException>(row),
    str_to_int<Life::ParseSizeException>(col)
  );
}

Header parse_header(std::istringstream& iss) {
  std::string line;

  if (!std::getline(iss, line)) {
    throw Life::ParseGenerationException();
  }

  const auto generation = parse_generation(line);

  if (!std::getline(iss, line)) {
    throw Life::ParseSizeException();
  }

  const auto grid_size = parse_size(line);

  return Header{generation, grid_size.first, grid_size.second};
}

Life::State* parse_state(const char& character) {
  if (character != '.' && character != '*') {
    throw Life::ParseGridException();
  }

  if (character == '*') {
    return new Life::AliveState();
  }

  return new Life::DeadState();
}

class GridParser {
public:
  GridParser(int rows, int cols) : rows(rows), cols(cols), grid(rows, cols) {}

  Life::Grid parse(std::istringstream& iss) {
    std::string line;
    unsigned int line_count = 0;

    while (std::getline(iss, line)) {
      parse_line(line_count, line);
      line_count++;
    }

    if (line_count != rows) {
      throw Life::ParseGridException();
    }

    return grid;
  }

private:
  const unsigned int rows;
  const unsigned int cols;
  Life::Grid grid;

  void parse_line(int line_count, const std::string& line) {
    if (line.size() != cols) {
      throw Life::ParseGridException();
    }

    for (size_t i = 0; i < line.size(); i++) {
      parse_cell(line_count, i, line[i]);
    }
  }

  void parse_cell(int row, int col, const char& character) {
    if (character != '.' && character != '*') {
      throw Life::ParseGridException();
    }

    if (character == '*') {
      grid(row, col).set_state(new Life::AliveState());
    }
  }
};

Life::Grid parse_grid(std::istringstream& iss, unsigned int rows, unsigned int cols) {
  GridParser parser(rows, cols);
  auto grid = parser.parse(iss);
  grid.update();

  return grid;
}


} // end namespace


namespace Life {


Grid parse(const std::string& input) {
  std::istringstream iss(input);

  const auto header = parse_header(iss);
  auto grid = parse_grid(iss, header.rows, header.cols);
  grid.set_generation(header.generation);

  return grid;
}


} // end namespace