// example.cpp
/*
  search algorithm

  elements MUST be sorted before search algorithm!

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>


/*
  class Foobar
//*/
class Foobar
{
public:
  Foobar(int id) : id_(id) {}

  int getId() const { return id_; }

private:
  const int id_;
};


/*
  functor for compare operation
//*/
class id_compare
  : public std::binary_function< Foobar, int, bool >
{
public:
  bool operator()(const Foobar& foo, int idx) const
  {
    return foo.getId() < idx;
  }
};


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  Foobar arr[] = { Foobar(10), Foobar(20), Foobar(30), Foobar(40) };
  cout << endl;

  cout << "lower_bound() - 25 or next to\n";
  Foobar* ptr = lower_bound(arr, arr+4, 25, id_compare());
  if(ptr != arr+4){
    cout << ptr->getId() << endl;
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
