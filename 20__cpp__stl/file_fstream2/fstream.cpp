// fstream.cpp
/*
  file streams - another example

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>
#include <fstream>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const char* const filename = "Jack.txt";
  fstream file(filename, ios_base::in | ios_base::out | ios_base::trunc);
  cout << endl;

  cout << "check...";
  if(!file){
    cerr << "error,\nfailed opening file " << filename << endl;

  }else{
    cout << "ok,\nwrite\n";
    file << 1234567;
    cout << endl;

    cout << "seekg() - go to file start\n";
    file.seekg(0, ios_base::beg); // go to file start
    cout << endl;

    cout << "read\n";
    int idx;
    file >> idx;
    cout << idx << endl;
    cout << endl;
  }

  cout << "READY.\n";
  return 0;
}
