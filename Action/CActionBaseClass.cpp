#include "CActionBaseClass.h"
#include <iostream>

using namespace std;

int CActionBaseClass::_numOfPauseActions = 0;

CActionBaseClass::CActionBaseClass()
{
    _skip = _pauseRequest = false;
}

CActionBaseClass::~CActionBaseClass()
{
    if (_pauseRequest)
        _numOfPauseActions--;
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

int CActionBaseClass::GetNumberOfActionInPause()
{
    if (_numOfPauseActions < 0)
        cout << "CActionBaseClass::GetNumberOfActionInPause(): the number is less 0." << endl;

    return _numOfPauseActions;
}