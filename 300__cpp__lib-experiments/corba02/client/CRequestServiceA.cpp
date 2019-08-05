// CRequestServiceA.cpp
/*
//*/

#include "Data.hh"
#include "CRequestServiceA.h"

#include <cassert>



using namespace Data;

CRequestServiceA::CRequestServiceA()
{
  try{
    // init ORB - dummy
    int argc=0;
    char** argv=NULL;
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // bind ORB to name service object
    CORBA::Object_var obj = orb->resolve_initial_references("OmniNameService");
    assert(!CORBA::is_nil(obj.in()));

    // narrow to naming context
    CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj.in());
    assert(!CORBA::is_nil(nc.in()));

    // further binding
    CosNaming::Name _corbaCosName;
    _corbaCosName.length(1);
    _corbaCosName[0].id = CORBA::string_dup("DataServiceName1"); // calls malloc!

    // resolve name text identifier to an object reference
    CORBA::Object_var obj1 = nc->resolve(_corbaCosName);
    assert(!CORBA::is_nil(obj1.in()));

    m_Data = ServiceA::_narrow(obj1.in());
    if(CORBA::is_nil(obj1.in())){
      std::cerr << "IOR is not an SA object reference." << std::endl;
    }

  }catch(CORBA::COMM_FAILURE& ex){
    std::cerr << "client: caught system exception COMM_FAILURE - unable to contact the object." << std::endl;
    throw DS_ServerConnectionException();
    return;

  }catch(CORBA::SystemException&){
    std::cerr << "client: caught a CORBA::SystemException." << std::endl;
    throw DS_SystemException();
    return;

  }catch(CORBA::Exception&){
    std::cerr << "client: caught a CORBA::Exception." << std::endl;
    throw DS_Exception();
    return;

  }catch(omniORB::fatalException& ex){
    std::cerr << "client: caught omniORB::fatalException:" << std::endl
              << "\tfile: " << ex.file() << std::endl
              << "\tline: " << ex.line() << std::endl
              << "\tmesg: " << ex.errmsg() << std::endl;
    throw DS_FatalException();
    return;

  }catch(...){
    std::cerr << "client: caught unkown exception" << std::endl;
    throw DS_Exception();
    return;
  }
}


CRequestServiceA::~CRequestServiceA()
{
  // ...
}


bool CRequestServiceA::RequestServiceARoutineA()
{
  CORBA::Long num1 = 4;
  CORBA::Long num2 = 5;
  CORBA::Long retNum;

  std::cout << "client: values input to service routine A: "
            << num1 << " " << num2 << " " << retNum << std::endl;

  // remote CORBA call
  if( m_Data->CallServiceRoutineA( num1, num2, retNum)){
    std::cout << "client: vlaues returned by service routine A: "
              << num1 << " " << num2 << " " << retNum << std::endl;
    return true;

  }else{ // call failed!
    return false;
  }


  return true;
}



bool CRequestServiceA::RequestServiceARoutineB()
{
  CORBA::Long num1 = 0;
  CORBA::Long num2 = 50;

  std::cout << "client: values input to service routine B: "
            << num1 << " " << num2 << " " << std::endl;

  // remote call to server
  if(m_Data->CallServiceRoutineB( num1, num2)){
    std::cout << "client: values returned by service rotine B: "
              << num1 << " " << num2 << std::endl;
    return true;

  }else{ // call failed
    return false;
  }

  return true;
}



