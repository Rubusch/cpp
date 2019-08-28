// lambda.cpp
/*
  demonstrates lambdas (>=cpp11)

  syntax variants:
  [capture] (params) mutable exception attribute -> ret { body }
  [capture] (params) -> ret { body }
  [capture] (params) { body }
  [capture] { body }

  where:
  mutable = allows the body to modify copied params and to call their non-const member functions
  exception = exception specification, or noexcept
  attribute = attribute specificatio for the closure type

  capture = which symbols are captured and thus visible for the lambda body
  e.g.
    [a,&b]   a as by value copy, b as reference
    [this]   this pointer as a by value copy
    [&]      all symbols available in function scope as reference
    [=]      all symbols available in function scoe as a copy
    []       nothing captured

  params = list of parameters
  ret = return type, defaults to "void"

//*/

#include <vector> /* vector */
#include <algorithm> /* remove_if() */
#include <functional> /* lambda */
#include <iostream>

using namespace std;


class Greek
{
private:
  const string *pItem = nullptr;

public:
  Greek(const string *item)
  {
    pItem = item;
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // copy assignment constructor: needed for iterating on vector<Greek>
  Greek(const Greek& gr)
  {
    if (this == &gr) return;
    pItem = new string(*gr.pItem);
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // copy move constructor: needed for vector<Greek>::push_back()
  Greek(Greek&& gr)
  {
    if (this == &gr) return;
    pItem = gr.pItem;
    gr.pItem = nullptr;
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // copy move constructor: needed for vector<Greek>::push_back()
  ~Greek()
  {
    if (nullptr != pItem) delete pItem;
    pItem = nullptr;
  }

  // !!! always respect rule of five having member pointer to allocated things !!!
  //
  // needed for remove_if() and lambda
  constexpr Greek& operator=(const Greek& gr)
  {
    if (this != &gr) {
      if (pItem) delete pItem;
      pItem = new string(*gr.pItem);
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
  ostream& operator<<(ostream& out, Greek& gr);
};

ostream& operator<<(ostream& out, Greek& gr)
{
  if (gr.pItem) return out << *gr.pItem; // segfaults: when copy assignment ctor is missing
  return out << "";
}


int main(void)
{
  vector<Greek> box;
  box.push_back( Greek(new string("Perikles"))); // double free: when copy move ctor missing
  box.push_back( Greek(new string("Poplicola")));
  box.push_back( Greek(new string("Nikias")));
  box.push_back( Greek(new string("Themistokles")));

  cout << "before:" << endl;
  for (Greek gr : box) cout << "  " << gr;
  cout << endl << endl;

  // the lambda function passed to the remove_if()
  string x = "Poplicola";
  cout << "now removing '" << x << "'" << endl;
  box.erase( remove_if( box.begin(), box.end()
                        , [x](Greek gr){
                            cout << "CALLED: lambda for '" << *gr.getItem() << "' " << endl;
                            return *gr.getItem() == x;
                          }), box.end() );
  cout << endl;

  cout << "after:" << endl;
  for (Greek gr : box) cout << "  " << gr;
  cout << endl << endl;

  cout << "READY." << endl;
}

