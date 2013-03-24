// visitor.cpp
/*
  Represent an operation to be performed on the elements of an object structure.
  Visitor lets you define a new operation without changing the classes of the
  elements on which it operates.

     +---------------------+                     +---------------------+
  +--| Client              |-------------------->| Visitor             |
  |  +---------------------+                     +=====================+
  |                                              |                     |
  |                                              +---------------------+
  |                                              | visit(Element1)     |
  |                                              | visit(Element2)     |
  |                                              +---------------------+
  |                                                        /_\
  |                                                         |
  |                                                         |
  |                                                         |
  |                                              +----------------------+
  |                                              | ConcreteVisitor      |
  |                                              +======================+
  |                                              |                      |
  |                                              +----------------------+
  |                                              | visit(Element1)      |
  |                                              | visit(Element2)      |
  |                                              +----------------------+
  |
  |
  |  +---------------------+                     +---------------------+
  +->| ObjectStructure     |<>------------------>| Element             |
     +---------------------+                     +=====================+
                                                 |                     |
                                                 +---------------------+
                                                 | accept(visitor)     |
                                                 +---------------------+
                                                           /_\
                                                            |
                                              +-------------+-------------+
                                              |                           |
                                   +---------------------+     +---------------------+
                                   | Element1            |     | Element2            |
                                   +=====================+     +=====================+
                                   |                     |     |                     |
                                   +---------------------+     +---------------------+
                                   | accept(Visitor) o   |     | accept(Visitor) o   |
                                   | operationA()    |   |     | operationB()    |   |
                                   +-----------------|---+     +-----------------|---+
                                                     |                           |
                                                     |                           |
                                    +------------------+\       +------------------+\
                                    | v->visit(*this)  +-+      | v->visit(*this)  +-+
                                    +--------------------+      +--------------------+

  (GoF, 1995)
//*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


class Visitor;


struct Element
{
  virtual void accept(Visitor* visitor) = 0;
};


class Element1
  : public Element
{
public:
  void sayHello()
  {
    std::cout << "\t\t\"Hello, from Element1!\"\n";
  }
  
  void accept(Visitor* visitor);
};


class Element2 : public Element
{
private:
  std::string str_;

public:
  Element2() : str_("Hello, from Element2!")
  {}

  void accept(Visitor* visitor);

  friend std::ostream& operator<<(std::ostream& os, Element2& element);
};

std::ostream& operator<<(std::ostream& os, Element2& element)
{
  return os << element.str_;
}


class ObjectStructure
{
private:
  std::vector< Element* > elements_;

public:
  std::vector< Element* >& elements()
  {
    return elements_;
  }
};


class Visitor
{
public:
  virtual void visit(Element1&) const = 0;
  virtual void visit(Element2&) const = 0;

  virtual void visitAll(ObjectStructure*) const = 0;
};


class ConcreteVisitor
  : public Visitor
{
public:
  void visit(Element1& element) const
  {
    element.sayHello();
  }

  void visit(Element2& element) const
  {
    std::cout << "\t\tElement2 says: " << element << std::endl;
  }

  void visitAll(ObjectStructure* os) const
  {
    if(NULL == os) return;
    std::for_each(os->elements().begin(), os->elements().end(), std::bind2nd( std::mem_fun(&Element::accept), this));
  }
};


// declaration issues..

void Element1::accept(Visitor* visitor)
{
  visitor->visit(*this);
}


void Element2::accept(Visitor* visitor)
{
  visitor->visit(*this);
}



/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  ObjectStructure os;
  Element1 elem_1;
  os.elements().push_back(&elem_1);
  Element1 elem_2;
  os.elements().push_back(&elem_2);
  Element1 elem_3;
  os.elements().push_back(&elem_3);
  Element2 elem_4;
  os.elements().push_back(&elem_4);
  Element2 elem_5;
  os.elements().push_back(&elem_5);
  Element1 elem_6;
  os.elements().push_back(&elem_6);
  Element2 elem_7;
  os.elements().push_back(&elem_7);
  cout << endl;

  cout << "do visits\n";
  ConcreteVisitor concVisitor;
  concVisitor.visitAll(&os);  
  cout << endl;

  cout << "READY.\n";
  return 0;
}
