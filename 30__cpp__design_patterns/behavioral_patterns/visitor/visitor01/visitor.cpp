// visitor.cpp
/*
  Represent an operation to be performed on the elements of an object
  structure. Visitor lets you define a new operation without changing
  the classes of the elements on which it operates.

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


/*
  Element

  - defines an Accept operation that takes a visitor as an argument.
//*/
class Element
{
public:
  virtual void accept(Visitor* visitor) = 0;
};


/*
  Element1 - a ConcreteElement

  - impelments an accept operation that takes a visistor as an argument.
//*/
class Element1
  : public Element
{
public:
  void sayHello()
  {
    std::cout << "\tElement1::sayHello()\n";
    std::cout << "\t\t\"Hello, from Element1!\"\n";
  }

  void accept(Visitor* visitor);
};


/*
  Element2 - another concrete element
//*/
class Element2
  : public Element
{
private:
  std::string str_;

public:
  Element2()
    : str_("Hello, from Element2!")
  {
    std::cout << "\tElement2::Element2() - ctor\n";
  }

  void accept(Visitor* visitor);

  friend std::ostream& operator<<(std::ostream& os, Element2& element);
};

std::ostream& operator<<(std::ostream& os, Element2& element)
{
  return os << element.str_;
}


/*
  ObjectStructure

  - can enumerate its elements.
  - may provide a high-level interface to allow the visitor to visit its elements
  - may either be a composite or a collection such as a sequential or associative structure
//*/
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


/*
  Visitor

  - declares a Visit operation for each class of ConcreteElement in the object structure.
  The operation's name and signature identifies the class that sends the Visit request to
  the visitor. That lets the visitor determine the concrete class of the element being
  visited. Then the visitor can access the element directly through its particular
  interface.
//*/
class Visitor
{
public:
  virtual void visit(Element1&) const = 0;
  virtual void visit(Element2&) const = 0;

  virtual void visitAll(ObjectStructure*) const = 0;
};


/*
  ConcreteVisitor

  - implements each operation declared by Visitor. Each operation implements a fragment of the
  algorithm defined for the corresponding class of object in the structure. ConcreteVisitor
  provides the context for the algorithm and stores its local state. This state often accumulates
  results during the traversal of the structure.
//*/
class ConcreteVisitor
  : public Visitor
{
public:
  void visit(Element1& element) const
  {
    std::cout << "\tConcreteVisitor::visit(Element1&)\n";
    element.sayHello();
  }

  void visit(Element2& element) const
  {
    std::cout << "\tConcreteVisitor::visit(Element2&)\n";
    std::cout << "\t\tElement 2 says: " << element << std::endl;
  }

  void visitAll(ObjectStructure* os) const
  {
    std::cout << "\tConcreteVisitor::visitAll(ObjectStructure*)\n";
    if(NULL == os) return;
    std::for_each(os->elements().begin(), os->elements().end(), std::bind2nd( std::mem_fun(&Element::accept), this));
    /* same as:
    std::vector< Element* >& elements = os->elements();
    for( std::vector< Element* >::iterator iter = elements.begin(); iter != elements.end(); ++iter){
       (*iter)->accept(*this);
    }
    //*/
  }
};


/*
  definitions here due to declaration issues
//*/

void Element1::accept(Visitor* visitor)
{
  std::cout << "\tElement1::accept(Visitor*)\n";
  visitor->visit(*this);
}


void Element2::accept(Visitor* visitor)
{
  std::cout << "\tElement2::accept(Visitor*)\n";
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
