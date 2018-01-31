// destructoranddelete.cpp
/*
  Shows how to handle internal used dynamic memory.

  Use delete on pointer members in destructors.

 (6/Meyers)
//*/

#include <iostream>
#include <string>
using namespace std;

template<class T>
class Foobar
{
private:
  T* pMember;

public:
  // ctor
  Foobar()
    :pMember(NULL)
  {
    // nothing
  }

  // cpy ctor
  Foobar(const Foobar& fb)
  {
    setMember(fb.getMember());
  }

  // dtor
  ~Foobar()
  {
    // delete every dynamical pointer at least once in the destructor
    // if it is not used the pointer should point to NULL
    // -> delete NULL is harmless!
    delete pMember;
    // thus set it again to NULL!
    pMember = NULL;
  }


  /*
    F U N C T I O N S
  //*/


  T getMember() const
  {
    return *pMember;
  }

  void setMember(T tmp)
  {
    pMember = new T;
    *pMember = tmp;
  }
};


int main()
{
  Foobar<string> fb;
  fb.setMember("Jack and Jill went up the hill to fetch a pail of water.");
  cout << fb.getMember() << endl;

  cout << "READY\n";
  return 0;
}

