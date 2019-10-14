// callback.cpp
/*
  "Callbacks are executable code that is passed as an argument to
  other code. It allows a lower-level software layer to cal a
  subroutine (or function) defined in a higher-level layer."

  The version here shows the original code, to use callbacks
  internally.

  source en.wikipedia.org
//*/


#include <iostream>


int main()
{
  const int length = 10; // to something
  const int exitCode = 7;

  int array[length];

  std::cout << "\t               - searching w/o callback\n";
  int idx;
  for (idx = 0; idx < length; ++idx) {
    std::cout << "\t               - exitCode < array[" << idx << "], "
              << exitCode << " < " << array[idx] << ", - "
              << ((exitCode < array[idx]) ? "true" : "false") << std::endl;
    if (exitCode < array[idx]) {
      std::cout << "\t               -> BREAK\n";
      break;
    }
  }

  if (idx < length) {
    std::cout << "item " << idx << " - " << array[idx] << std::endl;
  } else {
    std::cout << "not found\n";
  }

  std::cout << "READY.\n";
  return 0;
}
