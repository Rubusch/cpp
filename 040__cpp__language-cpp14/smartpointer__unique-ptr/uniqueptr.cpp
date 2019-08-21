/*
  C++11 - prefer unique_ptr to auto_ptr and raw pointers (Meyers / item 18)


 Conclusion:

 - 'std::unique_ptr' is a small, fast, move-only smart pointer for managing
   resources with exclusive-ownership semantics

 - by default, resource destruction takes place via 'delete', but custom
   deleters can be specified. Stateful deleters and function pointers as
   deleters increase the size of 'std::unique_ptr' objects

 - converting a 'std::unique_ptr' to a 'std::shared_ptr' is easy

 @author: lothar Rubusch
 */

#include <iostream>

using namespace std;


int main(void)
{
  // TODO

  cout << "READY." << endl;
}
