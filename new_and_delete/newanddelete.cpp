// newanddelete.cpp
/*
  Use the same form in corresponding uses of new and delete.

  (5/Meyers)
//*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
  // allocate space for a..
  //   ..dynamic string
  string *pStr = new string;

  //   ..dynamic string array
  string *pStrArr = new string[12];

  // init
  //   ..string
  *pStr = "Hello World!";

  //   ..array
  pStrArr[0] = "January";
  pStrArr[1] = "February";
  pStrArr[2] = "March";
  pStrArr[3] = "April";
  pStrArr[4] = "May";
  pStrArr[5] = "June";
  pStrArr[6] = "July";
  pStrArr[7] = "August";
  pStrArr[8] = "September";
  pStrArr[9] = "October";
  pStrArr[10] = "November";
  pStrArr[11] = "December";

  // output
  //   ..string
  cout << "string: " << *pStr << endl;

  //   ..array
  cout << "array: ";
  for(int idx = 0; 12 > idx; ++idx){
    cout << pStrArr[idx] << " ";
  }
  cout << endl;

  // free the allocated memory AND RESET to NULL!
  delete pStr; 
  pStr = NULL;

  delete [] pStrArr;
  pStrArr = NULL;

  // Remember a "double delete" is Killaah! The only possibility to avoid issues with "double 
  // deletes" is to set the pointer to NULL. A "delete NULL" is ALWAYS possible!
  delete pStr;
  delete pStrArr;
 
  cout << "READY.\n";
  return 0;
}
