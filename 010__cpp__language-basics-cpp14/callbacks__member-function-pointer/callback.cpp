/*
  callbacks in cpp

  example based on the example of the blog post of davis vigneault on the topic

  resources:
  https://sudomakeinstall.io/posts/2017/11/30/callbacks-in-cpp11/
  davis.vigneault@gmail.com, blog post, 2017 Effective Modern C++, Scott Meyers,
  2015 cppreference.com, 2019
 */

#include <cstdlib>
#include <functional> /* function pointer */
#include <iostream>
#include <math.h>
#include <vector> /* vector of function pointers */

using namespace std;

class MemberFunctionPointer
{
public:
  void call(const size_t iteration, const double guess)
  {
    cout << iteration << " : " << guess << " (member function)" << endl;
  }
};

class SquareRoot
{
public:
  // function pointer: 'returntype (parameters)'
  using TCallback = std::function< void(const size_t, const double) >;

  // vector of function pointers to make them interchangeable
  using TCallbackVector = vector< TCallback >;

  void add_callback(TCallback cb) { m_callbacks.push_back(cb); }

  // main logic of class.
  double run(const double input)
  {
    if (input < 0.0)
      throw 0;            // error checking
    this->iteration = 0;  // reset iteration number
    double guess = input; // set initial guess to input

    // heron algorithm
    while (std::fabs(guess - input / guess) > this->epsilon) {
      for (const auto &cb : m_callbacks) {
        // ideally: different "printers" could be in the callbacks list, the
        // for-loop would call all of them at each while-iteration
        cb(iteration, guess);
      }
      guess = (guess + input / guess) / 2.0;
      ++iteration;
    }
    return guess;
  }

private:
  const double epsilon = 1e-6; // maximum allowed error.
  size_t iteration = 0;        // iteration number.

  // interchangeable callbacks
  TCallbackVector m_callbacks;
};


int main()
{
  SquareRoot sr;

  // member function callback, needs a temporary instance
  MemberFunctionPointer cb_tmp;

  // then a connection via std::bind() for passing the arguments
  auto cb = std::bind(&MemberFunctionPointer::call, &cb_tmp,
                      std::placeholders::_1, std::placeholders::_2);
  sr.add_callback(cb);

  std::cout << "Result: " << sr.run(1234.5 * 1234.5) << std::endl;

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
