/*
 * c++14: N3760 "[[deprecated]] attribute"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3760.html
 *
 * compiler support:
 * gcc 4.9 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>

using namespace std;

int main()
{
  /*
    Compiler          Simple deprecation                  Deprecation with message

    gcc and clang     __attribute__((deprecated)) int a;  __attribute__((deprecated("message"))) int a;
    Visual Studio     __declspec(deprecated) int a;       __declspec(deprecated("message")) int a;
    Embarcadero (1)   int a [[deprecated]];               int a [[deprecated("message")]];

    (1) Embarcadero currently implements the pre-N3067 C++0x attribute syntax.
 */

  //  __attribute__((deprecated)) int something = 777; // warning as deprecated
  [[deprecated]] int something = 777; // warning as deprecated

  /*
    [[deprecated]] is either evaluated by the compiler or ignored similar to a
    #pragma declaration, the warning may have a text message
   */
  cout << "something deprecated: " << something << endl;
}
