// CServiceA.h
/*
//*/

// TODO include guard???
#ifndef __CSERVICEA_H
#define __CSERVICEA_H

// TODO check
//#ifdef _cplusplus_

#include "Data.hh"

class CServiceA_i : public POA_Data::ServiceA,
                    public PortableServer::RefCountServantBase
{
public:
  CServiceA_i() {}

  virtual ~CServiceA_i() {}

  virtual CORBA::Boolean CallServiceRoutineA(CORBA::Long num1 // in
                                             ,
                                             CORBA::Long &num2 // inout
                                             ,
                                             CORBA::Long &retNum); // out

  virtual CORBA::Boolean CallServiceRoutineB(CORBA::Long &num1 // inout
                                             ,
                                             CORBA::Long &num2); // inout
};

#endif
