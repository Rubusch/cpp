/*
  move assinment

 in context of move and copy constructors:
 - a copy constructor creates a deep copy of an object with out changing the object's content
 - a move constructor creates a deep copy of an object, allowing to change even the object itself (rhs)

 purpose:
 - performance increase and under the hood optimizations when using STL containers (return value optimization, rvo)
 - non-copiable objects: parallel execution of a function of a non-copiable object e.g. inside threads

 caution:
 use of moved objects after the move can implicitely be dangerous,
 but is guaranteed for the STL and should always be implemented as best practice
 */

#include <iostream>
#include <string>

using namespace std;


class Box
{
private:
  string item;

public:
  Box(string it) : item(it) {}
};


int main(void)
{
  string item = "elephant";
  Box box(item);

  cout << "XXX: " << item << endl;

  cout << "READY." << endl;

  exit(EXIT_SUCCESS);
}
