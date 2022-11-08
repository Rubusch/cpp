// observer.cpp
/*
  Define a one-to-many dependency between objects so that when one
  object changes state, all its dependents are notified and updated
  automatically.

  +---------------------+                                       observers +---------------------+
  | Subject             |------------------------------------------------>| Observer            |
  +=====================+                                                 +=====================+
  | attach(Observer)    |  +-------------------------+                    | update()            |
  | detach(Observer)    |  | for all o in observers{ | \                  +---------------------+
  | notify()  o - - - - - -|   o->update();          +--+                         /_\
  +---------------------+  | }                          |                          |
           /_\             +----------------------------+                          |
            |                                                                      |
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
*/


#include <algorithm>
#include <iostream>
#include <list>


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

  explicit State(const State &state) : val_(state.val_), str_(state.str_) {}

  State(int val, std::string s) : val_(val), str_(s) {}

  friend std::ostream &operator<<(std::ostream &, State &);
};

std::ostream &operator<<(std::ostream &os, State &state)
{
  return os << ">> State (Originator): int = " << state.val_
            << ", string = " << state.str_;
}


struct Observer {
  virtual ~Observer() {}
  virtual void update() = 0;
};


class Subject
{
private:
  std::list< Observer * > lst_;

public:
  virtual ~Subject() {}

  virtual void attach(Observer *pObserver)
  {
    if (!pObserver)
      return;
    lst_.push_back(pObserver);
  }

  virtual void detach(Observer *pObserver)
  {
    if (!pObserver)
      return;
    lst_.remove(pObserver);
  }

  virtual void notify()
  {
    std::for_each(lst_.begin(), lst_.end(), std::mem_fun(&Observer::update));
  }
};


class ConcreteSubject : public Subject
{
private:
  State *subjectState_;

public:
  ConcreteSubject() : subjectState_(NULL)
  {
    try {
      subjectState_ = new State(666, "murder");
    } catch (std::bad_alloc &e) {
      std::cerr << "Allocation of state failed!\n";
      std::exit(-1);
    }
  }

  ~ConcreteSubject()
  {
    delete subjectState_;
    subjectState_ = NULL;
  }

  State *getState() const { return subjectState_; }

  void setState(State *pState)
  {
    if (!pState)
      return;

    if (subjectState_) {
      delete subjectState_;
      subjectState_ = NULL;
    }
    subjectState_ = new State(*pState);
  }
};


class ConcreteObserver : public Observer
{
private:
  State *observerState_;
  const ConcreteSubject *subject_;

public:
  ConcreteObserver(const ConcreteSubject &pSubject)
      : observerState_(NULL), subject_(&pSubject)
  {
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
    delete observerState_;
    observerState_ = NULL;
  }

  void update()
  {
    if (observerState_) {
      delete observerState_;
      observerState_ = NULL;
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
