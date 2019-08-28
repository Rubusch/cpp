/*
  C++11 - prefer const_iterators to iterators (Meyers / item 13)

  ---

  lvalue    - has an address, e.g. a user maintained variable or memory with
              accessible address

  rvalue    - has no accessible address, e.g. a plain number value (stored only
              temporarlily)


  conclusion:

  - prefer const_iterators to iterators

  - in maximally generic code, prefer non-member versions of begin, end, rbegin,
    etc., over their member function counterparts

  resources: Effective Modern C++, Scott Meyers, 2015
 */

#include <iostream>
#include <vector>
#include <algorithm> /* find() */

using namespace std;

template< typename C, typename V >
void find_and_insert98(C& container, const V& targetval, const V& insertval)
{
//*
  vector<int>::iterator it = find(container.begin(), container.end(), targetval);
  container.insert(it, insertval);
/*/
  // iterators aren't really the proper choice here, because
  // this code never modifies what an iterator points to;
  // revising the code to use const_iterators should be trivial
  // (which in C++98 was not anything but trivial)
  using iter_t = std::vector<int>::iterator;
  using const_iter_t = std::vector<int>::const_iterator;
  const_iter_t ci = std::find(static_cast<const_iter_t>(container.begin())
                              , static_cast<const_iter_t>(container.end())
                              , targetval);

  container.insert(static_cast<iter_t>(ci), insertval);
  // even may not compile
// */
}

template< typename C, typename V >
void find_and_insert14(C& container, const V& targetval, const V& insertval)
{
  using std::cbegin;
  using std::cend;

  auto it = std::find(cbegin(container)
                      , cend(container)
                      , targetval);

  container.insert(it, insertval);
}


int main(void)
{
  vector<int> values(10, 20);
  values.push_back(1976);

//* // C++98
  cout << "performing C++98 find_and_insert()" << endl;
  find_and_insert98(values, 1976, 1998);
  cout << endl;
// */

//*
  // C++14 version:
  cout << "performing C++14 find_and_insert()" << endl;
  find_and_insert14< vector<int>, int >(values, 1976, 2014);
  cout << endl;
//*/

  cout << "READY." << endl;
}

