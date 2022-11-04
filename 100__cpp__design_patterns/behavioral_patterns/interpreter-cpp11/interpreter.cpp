// inerpreter.cpp
/*
  Given a language, define a representation for its grammar along with
  an interpreter that uses the representation to interpret sentences
  in the language.

                         +---------------------+
                +------->| Context             |
                |        +=====================+
                |        |                     |
                |        +---------------------+
                |        |                     |
                |        +---------------------+
  +--------+    |
  | Client |----+
  +--------+    |
                |        +---------------------+
                +------->| AbstractExpression  |<------------------+
                         +=====================+                   |
                         |                     |                   |
                         +---------------------+                   |
                         | interpret(Context*) |                   |
                         +---------------------+                   |
                                   /_\                             |
                                    |                              |
                      +-------------+--------------+               |
                      |                            |               |
          +---------------------+       +---------------------+    |
          | Terminal            |       | Nonterminal         |<>--+
          |   Expression        |       |   Expression        |
          +=====================+       +=====================+
          |                     |       |                     |
          +---------------------+       +---------------------+
          | interpret(Context*) |       | interpret(Context*) |
          +---------------------+       +---------------------+

  Indications:
  - the grammar is simple (for complex grammars parser generators are
    more usefull)
  - efficiency is not a critical concern.

  Similarities in the tree with chain of responsibility?!

  (GoF, 1995)
*/


#include <iostream>
#include <vector>


/*
  Context

  - contains information that's global to the interpreter
*/
class Context
{
private:
  std::vector< std::string > content;
  std::string tmp;

public:
  void push(std::string word)
  {
    std::cout << "\tContext::push( std::string)\n";
    content.push_back(word);
  }

  std::string pop()
  {
    std::cout << "\tContext::pop()\n";
    tmp = content.back();
    content.pop_back();
    return tmp;
  }
};


/*
  AbstractExpression

  - declares an abstract Interpret operation that is common to all
    nodes in the abstract syntax tree
*/
class AbstractExpression
{
public:
  virtual ~AbstractExpression() = default;
  virtual bool interpret(Context *context) = 0;
};


/*
  TerminalExpression / LiteralExpression

  - implements an Interpret operation associated with terminal symbols
    in the grammar
  - an instance is required for every terminal symbol in a sentence
*/
class TerminalExpression_bool : public AbstractExpression
{
public:
  bool interpret(Context *context) override
  {
    std::cout << "\tTerminalExpression_bool::interpret( Context*);\n";
    if (0 == (context->pop()).compare("TRUE")) {
      return true;
    }
    return false;
  }
};


/*
  NonterminalExpression / AlternationExpression

  - one such class is required for every rule R ::= R1 R2 ... Rn in
    the grammar
  - maintains instance variables of type AbstractExpression for each
    of the symbols R1 through Rn
  - implements an Interpret operation for nonterminal symbols in the
    grammar. Interpret typically calls itself recursively on the
    variables representing R1 through Rn
*/
class NonterminalExpression_equals : public AbstractExpression
{
private:
  AbstractExpression *pOperand1_, *pOperand2_;

public:
  NonterminalExpression_equals()
  {
    std::cout << "\tNonterminalExpression_equals::NonterminalExpression_equals("
                 "AbstractExpression*) - ctor\n";
    pOperand1_ = new TerminalExpression_bool;
    pOperand2_ = new TerminalExpression_bool;
  }

  ~NonterminalExpression_equals() override
  {
    std::cout << "\tNonterminalExpression_equals::~NonterminalExpression_"
                 "equals() - dtor\n";
    delete pOperand1_;
    pOperand1_ = nullptr;
    delete pOperand2_;
    pOperand2_ = nullptr;
  }

  bool interpret(Context *context) override
  {
    std::cout << "\tNonterminalExpression_equals::interpret( Context*)\n";
    return (pOperand1_->interpret(context) == pOperand2_->interpret(context));
  }
};


/*
  Client

  - builds (or is given) an abstract syntax tree representing a
    particular sentence in the language that the grammar defines. The
    abstract syntax tree is assembled from instances of the
    NonterminalExpression and TerminalExpression classes.
  - invokes the Interpret operation
*/
int main()
{
  using namespace std;

  cout << "init..\n";
  Context context;
  context.push("TRUE");
  context.push("TRUE");
  context.push("EQUALS");
  cout << endl;

  if (0 == (context.pop()).compare("EQUALS")) {
    // in case the sequence in our grammar would end with EQUALS
    NonterminalExpression_equals start;
    cout << "-> result: \'"
         << (start.interpret(&context) ? ("true") : ("false")) << "\'\n";
    cout << endl;

  } else {
    cout << "not interpretable with our grammar\n";
  }

  cout << "READY.\n";
  return 0;
}
