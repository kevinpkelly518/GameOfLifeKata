#pragma once

#include <memory>


namespace Life {


class Cell;

class State {
public:
  virtual void tick(Cell*) = 0;
  virtual bool is_alive() const = 0;

  std::unique_ptr<State> clone() const;

protected:
  virtual State* clone_impl() const = 0;
};

class AliveState : public State {
public:
  void tick(Cell* cell) override;
  bool is_alive() const override;

protected:
  State* clone_impl() const override;
};

class DeadState : public State {
public:
  void tick(Cell* cell) override;
  bool is_alive() const override;

protected:
  State* clone_impl() const override;
};

class Cell {
public:
  ~Cell() = default;
  Cell(State* state);
  Cell(const Cell& other);
  Cell(Cell&& other) = default;
  Cell& operator=(const Cell& other);
  Cell& operator=(Cell&& other) = default;

  void tick();
  bool is_alive() const;
  void add_live_neighbor();
  int get_live_neighbors_count() const;
  void set_state(State* state);

private:
  std::unique_ptr<State> state;
  int live_neighbors_count = 0;
};


} // end namespace Life