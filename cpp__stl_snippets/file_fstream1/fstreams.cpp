// fstreams.cpp
/*
  file streams

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
  ofstream out(filename, ios_base::out | ios_base::trunc);
  cout << endl;  
  
  cout << "write\n";
  if(out.is_open()){
    out << 1234567;
    out.close();
    cout << endl;

    cout << "read\n";
    ifstream in;
    in.open(filename);
    if(in){
      int val;
      in >> val;
      cout << val << endl;
      cout << endl;
    }
  } // in.close() happens automatically at exiting block

  cout << "READY.\n";
  return 0;
}
