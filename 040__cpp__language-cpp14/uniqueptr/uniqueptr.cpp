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
  int number_of_toys;

public:
  Box( int number) : number_of_toys(number)
  {
    cout << "CALLED: Box(" << number << ")" << endl;
  }
  ~Box()
  {
    cout << "CALLED: ~Box()" << endl;
  }

  auto box_content() const
  {
    return number_of_toys;
  }
};



int main(void)
{
  std::unique_ptr< Box > pBox( new Box(12) );

  auto content = pBox->box_content();
  cout << "The box contains " << content << " toys" << endl;

  cout << "READY." << endl;
}
