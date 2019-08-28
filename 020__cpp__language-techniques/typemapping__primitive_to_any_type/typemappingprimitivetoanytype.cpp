// int2type.cpp
/*
Mapping integral Constants to Types

What's going on here?

By the call of one and the same function "doSomething()" of a class
"NiftyContainer" are implemented two different behaviors, and thus two
different actions to be done with one and the same passed argument:
a pointer to an instance of the "GuineaPig" class

"Typically, you use Int2Type when both of the following conditions are
satisfied:
- you need to call one of several different functions, depending on a
compile-time constant
- you need to do this dispatch at compile time."

resources: Modern C++ Design, Alexandrescu
//*/


#include <iostream>


using namespace std;


/*
  the Int2Type trick
//*/
template< int v >
struct Int2Type
{
  enum{ value = v };
};


/*
the problem situation:

"Say NiftyContainer contains pointers to objects of type T. To duplicate an
object contained in NiftyContainer, you want to call either its copy constructor
(for nonpolymorphic types) or clone() virtual function (for polymorphic types).
You get this information from the user in the form of a Boolean template
parameter."

"It is also possible for the nonpolymorphic branch of the code to fail to
compile. If T is a polymorphic type and the nonpolymorphic code branch attempts

    new T(*pObj)

the code might fail to compile. This might happen if T has disabled its copy
constructor (by making it private), as a well-behaved polymorpic class should."

"As it turns out, there are a number of solutions, and Int2Type provides a
particularly clean one. It can transform ad hoc the Boolean value isPolymorphic
into two distinct types corresponding to isPolymorphic's true and false values.
Then you can use Int2Type<isPolymorphic> with simple overloading, and voila!"
//*/
template< typename T, bool isPolymorphic >
class NiftyContainer
{
private:
  // polymorphic
  void doSomething( T* pObj, Int2Type<true> )
  {
    std::cout << " - polymorphic algorithm, we use the clone()\n";
    T* pNewObj = pObj->clone();
    pNewObj->printContent();
    delete pNewObj; pNewObj = NULL;
  }

  // nonpolymorphic
  void doSomething( T* pObj, Int2Type<false> )
  {
    std::cout << " - nonpolymorphic algorithm, we use the copy ctor\n";
    T* pNewObj = new T(*pObj);
    pNewObj->printContent();
    delete pNewObj; pNewObj = NULL;
  }

public:
  // public interface
  void doSomething(T* pObj)
  {
    doSomething( pObj, Int2Type<isPolymorphic>() );
  }
};


/*
//*/
class GuineaPig
{
private:
  string str;

public:
  GuineaPig(const string& initStr);
  GuineaPig(GuineaPig const& fb);
  ~GuineaPig();

  GuineaPig* clone();
  void printContent() const;
};

GuineaPig::GuineaPig(const string& initStr)
{
  str = initStr;
}

// copy ctor
GuineaPig::GuineaPig(GuineaPig const& fb)
{
  std::cout << "\tGuineaPig::copy constructor\n";
  str = fb.str; // works due to copy ctor!!
  str += " (made by copy constructor)";
}

// dtor
GuineaPig::~GuineaPig()
{
  std::cout << "\tGuineaPig:: - destructor - \n";
}

// clone()
GuineaPig* GuineaPig::clone()
{
  std::cout << "\tGuineaPig::clone()\n";
  return new GuineaPig(this->str + " (made by clone())");
}

void GuineaPig::printContent() const
{
  cout << "\tGuineaPig::content() - \"" << str << "\"" << endl;
}




/*
some main..

"The trick works because the compiler does not compile template functions that
are never used - it only checks their syntax. And, of course, you usually
perform dispatch at compile time in template code."
//*/
int main()
{
  cout << "Integral Type To Any Type\n"
       << "\n"
       << "Nifty Container distinguishes the function to use internally by type\n"
       << "mapping / setting up of the container:\n"
       << endl;

  // init
  GuineaPig *gp = new GuineaPig("Hello World!");

  // call polymorphic
  NiftyContainer<GuineaPig, true>  niftyPolymorphic;
  niftyPolymorphic.doSomething(gp);
  cout << endl;

  // call nonpolymorphic
  NiftyContainer<GuineaPig, false> niftyNonpolymorphic;
  niftyNonpolymorphic.doSomething(gp);

  cout << "READY.\n";
  // free mem
  delete gp; gp = NULL;

  return 0;
}
