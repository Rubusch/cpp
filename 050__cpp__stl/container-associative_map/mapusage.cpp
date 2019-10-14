// mapusage.cpp
/*
  demonstrates a map

  +-----------------+----------------+------------------+
  |                 | one occurance  | more occurances  |
  |                 |                |                  |
  +-----------------++================+=================+
  | only keys       || set            | multiset        |
  +-----------------++----------------+-----------------+
  | keys and values || map            | multimap        |
  +-----------------++----------------+-----------------+

  resources: Kuhlins and Schader (2003)
//*/


#include <iostream>
#include <map>
#include <string>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  map< string, string > telefonebook;

  // insertpossibilities
  cout << "insertion #1\n";
  telefonebook.insert(pair< const string, string >("tick", "123"));
  cout << endl;

  cout << "insertion #2\n";
  telefonebook.insert(make_pair(string("trick"), string("456")));
  cout << endl;

  cout << "insertion #3\n";
  telefonebook.insert(map< string, string >::value_type("track", "789"));
  cout << endl;

  cout << "check if insert was successfull\n";
  map< string, string >::value_type val_t("foo", "bar");
  if (telefonebook.insert(val_t).second) {
    cout << "successfull\n";
  }
  cout << endl;

  cout << "check if already in list\n";
  const pair< map< string, string >::iterator, bool > pa =
      telefonebook.insert(val_t);
  if (!pa.second) {
    cout << "\"" << pa.first->first << "\" is already in the list with value \""
         << pa.first->second << "\"" << endl;
  }
  cout << endl;

  cout << "READY.\n";
  return 0;
}
