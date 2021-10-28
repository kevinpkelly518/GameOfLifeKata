#include "Cell.hpp"


namespace Life {


std::unique_ptr<State> State::clone() const {
  return std::unique_ptr<State>(clone_impl());
}

void AliveState::tick(Cell* cell) {
  if (cell->get_live_neighbors_count() < 2 || cell->get_live_neighbors_count() > 3) {
    cell->set_state(new DeadState());
  }
}

bool AliveState::is_alive() const {
  return true;
}

State* AliveState::clone_impl() const {
  return new AliveState(*this);
}

void DeadState::tick(Cell* cell) {
  if (cell->get_live_neighbors_count() == 3) {
    cell->set_state(new AliveState());
  }
}

bool DeadState::is_alive() const {
  return false;
}

State* DeadState::clone_impl() const {
  return new DeadState(*this);
}

Cell::Cell(State* state) : state(std::unique_ptr<State>(state)) {}

Cell::Cell(const Cell& other) : state(other.state->clone()) {}

Cell& Cell::operator=(const Cell& other) {
  state = other.state->clone();

  return *this;
}

void Cell::tick() {
  state->tick(this);
}

bool Cell::is_alive() const {
  return state->is_alive();
}

void Cell::add_live_neighbor() {
  live_neighbors_count++;
}

int Cell::get_live_neighbors_count() const {
  return live_neighbors_count;
}

void Cell::set_state(State* s) {
  state = std::unique_ptr<State>(s);
}


} // end namespace Life