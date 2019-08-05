// ifstream.cpp
/*
  reads a file with ' ' and '\n'
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

  ifstream in;
  in.open(filename.c_str());
  char ch;
  while(!in.eof()){
    in.get(ch);
    cout << ch;
  }
  in.close();
  cout << endl;

  cout << "READY.\n";

  return 0;
}
