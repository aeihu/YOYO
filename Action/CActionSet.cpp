/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CActionSet.h"

CActionSet::CActionSet()
{
    _name = "";
    _iterator = _actionList.begin();
}


string CActionSet::GetName() const
{
    return _name;
}

void CActionSet::SetName(string name)
{
    _name = name;
}

void CActionSet::SetPause(bool pause)
{
    _pauseRequest = pause;

    if (_pauseRequest)
        _numOfPauseActions++;
    else
        _numOfPauseActions--;
}
        
bool CActionSet::DeleteAct(string name, bool skip)
{
    if (name != ""){
        for (list<CActionBaseClass*>::iterator it=_actionList.begin();it!=_actionList.end();){
            if (name == (*it)->GetName()){
                if (skip){
                    (*it)->Skip();
                    (*it)->OnLoop();
                }

                (*it)->OnCleanup();
                delete (*it);
                (*it) = NULL;
                it = _actionList.erase(it);
            }
            else
                ++it;
        }

        return true;
    }

    return false;
}

void CActionSet::AddAction(CActionBaseClass* act)
{
    if (act != NULL){
        _actionList.push_back(act);
        _iterator = _actionList.begin();
    }
}

void CActionSet::OnCleanup()
{
    if (_actionList.empty())
        return;

    for (list<CActionBaseClass*>::iterator it = _actionList.begin(); it != _actionList.end(); it++){
        (*it)->OnCleanup();
        delete (*it);
        (*it) = NULL;
    }

    _actionList.clear();
}

bool CActionSet::CopyList(CActionSet* act)
{
    if (act){
        act->SetName(_name);
        act->SetPause(_pauseRequest);

        for (list<CActionBaseClass*>::iterator it = _actionList.begin(); it != _actionList.end(); it++)
            act->AddAction((*it)->Copy());

        return true;
    }

    return false;
}
