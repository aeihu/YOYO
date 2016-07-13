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
    _isDelete = true;
    _name = "";
    _iterator = _actionList.begin();
}


string CActionSet::GetName() const
{
    return _name;
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
        if (this->GetType() == ACTION_REP){
            SetIsDelete(act,  false);
        }
        
        _actionList.push_back(act);
        _iterator = _actionList.begin();
    }
}

void CActionSet::SetIsDelete(CActionBaseClass* act, bool b)
{
    if (act){
        if (act->GetType() == ACTION_SEQ || 
            act->GetType() == ACTION_SIM ||
            act->GetType() == ACTION_REP){
            CActionSet* __actset = static_cast<CActionSet*>(act);
            __actset->_isDelete = b;

            for (list<CActionBaseClass*>::iterator it = __actset->_actionList.begin();
                it != __actset->_actionList.end(); it++){

                if ((*it)->GetType() == ACTION_SEQ ||
                    (*it)->GetType() == ACTION_SIM ||
                    (*it)->GetType() == ACTION_REP){
                    SetIsDelete((*it), b);
                }
            }
        }
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
        for (list<CActionBaseClass*>::iterator it = _actionList.begin(); it != _actionList.end(); it++)
            act->AddAction((*it)->Copy());

        return true;
    }

    return false;
}
bool CActionSet::IsDelete() const
{
    return _isDelete;
}
