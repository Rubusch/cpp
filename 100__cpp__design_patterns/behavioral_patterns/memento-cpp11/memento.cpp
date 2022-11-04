// memento.cpp
/*
  Without violating encapsulation, capture and externalize an objects internal
  state so that the object can be restored to this state later.

  +---------------------+           +---------------------+   memento +---------------------+
  | Originator          |---------->| Memento             |<--------<>| Caretaker           |
  +=====================+           +=====================+           +---------------------+
  | setMemento(Memento) o---+       | getState() : State  |
  | createMemento()   o |   |       | setState( State)    |
  +-------------------|-+   |       +---------------------+
  | state : State     | |   |
  +-------------------|-+   |
                      |     |
                      |     |  +------------------------+\
                      |     +--| state = m->getSate()   +-+
                      |        |                          |
                      |        +--------------------------+
                      |        +-----------------------------+\
                      +--------| return new Memento(state)   +-+
                               |                               |
                               +-------------------------------+

  (GoF, 1995)
*/

#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>


class Originator;


/*
  State - helper
*/
class State
{
private:
  int i_;
  std::string str_;

public:
  State() : i_(0), str_("") {}

  explicit State(const State &state)  = default;

  State(int i, std::string s) : i_(i), str_(std::move(s)) {}

  friend std::ostream &operator<<(std::ostream &, State &);
};

std::ostream &operator<<(std::ostream &os, State &state)
{
  return os << ">> State (Originator): int = " << state.i_
            << ", string = " << state.str_;
}


/*
  Memento

  - stores internal state of the Originator object. The memento
  may store as much or as little of the originator's internal
  state as necessary at its Originator's discretion.

  - protects against access by ojects other than the originator.
  Mementos have effectively two interfaces. Caretaker sees a
  narrow interface to the Memento - it can only pass the memento
  to other objects. Originator, in contrast, sees a wide
  interface, one that lets it access all the data necessary to
  restore itself to its previous state. Ideally, only the
  Originator that produced the memento would be permitted to
  access the memento's internal state.
*/
class Memento
{
private:
  State *state_;

public:
  virtual ~Memento()
  {
    std::cout << "\tMemento::~Memento() - dtor\n";
    delete state_;
    state_ = nullptr;
  }

private:
  // private members accessible only to Originator
  friend class Originator;
  Memento() { std::cout << "\tMemento::Memento() - ctor\n"; }

  void setState(State *state)
  {
    std::cout << "\tMemento::setState( State*);\n";
    try {
      state_ = new State(*state);
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation in Memento failed!\n";
      std::exit(-1);
    }
  }

  State *getState() const
  {
    std::cout << "\tMemento::getState()\n";
    return state_;
  }
};


/*
  Originator / Constraint Solver

  - creates a memento containing a snapshot of its current internal state
  - uses the memento to restore its internal state
*/
class Originator
{
private:
  State *state_;

public:
  Originator()
  {
    std::cout << "\tOriginator::Originator() - ctor\n";
    try {
      state_ = new State(123, "foobar");
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation of State failed!\n";
      std::exit(-2);
    }
  }

  ~Originator()
  {
    std::cout << "\tOriginator::~Originator() - dtor\n";
    delete state_;
    state_ = nullptr;
  }

  Memento *createMemento()
  {
    std::cout << "\tOriginator::createMemento()\n";

    // check
    if (!state_)
      return nullptr;
    std::cout << *state_ << std::endl;

    /*
      memento is instantiated on the heap, in order to control the
      creation and destruction of the object.
      Never return local variables (only new/delete enables to explicitly
      control this)
    */
    Memento *pMemento = nullptr;
    try {
      pMemento = new Memento();
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation of Memento failed!\n";
      std::exit(-3);
    }

    // copies deep copy to the memento
    pMemento->setState(state_);

    return pMemento;
  }

  // not a setter - activates memento's settings!
  void setMemento(const Memento *memento)
  {
    std::cout << "\tOriginator::setMemento(const Memento*);\n";
    if (!memento->getState())
      return;

    if (state_) {
      delete state_;
      state_ = nullptr;
    }

    // set the state, as deep copy
    try {
      state_ = new State(*memento->getState());
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation failed setting the Memento!\n";
      std::exit(-4);
    }

    // clean up!
    delete memento;
    memento = nullptr;

    std::cout << *state_ << std::endl;
  }

  void changeState()
  {
    std::cout << "\t\tchanges in Originator...\n";
    std::cout << *state_ << std::endl;

    std::cout << "\t\tdeleting...\n";
    delete state_;
    state_ = nullptr;

    std::cout << "\t\treallocating...\n";
    try {
      state_ = new State(777, "something odd...");
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation failed somewhere!\n";
      std::exit(-5);
    }
    std::cout << *state_ << std::endl;
    std::cout << "\t\tchanges done...\n";
  }
};


/*
  main / Caretaker (mementos are passive!)

  - is responsible for the memento's safekeeping
  - never operates on or examines the contents of a memento
*/
int main()
{
  using namespace std;

  // init
  cout << "init\n";
  Memento *pMemento = nullptr;
  Originator anOriginator;
  cout << endl;

  // caretaker: create the memento (Caretaker allocates Memento!)
  pMemento = anOriginator.createMemento();
  cout << endl;

  // do something
  anOriginator.changeState();
  cout << endl;

  // caretaker: set the menento (Caretaker deletes Memento!)
  // to e.g. reset the Originator to the state before
  anOriginator.setMemento(pMemento);
  pMemento = nullptr;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
