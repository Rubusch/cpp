// matrix.cpp
/*
  valarray - matrix simulation using slice()

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <valarray>


template< class T >
std::ostream& operator<<(std::ostream& os, const std::valarray< T >& va)
{
  for(size_t idx = 0; idx < va.size(); ++idx){
    os << va[idx] << " ";
  }
  return os;
}


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const int var_a = 3, var_b = 4;
  cout << endl;

  cout << "spanning up a x b matrix\n";
  valarray< int > va(var_a * var_b);
  for( int idx = 0; idx < var_b; ++idx){
    va[idx] = idx;
  }
  cout << "va \'real\' = \t" << va << endl;
  cout << endl;

  cout << "get matrix from b-idx\n";
  for(int idx = 0; idx < var_b; ++idx){
    cout << 'b' << idx << " = " << valarray< int >(va[ slice( idx * var_a, va.size() / var_b, 1 ) ]) << '\n';
  }
  cout << endl;

  cout << "get matrix from a-idx\n";
  for(int idx=0; idx < var_a; ++idx){
    cout << 'a' << idx << " = " << valarray< int >(va[ slice( idx, va.size() / var_a, var_a) ]) << '\n';
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
