/*
  C++11 - prefer unique_ptr to auto_ptr and raw pointers (Meyers / item 18)


  // factory method:
  // with default delete method
  template< typename... Ts>
  std::unique_ptr< Fruit >
  makeJuice(Ts&&... params);


 Conclusion:

 - 'std::unique_ptr' is a small, fast, move-only smart pointer for managing
   resources with exclusive-ownership semantics

 - by default, resource destruction takes place via 'delete', but custom
   deleters can be specified. Stateful deleters and function pointers as
   deleters increase the size of 'std::unique_ptr' objects

 - converting a 'std::unique_ptr' to a 'std::shared_ptr' is easy
  resources: Effective Modern C++, Scott Meyers, 2015

 @author: lothar Rubusch
 */

#include <iostream>
#include <memory> /* unique_ptr */

using namespace std;


static auto is_orange_juice=true;

class Fruit
{
public:
  Fruit()
  {
    cout << "CALLED: Fruit()" << endl;
  }
  virtual ~Fruit() = default; // essential: derrived class object shall be destructed via base class pointer
};


class Lemon
  : public Fruit
{
public:
  Lemon()
  {
    cout << "CALLED: Lemon()" << endl;
  }
};


class Orange
  : public Fruit
{
public:
  Orange()
  {
    cout << "CALLED: Orange()" << endl;
  }
};


// customize delete, e.g. logs out
auto delete_fruit = [](Fruit* pFruit)
  {
    cout << "CALLED: delete_fruit" << endl;
    delete pFruit;
  };
// revised return type, version with customized delete

// C++11
template< typename... Ts>
unique_ptr< Fruit, decltype(delete_fruit) >
makeJuice(Ts&&... params)
{
  // pointer to be returned
  unique_ptr< Fruit, decltype(delete_fruit) > pFruit(nullptr, delete_fruit);

  if (is_orange_juice) {
    pFruit.reset(new Orange(std::forward< Ts >(params)...));
  } else {
    pFruit.reset(new Lemon(std::forward< Ts >(params)...));
  }
  return pFruit;
}


int main(void)
{
  cout << "let's get some fresh fruit" << endl;
  auto pointerjuice = makeJuice();

  // work with the pointerjuice, at exit of scope it's deleted automatically
  cout << "READY." << endl;
}
