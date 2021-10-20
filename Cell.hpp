#pragma once

#include <memory>


namespace Life {


class Cell;

class State {
public:
  virtual void tick(Cell*) = 0;
  virtual bool is_alive() const = 0;
};

class AliveState : public State {
public:
  void tick(Cell* cell) override;
  bool is_alive() const override;
};

class DeadState : public State {
public:
  void tick(Cell* cell) override;
  bool is_alive() const override;
};

class Cell {
public:
  Cell(State* state);

  void tick();
  bool is_alive() const;
  void add_live_neighbor();
  int get_live_neighbors_count() const;
  void set_state(State* state);

private:
  std::unique_ptr<State> m_state;
  int m_live_neighbors_count = 0;
};


} // end namespace Life