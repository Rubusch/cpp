// Main.cpp
/*
  Arrays and Assert

  Use assert to keep track for operator[]

     void assert(bool howItShouldBe)

//*/

#include <iostream>
using namespace std;
#include <assert.h>

class Someclass
{
private:
  const int SIZE;
  int *arr = nullptr;

public:
  Someclass() : SIZE(10) { arr = new int[SIZE]; };
  void set(int x, int at)
  {
    cout << "x = " << x << ", at = " << at << ", SIZE = " << SIZE << endl;
    assert(at < SIZE);
    assert(at >= 0);
    arr[at] = x;
    cout << "no Assertion" << endl;
  };
};


int main()
{
  Someclass *s = new Someclass();
  cout << "set(7, 1)" << endl;
  s->set(7, 1);
  cout << endl;

  cout << "set(7, 10)" << endl;
  s->set(7, 10);
  cout << endl;

  delete s;
};
