// streamformatting.cpp
/*
  stram formatting

  - remmember use sentry to clean up a stream on exception calls before a regular clean up
  - don't throw exceptions in destructors (stack unwinding crashes the proggy!)

  (Kuhlins & Schader, 2003)
//*/


#include <iostream>


/*
  main..
//*/
int main()
{
  using namespace std;
  
  cout << "init\n";
  const ios_base::fmtflags standard_flags = cout.flags();
  cout << "bool: " << boolalpha << true << " and " << boolalpha << false << endl;
  cout << endl << endl;


  const double dbl = 123.456;
  cout << "float: " << dbl << endl;
  cout << endl;

  cout.setf(ios_base::showpoint);
  const streamsize standard_precision = cout.precision(8);
  cout << "\t8 digits: " << dbl << endl;
  cout << endl;

  cout.precision(2);
  cout << "\t2 digits: " << dbl << endl;
  cout << endl;

  cout.setf(ios_base::scientific, ios_base::floatfield);
  cout << "\tscientific, 2 digits: " << dbl << "\n";
  cout << endl;

  cout.setf(ios_base::fixed, ios_base::floatfield);
  cout << "\tfixed, 2 digits: " << dbl << " (rounded!)\n";
  cout << endl << endl;


  const long lng = 135246;
  cout << "long: " << lng << endl;
  cout << endl;

  cout.setf(ios_base::hex, ios_base::basefield);
  cout << "\thexadezimal: " << lng << endl;
  cout << endl;

  cout.setf(ios_base::oct, ios_base::basefield);
  cout << "\toctal: " << lng << endl;
  cout << endl;

  cout.setf(ios_base::dec, ios_base::basefield);
  cout << "\tdezimal: " << lng << endl;
  cout << endl;
  
  cout.setf(ios_base::showpos);
  cout << "\tsigned positive: " << lng << ", another number: " << 0 << endl;
  cout << endl << endl;

  
  cout << "alignment\n";
  cout.setf(ios_base::unitbuf);
  cout.setf(ios_base::right, ios_base::adjustfield);
  cout.width(10);
  cout << lng << " (right)\n";
  cout << endl;
  
  cout.setf(ios_base::internal, ios_base::adjustfield);
  cout.width(10);
  cout << lng << " (internal)\n";
  cout << endl;
  
  cout.setf(ios_base::left, ios_base::adjustfield);
  cout.width(10);
  cout << lng << " (left)\n";
  cout << endl << endl;
  

  cout << "reset again\n";
  cout.flags(ios_base::uppercase 
             | ios_base::hex 
             | ios_base::scientific);
  
  cout << "uppercase, hex and scientific: " << lng << ", " << dbl << endl;
  cout << endl << endl;


  cout.flags(standard_flags);
  cout.precision(standard_precision);
  cout << "again with presettings: " << lng << ", " << dbl << endl;
  cout << endl << endl;  

  
  cout << "READY.\n";
  return 0;
}
