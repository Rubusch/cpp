// bind2nd.cpp
/*
  Generate function object class with 2nd parameter binded
//*/


#include <algorithm>
#include <functional>
#include <iostream>


int main()
{
  int numbers[] = {1, -2, 3, -4, -5, 6, 7};
  int cnt =
      std::count_if(numbers, numbers + 7, std::bind2nd(std::less< int >(), 0));
  std::cout << cnt << " negative elements\n";

  std::cout << "READY.\n";
  return 0;
}
