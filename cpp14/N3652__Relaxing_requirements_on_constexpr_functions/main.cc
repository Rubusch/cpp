/*
 * c++14: N3652 "Relaxing constraints on constexpr functions"
 *
 * resource:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3652.html
 *
 * compiler support:
 * gcc 5 (GNU)
 * Clang 3.4
 *
 * author: Lothar Rubusch
 */
#include <iostream>
#include <cmath> // pow(), to check square and multiply algorithm

using namespace std;

// the C++11 constexpr functions use recursion rather than iteration
// (C++14 constexpr functions may use local variables and loops, see below)
constexpr int factorial(int n)
{
  return n <= 1 ? 1 : (n * factorial(n-1));
}

template<class T>
class MyBinary {
private:
  int bitmap[sizeof(T)*8];
  int size;
public:
  constexpr MyBinary(T value) :size(-1)
  {
    for (int idx=0; idx < (int) (sizeof(T)*8); ++idx) {
      bitmap[(sizeof(T)*8-1) - idx] = value & (1 <<idx) ? 1 : 0;
      if (1 == bitmap[(sizeof(T)*8-1) - idx]) size = idx+1;
    }
  }
  constexpr int getpos(int pos)
  {
    return bitmap[(sizeof(T)*8-1) - size + 1 + pos];
  }
  constexpr int getsize() { return size; }
};

/*
  C++14: The proposal lists the following things which are going to be allowed
  in constexpr functions:
  - declarations in constexpr functions with the exception of static,
    thread_local or uninitialized variables
  - if and switch statements
  - looping constructs, including range-based for
  - modification of objects whose lifetime began within the constant expression
    evaluation
*/
template<class T>
constexpr int squareandmultipy(int base, T exp, int mod)
{
  int res = 1;
  MyBinary<T>* bitexp = new MyBinary<T>(exp);

  for (int idx=0; idx<bitexp->getsize(); ++idx) {
    res = res * res;
    if (0 != mod) res = res % mod;
    if (1 == bitexp->getpos(idx)) {
      res = res * base;
      if (0 != mod) res = res % mod;
    }
  }
  delete bitexp;

  return res;
}

// literal class
class conststr {
  const char * p;
  size_t sz;
public:
  template<size_t N>
  constexpr conststr(const char(&a)[N]) : p(a), sz(N-1) {}
  // constexpr functions signal errors by throwing exceptions
  // in C++11, they must do so from the conditional operator ?:
  constexpr char operator[](size_t n) const {
    return n < sz ? p[n] : throw out_of_range("");
  }
  constexpr size_t size() const { return sz; }
};

constexpr size_t countlower(conststr s, size_t n = 0, size_t c = 0) {
/*
  // C++11 constexpr functions had to put everything in a single return statement
  return n == s.size() ? c :
    s[n] >= 'a' && s[n] <= 'z' ? countlower(s, n+1, c+1) :
    countlower(s, n+1, c);
/*/
  // C++14 doesn't have that requirement
  if (n == s.size()) {
    return c;
  }else{
    if (s[n] >= 'a' && s[n] <= 'z') {
      return countlower(s, n+1, c+1);
    }else{
      return countlower(s, n+1, c);
    }
  }
//*/
}

// output function that requires a compile-time constant, for testing
template<int n> struct constN {
  constN() { cout << n << '\n'; }
};

int main()
{
  cout << "4! = " ;
  // computed at compile time
  constN<factorial(4)> out1;

  // disallow optimization using volatile
  volatile int k = 8;
  // computed at run time
  cout << k << "! = " << factorial(k) << '\n';

//  int check = pow(4.0, 13.0);
  // C++14: more complex operation possible within constexpr function
  cout << "4^13 = " << squareandmultipy<int>(4, 13, 0)
//       << " [" << check << "] "
       << endl;

  cout << "Number of lowercase letters in \"Hello, world!\" is ";
  // implicitly converted to conststr
  constN<countlower("Hello, world!")> out2;
}
