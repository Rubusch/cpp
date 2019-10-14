// CServiceA.cpp
/*
  C++ (with mixed in C)
//*/

// cpp headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "CServiceA.h"

// TODO check
using namespace std;

#include <sys/wait.h>

CORBA::Boolean CServiceA_i::CallServiceRoutineA(CORBA::Long num1,
                                                CORBA::Long &num2,
                                                CORBA::Long &retNum)
{
  std::cout << "\tCallServiceRoutineA()\n";

  num2 = num2 + num1;
  retNum = 10;

  return true;
}

CORBA::Boolean CServiceA_i::CallServiceRoutineB(CORBA::Long &num1,
                                                CORBA::Long &num2)
{
  std::cout << "\tCallServiceRoutineB()\n";

  ++num1;
  ++num2;

  return true;
}
