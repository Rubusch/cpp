// lambda.cpp
/*
  Lambda (>=cpp11) constructs a closure: an unnamed function object capable of capturing variables in scope.

  This example shows basic usage of lambda expressions.


  ---


  fundamentals
  ------------

  int x = 10;
  (...)
  auto var = [x] (int y) constexpr -> int {return x * y > 123; };



  syntax variants:

  [capture] (params) mutable exception attribute -> ret { body }
  [capture] (params) -> ret { body }
  [capture] (params) { body }
  [capture] { body }



  terminology:

  auto var : closure
    the lambda object is called 'closure'

  [x] : capture
    which symbols are captured and thus visible for the lambda body, e.g.
    [a,&b]   a as by value copy, b as reference
    [this]   this pointer as a by value copy
    [&]      all symbols available in function scope as reference
    [=]      all symbols available in function scope as a copy
    []       nothing captured

  (int y) : params
    list of parameters

  constexpr -> int : (optional, can be left out)
    specifier: mutable, constexpr, consteval (opt)
    where:
      mutable = allows the body to modify copied params and to call their non-const member functions
      exception = exception specification, or noexcept
      attribute = attribute specificatio for the closure type

    return type or use auto for closure, defaults to "void" (opt)

  {return x * y > 123; }; : function body
    implementation of the lambda class



  C++11 - avoid default capture modes
  (Meyers / item 31)

  CONCLUSION

  - Default by-reference capture can lead to dangling references.

  - Default by-value capture is susceptible to dangling pointers (especially this),
    and it misleadingly suggests that lambdas are self-contained.

  resources:
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
//*/

#include <vector> /* vector */
#include <algorithm> /* remove_if() */
#include <functional> /* lambda */
#include <iostream>

using namespace std;


class Fruit
{
private:
  const string *pItem = nullptr;

public:
  Fruit(const string *item)
  {
    pItem = item;
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // copy assignment constructor: needed for iterating on vector<Fruit>
  Fruit(const Fruit& fruit)
  {
    if (this == &fruit) return;
    pItem = new string(*fruit.pItem);
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // copy move constructor: needed for vector<Fruit>::push_back()
  Fruit(Fruit&& fruit)
  {
    if (this == &fruit) return;
    pItem = fruit.pItem;
    fruit.pItem = nullptr;
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // copy move constructor: needed for vector<Fruit>::push_back()
  ~Fruit()
  {
    if (nullptr != pItem) delete pItem;
    pItem = nullptr;
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // needed for remove_if() and lambda
  constexpr Fruit& operator=(const Fruit& fruit)
  {
    if (this != &fruit) {
      if (pItem) delete pItem;
      pItem = new string(*fruit.pItem);
    }
    return *this;
  }

  // some getter
  const string* getItem() const
  {
    return pItem;
  }

  // print out class
  friend
  ostream& operator<<(ostream& out, Fruit& fruit);
};

ostream& operator<<(ostream& out, Fruit& fruit)
{
  if (fruit.pItem) return out << *fruit.pItem; // segfaults: when copy assignment ctor is missing
  return out << "";
}


int main(void)
{
  vector<Fruit> box;
  box.push_back( Fruit(new string("Lemon"))); // double free: when copy move ctor missing
  box.push_back( Fruit(new string("Orange")));
  box.push_back( Fruit(new string("Banana")));
  box.push_back( Fruit(new string("Ananas")));

  cout << "before:" << endl;
  for (Fruit fruit : box) cout << "  " << fruit;
  cout << endl << endl;

  // the lambda function passed to the remove_if()
  string x = "Banana";
  cout << "now removing '" << x << "'" << endl;
  box.erase( remove_if( box.begin(), box.end()
                        , [x](Fruit fruit){
                            cout << "CALLED: lambda for '" << *fruit.getItem() << "' " << endl;
                            return *fruit.getItem() == x;
                          }), box.end() );
  cout << endl;

  cout << "after:" << endl;
  for (Fruit fruit : box) cout << "  " << fruit;
  cout << endl << endl;

  cout << "READY." << endl;
}

