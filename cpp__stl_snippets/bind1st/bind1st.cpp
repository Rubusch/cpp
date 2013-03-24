// bind1st.cpp
/*
  Return function object with first parameter binded.
//*/


#include <iostream>
#include <functional>
#include <algorithm>


int main()
{
  // create instance of binder1st object, call to: binder1st-ctor(operation, arg)
  std::binder1st< std::equal_to< int > > equal_to_5( std::equal_to< int >(), 5);

  int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 5 };
  int cnt = std::count_if( numbers, numbers+8, equal_to_5);

  std::cout << cnt << " elements equal to 5.\n";

  std::cout << "READY.\n";
  return 0;    
}

