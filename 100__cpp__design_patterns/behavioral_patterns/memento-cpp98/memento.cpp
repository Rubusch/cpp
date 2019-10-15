// memento.cpp
/*
  Without violating encapsulation, capture and externalize an objects internal
state so that the object can be restored to this state later.

  +---------------------+           +---------------------+  memento
+---------------------+ | Originator          |---------->| Memento
|<--------<>| Caretaker           |
  +=====================+           +=====================+
+---------------------+ | setMemento(Memento) o---+       | getState() : State |
  | createMemento()   o |   |       | setState( State)    |
  +-------------------|-+   |       +---------------------+
  | state : State     | |   |
  +-------------------|-+   |
                      |     |
                      |     |  +------------------------+\
                      |     +--| state = m->getSate()   +-+
                      |        +--------------------------+
                      |
                      |        +-----------------------------+\
                      +--------| return new Memento(state)   +-+
                               +-------------------------------+

  (GoF, 1995)
//*/

#include <cstdlib>
#include <exception>
#include <iostream>


class Originator;


class State
{
private:
  int i_;
  std::string str_;

public:
  State() : i_(0), str_("") {}

  explicit State(const State &state) : i_(state.i_), str_(state.str_) {}

  State(int i, std::string s) : i_(i), str_(s) {}

  friend std::ostream &operator<<(std::ostream &, State &);
};

std::ostream &operator<<(std::ostream &os, State &state)
{
  return os << ">> State (Originator): int = " << state.i_
            << ", string = " << state.str_;
}


class Memento
{
private:
  State *state_;

public:
  virtual ~Memento()
  {
    delete state_;
    state_ = NULL;
  }

private:
  // private members accessible only to Originator
  friend class Originator;
  Memento() {}

  void setState(State *state)
  {
    try {
      state_ = new State(*state);
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation in Memento failed!\n";
      std::exit(-1);
    }
  }

  State *getState() const { return state_; }
};


class Originator
{
private:
  State *state_;

public:
  Originator()
  {
    try {
      state_ = new State(123, "foobar");
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation of State failed!\n";
      std::exit(-2);
    }
  }

  ~Originator()
  {
    delete state_;
    state_ = NULL;
  }

  Memento *createMemento()
  {
    if (!state_)
      return NULL;
    std::cout << *state_ << std::endl;

    Memento *pMemento = NULL;
    try {
      pMemento = new Memento();
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation of Memento failed!\n";
      std::exit(-3);
    }

    pMemento->setState(state_);

    return pMemento;
  }

  // not a setter - activates memento's settings!
  void setMemento(const Memento *memento)
  {
    if (!memento->getState())
      return;

    if (state_) {
      delete state_;
      state_ = NULL;
    }

    // set the state, as deep copy
    try {
      state_ = new State(*memento->getState());
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation failed setting the Memento!\n";
      std::exit(-4);
    }

    delete memento;
    memento = NULL;

    std::cout << *state_ << std::endl;
  }

  void changeState()
  {
    std::cout << *state_ << std::endl;

    delete state_;
    state_ = NULL;

    try {
      state_ = new State(777, "something odd...");
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation failed somewhere!\n";
      std::exit(-5);
    }

    std::cout << *state_ << std::endl;
  }
};


/*
  main / Caretaker (mementos are passive!)
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  Memento *pMemento = NULL;
  Originator anOriginator;

  // create memento
  pMemento = anOriginator.createMemento();

  // do something
  anOriginator.changeState();

  // use memento
  anOriginator.setMemento(pMemento);
  pMemento = NULL;

  cout << "READY.\n";
  return 0;
}
