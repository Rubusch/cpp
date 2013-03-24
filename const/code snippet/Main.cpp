// Main.cpp
/*
  const void func(const &ref) const

  the greater() method needs two "const" variables
    bool greater(const int& a, const int& b)
    --> const int getKey()

  the compare() method has two "const" variables.
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
    Key()
    {
        key = rand()%123;
    };

    const int getKey() const
    {
        return key;
    };
};


class User
{
private:
    bool greater(const int& a, const int& b)
    {
        return a>b;
    };

public:
    bool compare(const Key& key1, const Key& key2)
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
    cout << "\tWhat do you think, the first looks longer? " << endl << "Al:\t"
         << (u->compare(*k1, *k2)?"Yes!":"No!")
         << " The first key has " << k1->getKey() << "mm" << endl
         << "\tand the second key " << k2->getKey() << "mm." << endl;
    return 0;
};


/*
  -> Const With Pointers and Type-Casting <-

  a pointer to a const object can be initialized with a pointer to an object
  that is not const, but not vice versa!!!
//*/
class FurtherInformation{
  const int x;                // constant int
  const int y=123;
  y=1; x = 2;                 // illegal - can't modify x

  const int* pX;    	      // changeable pointer to constant int
  *pX = 3;          	      // illegal -  can't use pX to modify an int
  pX = &someOtherIntVar;      // legal - pX can point somewhere else

  int* const pY;              // constant pointer to changeable int
  *pY = 4;                    // legal - can use pY to modify an int
  pY = &someOtherIntVar;      // illegal - can't make pY point anywhere else

  const int* const pZ;        // const pointer to const int
  *pZ = 5;                    // illegal - can't use pZ to modify an int
  pZ = &someOtherIntVar;      // illegal - can't make pZ point anywhere else
};
