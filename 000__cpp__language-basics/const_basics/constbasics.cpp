// Main.cpp
/*
  const void func(const &ref) const

  the greater() method needs two "const" parameters
    bool greater(const int& a, const int& b)
    --> const int getKey()

  the compare() method has two "const" parameters.
    bool compare(const Key& key1, const Key& key2)
    int getKey() const <--

  thus the getKey() method has to have "const" twice.
    --> const int getKey() const <--
//*/

#include <iostream>
using namespace std;

class Key;
class User;
class Tester;


class Key
{
private:
  int key;

public:
  Key() { key = rand() % 123; };

  const int getKey() const { return key; };
};


class User
{
private:
  bool greater(const int &a, const int &b) { return a > b; };

public:
  bool compare(const Key &key1, const Key &key2)
  {
    return greater(key1.getKey(), key2.getKey());
  };
};


int main()
{
  cout << "Me:\tHere are two keys." << endl;
  Key *k1 = new Key();
  Key *k2 = new Key();
  User *u = new User();

  cout << "\tWhat do you think, the first looks longer? " << endl
       << "Al:\t" << (u->compare(*k1, *k2) ? "Yes!" : "No!") << endl;

  cout << "The first key has " << k1->getKey() << "mm" << endl
       << "\tand the second key " << k2->getKey() << "mm." << endl;

  /*
  -> Const With Pointers and Type-Casting <-

  a pointer to a const object can be initialized with a pointer to an object
  that is not const, but not vice versa!!!
  //*/
  int someIntVar = 66;
  int yetAnotherIntVar = 99;
  // const int x;                     // illegal - must be initialized, inside a
  // class
  //           can be initialized via constructor
  const int y = 123;
  // y = 1;                           // illegal - cannot reinitialize a
  // constant


  /* changeable pointer to a constant */
  const int *pX; // legal - changeable pointer to a constant int
                 //         (constant, can be initialized at once,
                 //         or inside a class or function also later)
  //*pX = 3;                         // illegal -  can't use pX to modify an int
  pX = &yetAnotherIntVar; // legal - pX can point somewhere else
                          //         (instruction is inside function)


  /* constant pointer to a changeable */
  // int* const pY;                   // illegal - must be initialized
  int *const pY = &someIntVar; // legal - constant pointer to a changeable int
  cout << "pY [66]: " << *pY << ", before" << endl;

  *pY = 4; // legal - can use pY to modify an int
  cout << "pY [66]: " << *pY << ", after" << endl;

  // pY = &someIntVar;                // illegal - can't make pY point anywhere
  // else


  /* constant pointer to a constant */
  // const int* const pZ;             // illegal - must be initialized
  const int *const pZ = &someIntVar; // legal - const pointer to const int

  //*pZ = 5;                         // illegal - can't use pZ to modify an int
  // pZ = &yetAnotherIntVar;          // illegal - can't make pZ point anywhere
  // else
  // */


  /* cleanup, best practice to free memory explicitely, which is implicitely
   * done at program close, too */
  delete k1, k2, u;
  k1 = nullptr;
  k2 = nullptr;
  u = nullptr;

  return 0;
};
