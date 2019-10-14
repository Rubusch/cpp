// stringascontainer.cpp
/*
  string as container

  resources: Kuhlins and Schader (2003)
//*/

#include <algorithm>
#include <cctype> // toupper
#include <iostream>
#include <iterator>
#include <string>


/*
  main..
//*/
int main()
{
  using namespace std;

  cout << "init\n";
  const char szText[] = "Jack and Jill went up the hill.";
  string strText(szText, szText + sizeof(szText) - 1);
  copy(strText.begin(), strText.end(), ostream_iterator< char >(cout));
  cout << endl << endl;

  cout << "find() - set an iterator to \'.\'\n";
  string::iterator iter;
  if (strText.end() != (iter = find(strText.begin(), strText.end(), '.'))) {
    cout << "found token \'.\' at index: " << (iter - strText.begin()) << endl;
  }
  cout << "-> \'.\' is the last token, it is NOT str.end()!!!\n";
  cout << endl;

  /*
    transform(strText.begin(), strText.end(), strText.begin(), toupper);

    Doesn't compile because toupper is ambiguous! It can either refer to

    #include <cctype>
    ...
    int std::toupper(int);

    or

    #include <locale>
    ...
    template< class T >
    T std::toupper( T, const locale&);

    Therefore an explicit cast here!
  //*/
  cout << "transform()\n";
  transform(strText.begin(), strText.end(), strText.begin(),
            ( int (*)(int) )toupper);
  copy(strText.begin(), strText.end(), ostream_iterator< char >(cout));
  cout << endl << endl;

  cout << "reverse()\n";
  reverse(strText.begin(), strText.end());
  copy(strText.begin(), strText.end(), ostream_iterator< char >(cout));
  cout << endl << endl;

  cout << "replace() - \' \' with \'#\'\n";
  replace(strText.begin(), strText.end(), ' ', '#');
  copy(strText.begin(), strText.end(), ostream_iterator< char >(cout));
  cout << endl << endl;

  cout << "sort()\n";
  sort(strText.begin(), strText.end());
  copy(strText.begin(), strText.end(), ostream_iterator< char >(cout));
  cout << endl << endl;


  cout << "READY.\n";
  return 0;
}
