// binder.cpp
/*
  implements the Visitor-situation and its solution using STL binders

  Visitor::visitAll() calls for each element
  -> Element::accept( Visitor& ) so each element then calls
  -> Visitor::visit( Element& ) which will print "Element visited!"
//*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;


class Visitor;


struct Element
{
  void accept(Visitor*);
};


struct Visitor
{
  void visit(Element& e)
  {
    cout << "Element visited!\n";
  }

  void visitAll(vector< Element* > vec)
  {
    for_each(vec.begin(), vec.end(), bind2nd(mem_fun(&Element::accept), this));
  }
};


// declaration issues...
void Element::accept(Visitor* v)
{
  v->visit(*this);
}


int main()
{
  cout << "init..\n";
  vector< Element* > vec;
  Element elem1, elem2, elem3;
  vec.push_back(&elem1);
  vec.push_back(&elem2);
  vec.push_back(&elem3);
  
  Visitor visitor;
  visitor.visitAll(vec);
  cout << "READY.\n";

  return 0;
}
