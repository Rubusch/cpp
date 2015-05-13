// callback.cpp
/*
  "Callbacks are executable code that is passed as an argument to 
  other code. It allows a lower-level software layer to cal a 
  subroutine (or function) defined in a higher-level layer."

  The following example will be replaced by a callback approach.

  source en.wikipedia.org
//*/


#include <iostream>


/*
  Library code - lower layer
//*/
int traverseWith(int array[]
                 , size_t length
                 , bool (*callback)(int index, int item, void* param)
                 , void* param)
{
  std::cout << "\ttraverseWith()\n";

  std::cout << "\t               - searching via callback\n";
  int exitCode = 0;
  for(unsigned int idx=0; idx < length; ++idx){
    std::cout << "\t               - idx: " << idx << std::endl;
    exitCode = callback(idx, array[idx], param);
    std::cout << "\t               - exitCode[" << exitCode << "] != 0, " << ((exitCode != 0) ? "true" : "false") << std::endl;
    if(exitCode != 0){
      std::cout << "\t               -> BREAK\n";
      break;
    }
  }
  std::cout << "\ttraverseWith() - done.\n";
  return exitCode;
}


/*
  application code - higher layer
//*/
bool search( int index, int item, void* param)
{
  std::cout << "\t\tcallback function pointer: search()\n";
  if( item > 5){
    *(int*) param = index;
    return true;
  }else{
    return false;
  }
  std::cout << "\t\tcallback function pointer: search() - done.\n";
}


/*
  in some other function
//*/
int main()
{
  std::cout << "Callback Example\n"
            << "A callback function is passed itself as param and returns the result of a lower layer operation.\n\n";

  const int length = 10;
  int array[length];

  int index;
  int found = traverseWith( array, length, &search, &index);
  if(found){
    std::cout << "array[" << index << "] - " << array[index] << std::endl;
  }else{
    std::cout << "not found\n";
  }

  std::cout << "READY.\n";
  return 0;
}

