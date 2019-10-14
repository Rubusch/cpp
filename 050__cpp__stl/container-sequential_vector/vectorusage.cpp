// vectorusage.cpp
/*
  demonstrates some access, output and usage of the vector

  the STL has 3 sequential containers:
  - vector
  - deque
  - list

  acessibility:
  - operator[](), prints no exception if out of range
  - at(), prints an out_of_range exception, if so
//*/


#include <iostream>
#include <iterator>
#include <stdexcept> // std::out_of_range
#include <vector>


/*
  function that tries to access the 5th element passing the probably thrown
  out_of_range exception upward
//*/
inline int fifthelement(const std::vector< int > &vec) throw(std::out_of_range)
{
  return vec.at(5);
}


/*
  main...
//*/
int main()
{
  using namespace std;

  cout << "set up a vector with 5 elements\n";
  vector< int > vec(5);
  cout << endl;

  cout << "init each element\n";
  for (unsigned int idx = 0; idx < vec.size(); ++idx) {
    vec[idx] = idx + 1;
  }
  cout << endl;

  cout << "append an additional element \'9\'\n";
  vec.push_back(9);
  cout << endl;

  cout << "check if the last element is \'9\' using \"back()\"\n";
  if (vec.back() != 9) {
    cout << "Something\'s wrong!\n";
  }
  cout << "ok.\n";
  cout << endl;

  cout << "remove the last element using \"pop_back()\"\n";
  vec.pop_back();
  cout << endl;

  cout << "set the first element to 0\n";
  vec.front() = 0;
  cout << endl;

  cout << "print out the content of the vector so far using \"copy()\" and "
          "\"ostream_iterator<>()\"\n";
  copy(vec.begin(), vec.end(), ostream_iterator< int >(cout, " "));
  cout << endl;

  cout << "try to access an element out of range\n";
  try {
    cout << fifthelement(vec);
  } catch (out_of_range &ex) {
    cout << "\nout_of_range exception: " << ex.what();
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
