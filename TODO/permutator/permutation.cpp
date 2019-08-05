// permutation.cpp
/*
//*/

#include <iostream>
#include <fstream> // file i/o

#include <list>
#include <vector>

#include <iterator> // output

#include <cmath> // ???

#define PATTERN_LEN 4

// TODO make use of <algorithm>                 
// TODO class
// TODO implement via lambda


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

  // read from file
  string filename(argv[1]);
  list< char > ressource; // TODO use vector instead of list and solve "unique" problem -> copy_unique??

  // read w/o ' ' and '\n'
  ifstream in; in.open(filename.c_str());
  char ch;
  while(in){
    in >> ch;
    ressource.push_back(ch);
  }
  in.close();

  // prepare "ressource"
  ressource.sort();
  ressource.unique();

  // init vector
  // first  - value
  // second - number
  vector< pair< char, int > > pattern;
  for(uint16_t idx=0; idx<PATTERN_LEN; ++idx){
    pattern.push_back( pair< char, int >( ressource.front(), 0));
  }

  // highest number

  uint32_t ndigits = PATTERN_LEN;
  uint32_t nchars = ressource.size();
  uint32_t highest_num = pow( static_cast< long double >(nchars), static_cast< long double >(ndigits));
  int32_t digit = 0;
  uint32_t chr_sec =0;
  //  list< char >::iterator iter = ressource.begin();

  while(1){
    digit = ndigits-1;
    chr_sec = pattern.at(digit).second;
    ++chr_sec;
    if(chr_sec >= nchars){ // zero
      pattern.at(digit).first = ressource.front();
      pattern.at(digit).second = 0;

      --digit;
      chr_sec = pattern.at(digit).second;
      ++chr_sec;
      if(chr_sec >= nchars){
        pattern.at(digit).first = ressource.front();
        pattern.at(digit).second = 0;

        --digit;
        chr_sec = pattern.at(digit).second;
        ++chr_sec;
        if(chr_sec >= nchars){
          pattern.at(digit).first = ressource.front();
          pattern.at(digit).second = 0;

          --digit;
          chr_sec = pattern.at(digit).second;
          ++chr_sec;
          if(chr_sec >= nchars){// ndigits <= 0
            break;

          }else{ // increment
            ++pattern.at(digit).second;
            //            pattern.at(digit).first = ressource.at( pattern.at(digit).second);
          }

        }else{ // increment
          ++pattern.at(digit).second;
          //          pattern.at(digit).first = ressource.at( pattern.at(digit).second);
        }

      }else{
        ++pattern.at(digit).second;
        //          pattern.at(digit).first = ressource.at( pattern.at(digit).second);
        // TODO
      }

    }else{
      ++pattern.at(digit).second;
      //          pattern.at(digit).first = ressource.at( pattern.at(digit).second);
      // TODO

    }

    for(uint16_t idx=0; idx < pattern.size(); ++idx){ cout << pattern.at(idx).first << " "; }
    cout << endl;

    /*
    for(uint16_t idx=0; idx < pattern.size(); ++idx){ cout << pattern.at(idx).second << "\t"; }
    cout << endl;
    //*/

    //   break;
  }
  // permutate
  //  vector< pair > result;
  // int16_t idx=0;
  //  for
  // TODO


  // ressource
  cout << "READY.\n";

  return 0;
}
