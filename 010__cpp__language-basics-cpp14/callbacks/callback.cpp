/*
  callbacks in cpp

  resources:
  https://sudomakeinstall.io/posts/2017/11/30/callbacks-in-cpp11/ , blog post, 2017
  Effective Modern C++, Scott Meyers, 2015
  cppreference.com, 2019
 */

#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;


// TODO           

class SquareRoot {
public:
  // main logic of class.
  double run(const double input) {
    if (input < 0.0) throw 0; // error checking.
    this->iteration = 0;      // reset iteration number.
    double guess = input;     // set initial guess to input.
    // heron algorithm
    while (std::fabs(guess - input/guess) > this->epsilon) {
      guess = (guess + input / guess) / 2.0;
      ++iteration;
    }
    return guess;
  }

private:
  const double epsilon = 1e-6; // maximum allowed error.
  size_t iteration = 0;        // iteration number.
};


int main() {
  SquareRoot p;
  std::cout << "Result: " << p.run(1234.5*1234.5) << std::endl;

  cout << "READY." << endl;
  return EXIT_SUCCESS;
}
