// pts.cpp
/*
  Techniques: Partial Template Specialization

  "Partial template specialization allows you to spezialize a class template for subsets of that
  template's possible instantiation set.

  Unfortunately, partial template spezialization does not apply to functions - be they
  member or nonmember - which somewhat reduces the flexibility and the granularity of
  what you can do.

  - although you can totally specialize member functions of a class template, you cannot
  partially speciallize member functions.

  - you cannot partially specialize namespace-level (nonmember) template functions. The
  closest thing to partial specialization for namespace-level template functions is
  overloading. For practical purposes, this means that you have fine-grained specialization
  abilities only for the function parameters - not for the return value or for internally
  used types."

  resources: Modern C++ Design, Alexandrescu

  The example:

                                              +--------------------+
                                              | Array<T, int SIZE> |
                                              | template class     |
                                              +--------------------+
                                                  ***template***
                                                        |
                            specialized                 |
                            template function           |
                            for specific access         | specialized template
             / printChar10()-----------+                | instance
           /                           |      +--------------------+
  client <                             +----->| Array<char, SIZE>  |
           \                           |      +--------------------+
             \ printAnyCharArray()-----+
                            partial
                            specialized template
                            function for general
                            access

//*/


#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;


/*
  CAUTION!

  Uncomment the following to see that the "full specialized template" function won't compile
  with a differently by template types, instantiated object.
//*/
/*
#define PROBLEM
//*/

template <typename T, int>
class Array;

void printChar10(Array< char, 10 >& arr_obj);

template< int size >
void printAnyCharArray(Array< char, size >& arr_obj);


/*
  specialized template class

  The class represents an array, it can contain everything, but needs an size parameter - the
  SIZE can either be a valid number or a define, nothing else will compile!
//*/
template< typename T, int SIZE >
class Array
{
private:
  T arr[SIZE];

  // output
  T* content()
  {
    return arr;
  }

public:
  Array(const T* tmp, const int size)
  {
    if(SIZE < size) exit(-1);

    // reset
    for(int idx=0; idx<SIZE; ++idx){
      arr[idx] = tmp[idx];
    }
  }

  friend
  void printChar10(Array< char, 10 >& arr_obj);

  friend
  void printAnyCharArray< SIZE >(Array< char, SIZE >& arr_obj);
};


/*
  specialized template function

  To access a 10-element-char-array, a "specialized template function" for exact this case
  helps out.
//*/
void printChar10(Array< char, 10 >& arr_obj)
{
  cout << "printChar10()\t\t-\t#" << arr_obj.content() << "#" << endl;
}


/*
  partial specialized template function

  to access in a common way, but ONLY handle char arrays, a "partial specialized template
  function" helps.
//*/
template< int size >
void printAnyCharArray(Array< char, size >& arr_obj)
{
  cout << "printAnyCharArray()\t-\t#" << arr_obj.content() << "#" << endl;
}


/*
  main...
//*/
int main()
{
  string str1 = "123456789";
  string str2 = "1234567890123456789";

  // init
  cout << "init of two objects type Array...\n\n";
  Array< char, 10 > c10Arr(str1.c_str(), (strlen(str1.c_str()) + 1));
  Array< char, 20 > c20Arr(str2.c_str(), (strlen(str2.c_str()) + 1));

  // indirect call with a specified facade function
  cout << "using the specialized function to print out the contents of the two objects\n";
  printChar10(c10Arr);

#ifdef Problem
  /*
    This function call results in an compile time error because the size would not fit!
  //*/
  printChar10(c20Arr);
#endif

  cout << endl;

  cout << "using the partial specialized function to print out both using the same function\n";
  printAnyCharArray(c10Arr);
  printAnyCharArray(c20Arr);
  cout << endl;

  cout << "READY.\n";
  return 0;
}
