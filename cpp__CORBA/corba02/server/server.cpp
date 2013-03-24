// server.cpp
/*
  IMPORTANT NOTE: 
  you must set a global variable, to be able to use the ORB, e.g. in the /etc/profile

  export OMNIORB_CONFIG=/etc/omniORB.cfg

  TODO: avoid using C here
//*/

// c headers
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>

//* cpp headers - TODO check
#include <iostream>
#include <string>
using namespace std; 
//*/

// costumized headers 
#include "CServiceA.h"
#include "Data.hh"

int main(int argc, char** argv)
{


  try{
    // 1. init ORB
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // 2. get reference to root POA, in order to be available for the client
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var _poa = PortableServer::POA::_narrow(obj.in());
 
    // 3. bind to name service
    // Invoke operations defined in object interface, via object reference
    // Instance of CRequestSocketStream_i servant is initialized
    CServiceA_i* myRequestServiceA = new CServiceA_i();
    PortableServer::ObjectId_var myRequestServiceA_oid = _poa->activate_object(myRequestServiceA);
    CORBA::Object_var SA_obj = myRequestServiceA->_this();
    CORBA::String_var sior(orb->object_to_string(SA_obj.in()));
    fprintf(stderr, "\'%s\'\n", static_cast< char* >(sior)); // TODO check - std::string??

    // (re)bind object (orb) to the name (SA_obj) via name service
    CORBA::Object_var obj1 = orb->resolve_initial_references("OmniNameService");
    assert(!CORBA::is_nil(obj1.in()));

    // narrow to naming context
    CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj1.in());
    assert(!CORBA::is_nil(nc.in()));

    // bind to CORBA name service
    CosNaming::Name name;
    name.length(1);
    name[0].id = CORBA::string_dup("DataServiceName1"); // string_dup does malloc()
    nc->rebind(name, SA_obj.in());
    myRequestServiceA->_remove_ref();

    // 4. init servant object
    PortableServer::POAManager_var pmgr = _poa->the_POAManager();
    pmgr->activate();

    // accept requests from clients
    orb->run();

    // 5. cleanup
    orb->destroy();

    // TODO check memory management(!!!)
    free(name[0].id); // string_dup() / malloc() - no nulling possible without explicitly defined operator=() !

  }catch(CORBA::SystemException&){
    fprintf(stderr, "server: caught CORBA::SystemException. - every idl function can throw a CORBA::SystemException.\n");

  }catch(CORBA::Exception&){
    fprintf(stderr, "server: caught CORBA::Exception.\n");

  }catch(omniORB::fatalException& fe){
    fprintf(stderr, "server: omniORB::fatalException:\n");
    fprintf(stderr, "\tfile: %s\n", fe.file());
    fprintf(stderr, "\tline: %s\n", fe.line());
    fprintf(stderr, "\tmesg: %s\n", fe.errmsg());

  }catch(...){
    fprintf(stderr, "server: caught unknown exception.\n");
  }
}


