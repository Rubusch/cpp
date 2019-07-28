// ifstream.cpp
/*
  reads from a file without reading '\n' and spaces
//*/

#include <iostream>
#include <fstream> // file i/o


/*
  main
//*/
int main(int argc, char** argv)
{
  using namespace std;

  if(argc <= 1){
    cerr << "usage: prg <filename input>\n";
    return -1;
  }

  string filename(argv[1]);

  ifstream in; in.open(filename.c_str());
  char ch;
  while(in){
    in >> ch;
    cout << ch;
  }
  cout << endl;
  in.close();

  cout << "READY.\n";

  return 0;
}
