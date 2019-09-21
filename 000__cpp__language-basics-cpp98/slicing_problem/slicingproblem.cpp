//slicingproblem.cpp
/*
  assignment of a derrived class object into an object of its base class slices
  off the members of the derrived parts in the resulting object of class base
//*/

#include <iostream>
#include <string>

using namespace std;


class Base
{
protected:
  int var_;

public:
  Base(int initVar) :var_(initVar) {}
  virtual ~Base(){}; // needed for Derived
  int getVar() { return var_; }
  virtual string me() { return "BASE"; } // to be overwritten
};


class Derived
: public Base
{
private:
  int newVar_;

public:
  Derived(int initVar, int initNewVar) : Base(initVar), newVar_(initNewVar) {}
  int getNewVar() { return newVar_; }
  virtual string me() { return "DERIVED"; }
};


/*
  some main
//*/
int main()
{
  int baseVar = 1;
  cout << "Base base(" << baseVar << ");" << endl;
  Base base(baseVar);
  cout << endl;

  cout << "> base:" << endl
       << "> base.getVar() = " << base.getVar() << endl;
  cout << endl;

  int derivedVar = 2, derivedNewVar = 22;
  cout << "Derived derived(" << derivedVar << ", " << derivedNewVar << ");" << endl;
  Derived derived(derivedVar, derivedNewVar);
  cout << endl;

  cout << "> derived:" << endl;
  cout << "> derived.getVar() = " << derived.getVar() << endl;
  cout << "> derived.getNewVar() = " << derived.getNewVar() << endl;
  cout << "> derived.me() = " << derived.me() << endl;
  cout << endl;

/*
  Slicing Problem:
  slicing occurs here since the features of the derived class's
  object are not copied, though this kind of copy is allowed
*/
  cout << "Base base = derived; ";
  base = derived;
  cout << "// ...after slicing (base changed), but the Derived's attributes are \"sliced off\":" << endl << endl;

  cout << "> base:" << endl
       << "> base.getVar() = " << base.getVar() << endl;
  cout << endl;

  cout << "> derived:" << endl;
  cout << "> derived.getVar() = " << derived.getVar() << endl;
  cout << "> derived.getNewVar() = " << derived.getNewVar() << endl;
  cout << "> derived.me() = " << derived.me() << endl;
  cout << endl;

  int derivedVarP = 3, derivedNewVarP = 33;
  cout << "Base* pBase = new Derived(" << derivedVarP << ", " << derivedNewVarP << ");" << endl;
  Base* pBase = new Derived(derivedVarP, derivedNewVarP);

  cout << "> base ptr init to derived:" << endl;
  cout << "> pBase->getVar() = " << pBase->getVar() << endl;
  cout << "> pBase->me() = " << pBase->me() << endl;
  cout << "> pBase->getNewVar() = " << (dynamic_cast< Derived* >(pBase))->getNewVar() << endl; // SLICING -> FAILS, needs down-cast!
  cout << endl;

  delete pBase;

  cout << "READY." << endl;
  return 0;
}
