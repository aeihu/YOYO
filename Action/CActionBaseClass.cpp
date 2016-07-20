#include "CActionBaseClass.h"
#include <iostream>

using namespace std;

CActionBaseClass::CActionBaseClass()
{
    _skip = false;
}

CActionBaseClass::~CActionBaseClass()
{
}

string CActionBaseClass::GetName() const 
{ 
    return ""; 
}

void CActionBaseClass::Skip()
{ 
    _skip = true; 
}