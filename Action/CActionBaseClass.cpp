#include "CActionBaseClass.h"
#include <iostream>

using namespace std;

CActionBaseClass::CActionBaseClass()
{
    _name = "";
    _skip = false;
}

CActionBaseClass::~CActionBaseClass()
{
}

string CActionBaseClass::GetName() const 
{ 
    return _name;
}

void CActionBaseClass::SetName(string name)
{
    _name = name;
}

void CActionBaseClass::Skip()
{ 
    _skip = true; 
}