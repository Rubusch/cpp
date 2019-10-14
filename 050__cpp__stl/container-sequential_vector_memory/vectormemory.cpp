// vectormemory.cpp
/*
  vector and memory operations
//*/


#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

// using namespace std;

/*
  info output function
//*/
void info(const std::vector< int > &vec)
{
  std::cout << "size = " << vec.size() << std::setw(2)
            << ", capacity = " << vec.capacity() << ", content: ";
  std::copy(vec.begin(), vec.end(),
            std::ostream_iterator< int >(std::cout, " "));
  std::cout << std::endl << std::endl;
}


/*
  main...
//*/
int main()
{
  using namespace std;

  cout << "init..\n";
  const int arr[] = {1, 2, 3, 4, 5, 6, 7};
  vector< int > vec;
  info(vec);

  cout << "call \"reserve(6)\"\n";
  vec.reserve(6);
  info(vec);

  cout << "call \"assign( arr, arr + 4)\"\n";
  vec.assign(arr, arr + 4);
  info(vec);

  cout << "call \"resize(2)\"\n";
  vec.resize(2);
  info(vec);

  cout << "call \"assign(3U, 9)\"\n";
  vec.assign(3U, 9);
  info(vec);

  cout << "call \"resize(5, 7)\"\n";
  vec.resize(5, 7);
  info(vec);

  cout << "call \"insert(vec.end(), arr, arr + 2)\"\n";
  vec.insert(vec.end(), arr, arr + 2);
  info(vec);

  cout << "READY.\n";
  return 0;
}
