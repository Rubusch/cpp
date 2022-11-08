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
  - the grammar is simple (for complex grammars parser generators are more
  usefull)
  - efficiency is not a critical concern.

  Similarities in the tree with chain of responsibility?!

  (GoF, 1995)
*/


#include <iostream>
#include <vector>


class Context
{
private:
  std::vector< std::string > content;
  std::string tmp;

public:
  void push(std::string word) { content.push_back(word); }

  std::string pop()
  {
    tmp = content.back();
    content.pop_back();
    return tmp;
  }
};


struct AbstractExpression {
  virtual bool interpret(Context *context) = 0;
  virtual ~AbstractExpression() {}
};


struct TerminalExpression_bool : public AbstractExpression {
  bool interpret(Context *context)
  {
    if (0 == (context->pop()).compare("TRUE")) {
      return true;
    }
    return false;
  }
};


class NonterminalExpression_equals : public AbstractExpression
{
private:
  AbstractExpression *pOperand1_, *pOperand2_;

public:
  NonterminalExpression_equals()
  {
    pOperand1_ = new TerminalExpression_bool;
    pOperand2_ = new TerminalExpression_bool;
  }

  ~NonterminalExpression_equals()
  {
    delete pOperand1_;
    pOperand1_ = NULL;
    delete pOperand2_;
    pOperand2_ = NULL;
  }

  bool interpret(Context *context)
  {
    return (pOperand1_->interpret(context) == pOperand2_->interpret(context));
  }
};


/*
  Client
*/
int main()
{
  using namespace std;

  Context context;
  context.push("TRUE");
  context.push("TRUE");
  context.push("EQUALS");

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
