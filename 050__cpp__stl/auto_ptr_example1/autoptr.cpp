// autoptr.cpp
/*
  auto_ptr

  - auto_ptr is not deep copyable
  - auto_ptr is not deep assignable
  - auto_ptr won't work with STL containers because of the above
  - don't use 2 auto_ptr pointing to the same object

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <memory>


/*
//*/
class Foobar
{
private:
  int val_;

public:
  Foobar(int val = 0) : val_(val)
  {
    std::cout << "Foobar::Foobar " << this << std::endl;
  }

  ~Foobar() { std::cout << "Foobar::~Foobar " << this << std::endl; }

  void func() { std::cout << "Foobar::func" << std::endl; }

  friend std::ostream &operator<<(std::ostream &os, const Foobar &foo)
  {
    return os << foo.val_;
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  auto_ptr< Foobar > ap_a(new Foobar(1)), ap_b(new Foobar(2));
  cout << endl;

  cout << "call a member function\n";
  ap_a->func();
  cout << endl;

  cout << "assignment - NEVER DO THIS!\n";
  ap_b = ap_a;
  cout << endl;

  cout << "dereference - *ap_b:\n" << *ap_b << endl;
  cout << endl;

  cout << "auto_ptr::reset()\n";
  ap_a.reset(new Foobar(3));
  cout << endl;

  cout << "re-assign auto_ptr to normal pointer, and call func()\n";
  Foobar *pFoobar1 = ap_a.get();
  pFoobar1->func();
  cout << endl;

  cout << "release ap_a, assign to another \'real\'-pointer and try to delete "
          "that\n";
  Foobar *pFoobar2 = ap_a.release();
  delete pFoobar2;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
