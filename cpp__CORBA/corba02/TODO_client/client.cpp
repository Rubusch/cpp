// client.cpp
/*
//*/


#include "CRequestServiceA.h"


int main(int argc, char** argv)
{
  // establish link with CORBA server via ctor
  CRequestServiceA requestServiceA; 

  if(requestServiceA.RequestServiceARoutineA()){
    std::cout << "client: service A routine A - TRUE" << std::endl;
  }

  if(requestServiceA.RequestServiceARoutineB()){
    std::cout << "client: service A routine B - TRUE" << std::endl;
  }

  return 0;
}

