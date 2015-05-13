// doubledispatch
/*
  Demonstrates a simple example for double dispatching.

  "In Software Engineering, double dispatch is a mechanism that dispatches 
  a function call to different concrete functions depending on the runtime 
  types of multiple objects involved in the call. A related concept is 
  multimethods. In most object-oriented systems, the concrete function that 
  is called from a function call in the code depends on the dynamic type of 
  a single object and therefore they are known as single dispatch calls, or 
  simply virtual function calls."

  Typical scenarios are multiple dependencies, so one dependencies referes 
  to the base class another to a looser relation, e.g. a passed parameter 
  type. Furthermore there might be possibilities to use templates, too.

  The problem is that, while virtual functions are dispatched dynamically 
  in C++, function overloading is done statically.

  (idea http://en.wikipedia.org/wiki/Double_dispatching)


  If, later, a new derived class is added, the virtual functions might be 
  reimplemented easily and might be added to the used containers implicitely.
  double dispatching is more than virtual functions and uses two vtables.

  (More Effective C++ / 31 / Meyers)


  Double Dispatching uses TWO forms of polymorphism, therefore 'double' (?): 
  - function polymorphism (parameters vary, functions have the same name)
  - virtual function polymorphism (inheritance and virtual functions)

  A double dipatched function is a polymorphic virtual function.
//*/


#include <iostream>


class SpaceFighter_t
{};


class StarDestroyer_t 
  : public SpaceFighter_t
{};


class Asteroid_t
{
public:
  virtual void collideWith( SpaceFighter_t& tieFighter)
  {
    std::cout << "\tAsteroid hit the Tie Fighter.\n";
  }

  virtual void collideWith( StarDestroyer_t& superStarDestroyer)
  {
    std::cout << "\tAsteroid hit the Super Star Destroyer.\n";
  }
};


class ExplodingAsteroid_t : public Asteroid_t
{
public:
  void collideWith( SpaceFighter_t& tieFighter) 
  {
    std::cout << "\tExploding Asteroid hit a Tie Fighter.\n";
  }

  void collideWith( StarDestroyer_t& superStarDestroyer)
  {
    std::cout << "\tExploding Asteroid hit a Super Star Destroyer.\n";
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  SpaceFighter_t tieFighter;
  StarDestroyer_t superStarDestroyer;

  Asteroid_t asteroid;
  ExplodingAsteroid_t exploding;

  asteroid.collideWith( tieFighter);
  asteroid.collideWith( superStarDestroyer);
  exploding.collideWith( tieFighter);
  exploding.collideWith( superStarDestroyer);

  std::cout << "\n...assignment...\n\n";
  Asteroid_t *ptr = &exploding;

  ptr->collideWith( tieFighter);
  exploding.collideWith( tieFighter);  
  std::cout << "...or (should be equal -> virtual)\n";
  ptr->collideWith( superStarDestroyer);
  exploding.collideWith( superStarDestroyer);

  cout << "READY.\n";
  return 0;
}

