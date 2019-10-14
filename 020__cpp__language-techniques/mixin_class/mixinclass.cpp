// mixin.cpp
/*
  "a mixin is a class that provides a certain functionality to be inherited
  by a subclass, but is not meant to stand alone. Inheriting from a mixin is
  not a form of specialization but is rather a means to collect functionality.
  A class may inherit most or all of its functionality by inheriting from
  one or more mixins through multiple inheritance."

  (http://en.wikipedia.org/wiki/Mixin)

  Example of mixin classes are Policies or Type Traits.
//*/


#include <iostream>


class DefaultImpulseEngine
{
public:
  void launch() { std::cout << "\t\tImpulseEngine::launch()\n"; }
};


class WarpEngine
{
public:
  void launch() { std::cout << "\t\tWarpEngine::launch()\n"; }
};


/* entinge type as Mixin class (via template) */
template < typename Engine_t = DefaultImpulseEngine >
class StarShip
{
private:
  Engine_t engine;

public:
  void start()
  {
    std::cout << "\tStarShip starts..\n";
    engine.launch();
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init types..\n";
  typedef StarShip<> CheapSpaceShip_t;

  typedef StarShip< WarpEngine > DeLuxeSpaceShip_t;

  cout << "build ships..\n";
  CheapSpaceShip_t cheapShip;
  DeLuxeSpaceShip_t deLuxeShip;

  cout << "start ships..\n";
  cheapShip.start();

  cout << endl;
  deLuxeShip.start();

  cout << "READY.\n";
  return 0;
}
