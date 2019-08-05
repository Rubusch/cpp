/*
 * string compare in C++
 *
 * c++14: N3651 "Variable Templates"
 *
 * compiler support:
 * >= gcc 5 (GNU)
 * >= Clang 3.4
 *
 * author: Lothar Rubusch l.rubusch()gmx.ch
 */

#include <iostream>
#include <string>

using namespace std;


// TODO

//  C++ 15
constexpr int my_strcmp(const char* str1, const char* str2)
{
  int idx = 0;
  for (; str1[idx] && str2[idx] && str1[idx] == str2[idx]; ++idx) {}
  if (str1[idx] == str2[idx]) return 0;
  if (str1[idx] < str2[idx]) return -1;
  return 1;
}
//*/


/*
  usage of my_strcmp()
*/
int main()
{
  char str1[] = "abc";
  char str2[] = "abcbcc";

  cout << "my_strcmp( " << str1 << ", " << str2 << " ) = " << my_strcmp(str1, str2) << endl;

  cout << endl;
  cout << "the real situation (c++ is \"c with classes\" and \"never use the STL\" way):" << endl;
  cout << endl;

//*  // TESTS
  string a = "", b = "";
  int ret = 0;

  a = "abc";
  b = "abc";
  if (0 != (ret = my_strcmp(a.c_str(), b.c_str())) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [0]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";

  a = "cba";
  b = "abc";
  if (1 != (ret = my_strcmp(a.c_str(), b.c_str())) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [1]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";

  a = "abc";
  b = "abcabc";
  if (-1 != (ret = my_strcmp(a.c_str(), b.c_str())) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [-1]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";

  a = "abcabc";
  b = "abc";
  if (1 != (ret = my_strcmp(a.c_str(), b.c_str())) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [1]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";
//*/

  cout << endl;
  cout << "STL: string::compare():" << endl;
  cout << endl;

  a = "abc";
  b = "abc";
  if (0 != (ret = a.compare(b)) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [0]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";

  a = "cba";
  b = "abc";
  if (0 >= (ret = a.compare(b)) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [>0]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";

  a = "abc";
  b = "abcabc";
  if (0 <= (ret = a.compare(b)) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [<0]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";

  a = "abcabc";
  b = "abc";
  if (0 >= (ret = a.compare(b)) ) {
    cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  } else {
    cout << "OK [>0]: " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  }
  a=""; b="";
// */

  cout << endl;
  cout << "some operator way:" << endl;
  cout << endl;

// TODO

  return 0;
}

