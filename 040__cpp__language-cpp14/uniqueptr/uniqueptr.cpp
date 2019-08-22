/*
  C++11 - prefer unique_ptr to auto_ptr and raw pointers (Meyers / item 18)

  demonstrates basic operations with unique_ptr

 @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* unique_ptr */

using namespace std;


class Box
{
private:
  auto number_of_toys;

public:
  Box( int number) : number_of_toys(number)
  {
    cout << "CALLED: Box()" << endl;
  }
};



int main(void)
{
// TODO

  cout << "READY." << endl;
}
