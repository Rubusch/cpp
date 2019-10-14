// listusage.cpp
/*
  demonstrates list

  the STL has 3 sequential containers:
  - vector
  - deque
  - list
//*/


#include <algorithm>
#include <functional>
#include <iostream>
#include <list>


// using namespace std;


template < class T >
std::ostream &operator<<(std::ostream &os, const std::list< T > &lst)
{
  if (lst.empty()) {
    return os << "empty";
  }

  for (typename std::list< T >::const_iterator iter = lst.begin();
       iter != lst.end(); ++iter) {
    os << *iter << " ";
  }
  return os;
}


/*
  main...
//*/
int main()
{
  using namespace std;

  cout << "init a list..\n";
  list< int > lst_a, lst_b;
  for (int idx = 1; idx < 9; ++idx) {
    if (idx % 2 == 1) {
      lst_a.push_front(idx);
    } else {
      lst_b.push_back(idx);
    }
  }
  cout << "lst_a = " << lst_a << " and lst_b = " << lst_b << endl;
  cout << endl;

  cout << "call sort()\n";
  lst_a.sort();
  cout << "lst_a = " << lst_a << endl;
  cout << endl;

  cout << "set up another list lst_c\n";
  list< int > lst_c(lst_a);
  cout << "mix with copy of lst_a\n";
  lst_a.merge(lst_c);
  cout << "lst_a = " << lst_a << endl;
  cout << endl;

  cout << "call reverse()\n";
  lst_b.reverse();
  cout << "lst_b = " << lst_b << endl;
  cout << endl;

  cout << "call \"splice(lst_a.begin(), lst_b, iter_b4, lst_b.end())\" to "
          "combine the lists\n";
  list< int >::iterator iter_b4 = find(lst_b.begin(), lst_b.end(), 4);
  lst_a.splice(lst_a.begin(), lst_b, iter_b4, lst_b.end());
  cout << "lst_a = " << lst_a << " and lst_b = " << lst_b << endl;
  cout << endl;

  cout << "call \"splice(lst_a.end(), lst_b)\"\n";
  lst_a.splice(lst_a.end(), lst_b);
  cout << "lst_a = " << lst_a << " and lst_b = " << lst_b << endl;
  cout << endl;

  cout << "call \"remove(5)\"\n";
  lst_a.remove(5);
  cout << "lst_a = " << lst_a << endl;
  cout << endl;

  cout << "call \"unique()\"\n";
  lst_a.unique();
  cout << "lst_a = " << lst_a << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
