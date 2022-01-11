/*
  C++11 - prefer unique_ptr to auto_ptr and raw pointers
  (Meyers / item 18)

  unique_ptr is always the unique owner of the raw pointer resource!
  thus a unique_ptr object cannot be copied - only moved (i.e. the
  moving pointer looses its ownership, can mean it will be destroyed
  after moving)

  demonstrates access to a container< unique_ptr > elements, without
  destroying or shifting ownership of member elements

 @author: Lothar Rubusch <L.Rubusch@gmail.com>
 */

#include <vector>
#include <memory>
#include <iostream>

template <class T>
void display(const T& con)
{
  using namespace std;
  cout << '{';
  if (!con.empty()) {
    cout << *con.front();
  }
  for (auto idx = next(con.begin()); idx != con.end(); ++idx) {
    cout << ", " << **idx;
  }
  cout << "}\n";
}

int main()
{
  typedef std::unique_ptr< int > ptr_t;
  std::vector<ptr_t> vec;

  for (int idx = 1; idx <= 5; ++idx) {
    vec.push_back(ptr_t(new int(idx)));
  }

  display(vec);

  for (auto it = vec.begin(); it != vec.end(); ++it) {
    **it += 2;
  }

  display(vec);

  exit(EXIT_SUCCESS);
}
