// observer.cpp
/*
  Define a one-to-many dependency between objects so that
  when one object changes state, all its dependents are
  notified and updated automatically.

  +---------------------+                                       observers +---------------------+
  | Subject             |------------------------------------------------>| Observer            |
  +=====================+                                                 +=====================+
  | attach(Observer)    |  +-------------------------+                    | update()            |
  | detach(Observer)    |  | for all o in observers{ | \                  +---------------------+
  | notify()  o - - - - - -|   o->update();          +--+                          /_\
  +---------------------+  | }                          |                           |
           /_\             +----------------------------+                           |
            |                                                                       |
            |                                                             +---------------------+
            |                                                             | ConcreteObserver    |
  +---------------------+                                         subject +=====================+
  | ConcreteSubject     |<------------------------------------------------| update()         o  |
  +=====================+      +----------------------+                   +------------------ --+
  | getState() o - - - - - - - | return subjectState; +-+                 | observerState    |  |
  | setState()          |      |                        |                 +------------------ --+
  +---------------------+      +------------------------+                                    |
  | subjectState_       |
  +---------------------+                                                                    |
                                                                     +-------------------------+
                                                                     | observerState =         | \
                                                                     |   subject->getState()   +--+
                                                                     |                            |
                                                                     +----------------------------+
  (GoF, 1995)


  NB: in terms of Makefile... (cyclic dependency situation)

  This pattern can be a challenging pain-in-the.. talking about a
  setup in make/cmake. In case Observer is setup by template< T > and
  ConcreteObserver will instanciate Observer< ConreteSubject >. On the
  other side if ConcreteSubject needs to access functionality of
  ConcreteObserver, then easily a cyclic vice-versa dependency may
  result in terms of instantiation. For not discussing being good or
  bad having a cyclic dependency in this context, there is a solution
  for make / cmake to handle this.

  -> separate every declaration and definition by a file .cpp and .hpp, respectively
  -> put every class into a separate file pair
  -> ConcreteSubject.hpp: forward declaration "class ConcreteObserver;"
  -> ConcreteObserver.hpp: forward declaration "class ConcreteSubject;"

  When this is not done cleanly a very nasty "ConcreteObserver has
  incomplete type" error may result, no matter if the .hpp file was
  included or not.

  Another approach might be to solve the cyclic dependency by
  instantiating the abstract classes of the others, then using
  downcasts when working with the concrete. If this downcasting should
  be avoided the template approach with forward declaration (and
  cyclic declaration dependency) is the alternative.
*/


#include <algorithm>
#include <iostream>
#include <list>
#include <utility>


class Subject;
class Observer;
class ConcreteSubject;
class ConcreteObserver;


/*
  State
*/
class State
{
private:
  int val_;
  std::string str_;

public:
  State() : val_(0), str_("") {}

  explicit State(const State &state)  = default;

  State(int val, std::string s) : val_(val), str_(std::move(s)) {}

  friend std::ostream &operator<<(std::ostream &, State &);
};

std::ostream &operator<<(std::ostream &os, State &state)
{
  return os << ">> State (Originator): int = " << state.val_
            << ", string = " << state.str_;
}


/*
  Observer

  - defines an updating interface for objects that should be notified
    of changes in a subject.
*/
class Observer
{
public:
  virtual ~Observer() = default;
  virtual void update() = 0;
};


/*
  Subject

  - knows its observers. Any number of Observer objects may obserer a
    subject.
  - provides an interface for attaching and detaching Observer objects.
*/
class Subject
{
protected:
  std::list< Observer * > lst_;

public:
  virtual ~Subject() = default;

  void attach(Observer *pObserver)
  {
    std::cout << "\tSubject::attach( Observer)\n";
    if (!pObserver)
      return;
    lst_.push_back(pObserver);
  }

  void detach(Observer *pObserver)
  {
    std::cout << "\tSubject::detach( Observer)\n";
    if (!pObserver)
      return;
    lst_.remove(pObserver);
  }

  void notify()
  {
    std::cout << "\tSubject::notify()\n";
    std::for_each(lst_.begin(), lst_.end(), std::mem_fun(&Observer::update));
  }
};


/*
  ConcreteSubject

  - stores state of interest to ConcreteObserver objects.
  - sends a notification to its observers when its state changes.
*/
class ConcreteSubject : public Subject
{
private:
  State *subjectState_;

public:
  ConcreteSubject() : subjectState_(nullptr)
  {
    std::cout << "\tConcreteSubject::ConcreteSubject() - ctor\n";
    try {
      subjectState_ = new State(666, "murder");
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation of state failed!\n";
      std::exit(-1);
    }
  }

  ~ConcreteSubject()
  {
    std::cout << "\tConcreteSubject::~ConcreteSubject() - dtor\n";
    delete subjectState_;
    subjectState_ = nullptr;
  }

  State *getState() const
  {
    std::cout << "\tConcreteSubject::getState()\n";
    return subjectState_;
  }

  void setState(State *pState)
  {
    std::cout << "\tConcreteSubject::setState()\n";
    if (!pState)
      return;

    if (subjectState_) {
      delete subjectState_;
      subjectState_ = nullptr;
    }
    subjectState_ = new State(*pState);
  }
};


/*
  ConcreteObserver

  - maintains a reference to a ConcreteSubject object.
  - stores state that should stay consistent with the subject's
  - implements the Observer updating interface to keep its state
    consistent with the subject's
*/
class ConcreteObserver : public Observer
{
private:
  State *observerState_;
  const ConcreteSubject *subject_;

public:
  ConcreteObserver(const ConcreteSubject &pSubject)
      : observerState_(nullptr), subject_(&pSubject)
  {
    std::cout << "\tConcreteObserver::ConcreteObserver() - ctor\n";
    try {
      observerState_ = new State(999, "redrum");
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation of observer state failed!\n";
      std::exit(-2);
    }

    std::cout << *observerState_ << std::endl;
  }

  ~ConcreteObserver()
  {
    std::cout << "\tConcreteObserver::~ConcreteObserver() - dtor\n";
    delete observerState_;
    observerState_ = nullptr;
  }

  void update()
  {
    std::cout << "\tConcreteObserver::update()\n";
    if (observerState_) {
      delete observerState_;
      observerState_ = nullptr;
    }
    observerState_ = new State(*subject_->getState());

    std::cout << *observerState_ << std::endl;
  }
};


/*
  main
*/
int main()
{
  using namespace std;

  cout << "init\n";
  ConcreteSubject subject;
  ConcreteObserver observer_a(subject), observer_b(subject);
  subject.attach(&observer_a);
  subject.attach(&observer_b);
  cout << endl;

  cout << "notify subject and update observers\n";
  subject.notify();
  cout << endl;

  cout << "READY.\n";
  return 0;
}
