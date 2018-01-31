// server.cpp
/*
//*/

#include <time>
#include <iostream>

#include "timeS.hh"

/*
  necessary since get_gmt() is pure virtual in the idl file
//*/
class Time_impl : public virtual POA_Time{
public:
  virtual TimeOfDay get_gmt()
    throw(CORBA::SystemException);
};


/*
  the derived time implemenetation (bridge pattern) uses the
  following implementation
//*/
TimeOfDay Time_impl::get_gmt()
  throw(CORBA::SystemException)
{
  time_t time_now = time(0);
  struct tm* time_p = gmtime(&time_now);

  TimeOfDay tod;
  tod.hour = time_p->tm_hour;
  tod.minute = time_p->tm_min;
  tod.second = time_p->tm_sec;

  return tod;
}


/*
  the server main function
//*/
int main(int argc, char** argv)
{
  try{
    // init orb
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // get ref to root POA
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    // activate POA manager
    PortableServer::POAManager_var mgr = poa->the_POAManager();
    mgr->activate();

    // create an object
    Time_impl time_servant;

    // write its stringified reference to stdout
    Time_var tm = time_servant._this();
    CORBA::String_var str = orb->object_to_string(tm);
    std::cout << str << std::endl;

    // accept requests
    orb->run();

  }catch( const CORBA::Exception&){
    std::cerr << "server: uncaught CORBA exception" << std::endl;
    return 1;

  }catch(...){
    std::cerr << "server: uncaught exception" << std::endl;
    return 1;
  }

  return 0;
}
