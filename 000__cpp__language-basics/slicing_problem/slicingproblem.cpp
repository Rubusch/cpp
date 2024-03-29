// slicingproblem.cpp
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
  Base(int initVar) : var_(initVar) {}
  virtual ~Base() { cout << "CALLED: ~Base()" << endl; }; // needed for Derived
  int getVar() { return var_; }
  virtual string me() { return "BASE"; } // to be overwritten
};


class Derived : public Base
{
private:
  int newVar_;

public:
  Derived(int initVar, int initNewVar) : Base(initVar), newVar_(initNewVar) {}
  ~Derived() { cout << "CALLED: ~Derived()" << endl; }; // not needed
  int getNewVar() { return newVar_; }
  string me() { return "DERIVED"; } // virtual, too, overwriting Base::me()
};


/*
  some main
//*/
int main()
{
  int baseVar = 1;
  cout << "Base base(" << baseVar << ");" << endl;
  Base base(baseVar);
  cout << "> base.getVar() = " << base.getVar() << endl;
  cout << endl;

  int derivedVar = 2, derivedNewVar = 22;
  cout << "Derived derived(" << derivedVar << ", " << derivedNewVar << ");"
       << endl;
  Derived derived(derivedVar, derivedNewVar);
  cout << "> derived.getVar() = " << derived.getVar() << endl;
  cout << "> derived.getNewVar() = " << derived.getNewVar() << endl;
  cout << "> derived.me() = " << derived.me()
       << endl; // overwritten virtual base implementation
  cout << endl;

  cout << "Base base = derived; ";
  base = derived; // assignment (slicing)
  cout << "// ...after assignment:" << endl;
  cout << "> base.getVar() = " << base.getVar() << endl;
  cout
      << "> (crazy_cast< Derived >(base)).getNewVar() = FAIL" /*<< (crazy_cast<
                                                                 Derived
                                                                 >(base)).getNewVar()*/
      << endl; // SLICING - FAILES!
  // ...in static implementation Derived-only functions/values are sliced off!
  cout << "> base.me() = " << base.me() << endl; // SLICING - this is Base!!!
  cout << endl;

  /*
    Slicing Problem:
    slicing occurs with static information, at (simple) assignment from Derived
    to Base object, Derived qualities are cut off!

    slicing with dynamic instance at assignment to pointer to Base, keeps all
    information of the dynamic instance and can be accessed with a down cast
  */

  int dynBaseVar = 3;
  cout << "Base* pBase = new Base(" << dynBaseVar << ");" << endl;
  Base *pBase = new Base(dynBaseVar); /* NB: usually take shared_ptr/unique_ptr instead of new/delete */
  cout << "> pBase->getVar() = " << pBase->getVar() << endl;
  cout << endl;

  int dynDerivedVar = 4, dynDerivedNewVar = 44;
  cout << "Derived* pDerived = new Derived(" << dynDerivedVar << ", "
       << dynDerivedNewVar << ");" << endl;
  Derived *pDerived = new Derived(dynDerivedVar, dynDerivedNewVar); /* NB: usually take shared_ptr/unique_ptr instead of new/delete */
  cout << "> pDerived->getVar() = " << pDerived->getVar() << endl;
  cout << "> pDerived->getNewVar() = " << pDerived->getNewVar() << endl;
  cout << "> pDerived->me() = " << pDerived->me()
       << endl; // overwritten virtual base implementation
  cout << endl;

  cout << "Base *pNewBase = pDerived;";
  Base *pNewBase = pDerived; // assignment
  cout << "// ...after assignment:" << endl;
  cout << "> pNewBase->getVar() = " << pNewBase->getVar() << endl;
  cout << "> pNewBase->getVar() = " << pNewBase->getVar() << endl;
  cout << "> (dynamic_cast< Derived* >(pNewBase))->getNewVar() = "
       << (dynamic_cast< Derived * >(pNewBase))->getNewVar() << endl;
  // SLICING - derived-only funcs are hidden to Base pointer (dynamic) -> works
  // with down-cast!
  cout << "> pNewBase->me() = " << pNewBase->me() << endl;
  // overwritten virtual base implementation, and working correctly for dynamic
  // assignment (Derrived's output with Base pointer)
  cout << endl;


  /*
    int derivedVarP = 3, derivedNewVarP = 33;
    cout << "Base* pBase = new Derived(" << derivedVarP << ", " <<
  derivedNewVarP << ");" << endl; Base* pBase = new Derived(derivedVarP,
  derivedNewVarP); cout << "> pBase->getVar() = " << pBase->getVar() << endl;
    cout << "> pBase->me() = " << pBase->me() << endl; // overwritten virtual
  base implementation cout << "> pBase->getNewVar() = " << (dynamic_cast<
  Derived* >(pBase))->getNewVar() << endl; // derived-only funcs are hidden to
  Base pointer -> FAILS, needs down-cast! cout << endl;
  // */

  cout << "delete" << endl;
  delete pBase;
  delete pDerived;

  cout << "READY." << endl;
  return 0;
}
