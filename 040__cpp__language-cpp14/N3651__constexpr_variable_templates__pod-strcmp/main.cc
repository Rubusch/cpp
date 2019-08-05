/*
 * c++14: N3651 "Variable Templates"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3651.pdf
 *
 * compiler support:
 * gcc 5 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>
#include <string>

using namespace std;

/*
// C++ 11

constexpr int my_charcmp(char c1, char c2)
{
  return (c1 == c2) ? 0 : (c1 < c2) ? -1 : 1;
}

int my_strcmp(const char* str1, const char* str2)
{
  int ret=0, idx=0;
  for (; str1[idx] && str2[idx]; ++idx) {
    if (0 != (ret = my_charcmp(str1[idx], str2[idx])) ) return ret;
  }
  return my_charcmp(str1[idx], str2[idx]);
}


/*/
//  C++ 14
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

//*  // TESTS
  string a = "", b = "";
  int ret = 0;

  a = "abc";
  b = "abc";
  if (0 != (ret = my_strcmp(a.c_str(), b.c_str())) ) cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  a=""; b="";

  a = "cba";
  b = "abc";
  if (1 != (ret = my_strcmp(a.c_str(), b.c_str())) ) cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  a=""; b="";

  a = "abc";
  b = "abcabc";
  if (-1 != (ret = my_strcmp(a.c_str(), b.c_str())) ) cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  a=""; b="";

  a = "abcabc";
  b = "abc";
  if (1 != (ret = my_strcmp(a.c_str(), b.c_str())) ) cout << "FAIL " << "a = " << a << "; b = " << b << "; ret = " << ret << "\n";
  a=""; b="";
//*/

  return 0;
}
