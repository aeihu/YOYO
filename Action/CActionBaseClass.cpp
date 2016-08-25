/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CActionBaseClass.h"
#include <iostream>

using namespace std;

bool CActionBaseClass::_allSkip = false;
list<CActionBaseClass*> CActionBaseClass::_allActions;

CActionBaseClass::CActionBaseClass()
{
    _name = "";
    _skip = false;
}

CActionBaseClass::~CActionBaseClass()
{
}

void* CActionBaseClass::operator new(size_t size)
{
    _allActions.push_back((CActionBaseClass*)::operator new(size));
    return _allActions.back();
}

void CActionBaseClass::operator delete(void *ptr)
{
    for (list<CActionBaseClass*>::iterator it = _allActions.begin(); it != _allActions.end(); it++){
        if ((*it) == ptr){
            (*it)->OnCleanup();
            delete ptr;
            (*it) = NULL;
            _allActions.erase(it);
            return;
        }
    }
}

void CActionBaseClass::GC()
{
    while (_allActions.size() > 0){
        delete _allActions.front();
    }
}

void CActionBaseClass::OutAllActions()
{
    for (list<CActionBaseClass*>::iterator it = _allActions.begin(); it != _allActions.end(); it++){
        if ((*it) == this){
            _allActions.erase(it);
            return;
        }
    }
}

void CActionBaseClass::ClearListOfAllActions()
{
    _allActions.clear();
}

void CActionBaseClass::ClearListOfActions(CActionBaseClass* act)
{
    act->OutAllActions();
}

string CActionBaseClass::GetName() const 
{ 
    return _name;
}

void CActionBaseClass::SetName(string name)
{
    _name = name;
}

void CActionBaseClass::SetSkip()
{ 
    _skip = true; 
}

void CActionBaseClass::AllSkipOn()
{
    _allSkip = true;
}

void CActionBaseClass::AllSkipOff()
{
    _allSkip = false;
}