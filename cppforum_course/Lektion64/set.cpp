// set.cpp
/*
  Verwendet eine Initialisierungsliste
//*/

#include <iostream>
using namespace std;

#include "set.h"
#include "vector.h"

Set::Set()
    :m_data(10)
{
    m_size=0;
};
