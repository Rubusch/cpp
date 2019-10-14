// client.cpp
/*
//*/

#include <iomanip>
#include <iostream>

#include "time.hh"


int main(int argc, char **argv)
{
  try {

    // check arguments
    if (2 != argc) {
      std::cerr << "usage: client IOR_string" << std::endl;
      throw 0;
    }

    // init orb
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // destringify argv[1]
    CORBA::Object_var obj = obj->string_to_object(argv[1]);
    if (CORBA::is_nil(obj)) {
      std::cerr << "nil time reference" << std::endl;
      throw 0;
    }

    // narrow
    Time_var tm = Time::_narrow(obj);
    if (CORBA::is_nil(tm)) {
      std::cerr << "argument is not a time reference" << std::endl;
      throw 0;
    }

    // get time
    TimeOfDay tod = tm->get_gmt();
    std::cout << "time in greenwich is " << std::setw(2) << std::setfill('0')
              << tod.hour << ":" << std::setw(2) << std::setfill('0')
              << tod.minute << ":" << std::setw(2) << std::setfill('0')
              << tod.second << std::endl;

  } catch (const CORBA::Exception &) {
    std::cerr << "client: uncaught CORBA exception" << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "client: uncaught exception" << std::endl;
    return 1;
  }

  return 0;
}
