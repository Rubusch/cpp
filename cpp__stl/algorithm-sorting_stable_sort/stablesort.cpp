// stablesort.cpp
/*
  sorting algorithm

  stable_sort - sort a range of elements while preserving their relative order (heap sort)

                        ___ ___ ___ ___
       +---+---+---+---+---+---+---+---+- -+
  arr: | 3 | 1 | 0 | 6 | 1 | 6 | 3 | 0 |   |
       +---+---+---+---+---+---+---+---+- -+
   |
   | stable_sort(arr, arr+8)
   |
  \|/       ___     ___     ___     ___
       +---+---+---+---+---+---+---+---+- -+
  arr: | 0 | 0 | 1 | 1 | 3 | 3 | 6 | 6 |   |
       +---+---+---+---+---+---+---+---+- -+

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

using namespace std;
using namespace std::rel_ops;


/*
  Element class
//*/
class Element
{
public:
  Element(int value) : value_(value), idx_(++number_)
  {}

  friend ostream& operator<<(ostream& os, const Element& element)
  {
    return os << element.value_ << '-' << element.idx_;
  }

  bool operator<(const Element& element) const
  {
    return (value_ < element.value_);
  }

  bool operator>(const Element& element) const
  {
    return (value_ > element.value_);
  }

private:
  int value_, idx_;
  static int number_;
};

// init of static member
int Element::number_ = 0;


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  Element arr[] = { 3, 1, 0, 6, 3, 1, 0, 6 };
  copy(arr, arr+8, ostream_iterator< Element >(cout, " "));
  cout << endl << endl;

  cout << "stable_sort() - ascending order\n";
  stable_sort(arr, arr+8);
  copy(arr, arr+8, ostream_iterator< Element >(cout, " "));
  cout << endl << endl;

  cout << "stable_sort() - descending order\n";
  stable_sort(arr, arr+8, greater< Element >()); // XXX
  copy(arr, arr+8, ostream_iterator< Element >(cout, " "));
  cout << endl << endl;

  cout << "READY.\n";
  return 0;
}
