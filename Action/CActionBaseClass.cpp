#include "CActionBaseClass.h"

int CActionBaseClass::_numOfPauseActions = 0;

CActionBaseClass::CActionBaseClass()
{
    _skip = _pauseRequest = false;
}

string CActionBaseClass::GetName() const 
{ 
    return ""; 
}

bool CActionBaseClass::PauseRequest() const
{ 
    return _pauseRequest; 
}

void CActionBaseClass::Skip()
{ 
    _skip = true; 
}