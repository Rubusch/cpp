// CRequestServiceA.h
/*
  Supposed to be pure C++!
//*/

#ifndef _C_REQUEST_SERVICE_A_H_
#define _C_REQUEST_SERVICE_A_H_

#include <iostream>
#include <fstream>

#include "Data.hh"

// TODO check rm
using namespace std;

class CRequestServiceA
{
public:
  CRequestServiceA();  
  ~CRequestServiceA();

  bool RequestServiceARoutineA();
  bool RequestServiceARoutineB();
 
  //private: // TODO check
  CosNaming::Name m_corbaCosName;

  // CORBA ORB
  CORBA::ORB_var m_orb;
  CORBA::Object_var m_obj; // ORB object
  CORBA::Object_var m_obj1; // Resolved id to object reference
  
  // Resolved and narrowed CORBA object for proxy calls
  Data::ServiceA_var m_Data;
};


/*
  DS_ServerConnectionException
//*/
class DS_ServerConnectionException
{
public:
  DS_ServerConnectionException()
  {
    std::cerr << "CORBA COMM_FAILURE" << std::endl; 
  }
};


/*
  DS_SystemException
//*/
class DS_SystemException
{
public:
  DS_SystemException() 
  {
    std::cerr << "CORBA Exception" << std::endl;
  }
};


/*
  DS_FatalException
//*/
class DS_FatalException
{
public:
  DS_FatalException()
  {
    std::cerr << "CORBA Fatal Exception" << std::endl;
  }
};


/*
  DS_Exception
//*/
class DS_Exception
{
public:
  DS_Exception()
  {
    std::cerr << "Exception" << std::endl;
  }
};

#endif

