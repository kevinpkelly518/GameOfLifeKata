#include "Cell.hpp"


namespace Life {


void AliveState::tick(Cell* cell) {
  if (cell->get_live_neighbors_count() < 2 || cell->get_live_neighbors_count() > 3) {
    cell->set_state(new DeadState());
  }
}

bool AliveState::is_alive() const {
  return true;
}

void DeadState::tick(Cell* cell) {
  if (cell->get_live_neighbors_count() == 3) {
    cell->set_state(new AliveState());
  }
}

bool DeadState::is_alive() const {
  return false;
}

Cell::Cell(State* state) : m_state(std::unique_ptr<State>(state)) {}

void Cell::tick() {
  m_state->tick(this);
}

bool Cell::is_alive() const {
  return m_state->is_alive();
}

void Cell::add_live_neighbor() {
  m_live_neighbors_count++;
}

int Cell::get_live_neighbors_count() const {
  return m_live_neighbors_count;
}

void Cell::set_state(State* state) {
  m_state = std::unique_ptr<State>(state);
}


} // end namespace Life