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
    _iterator = _actionList.begin();
}
        
bool CActionSet::DeleteAct(string name, bool skip)
{
    if (name != ""){
        bool __deleted = false;
        for (list<pair<CActionBaseClass*, bool> >::iterator it = _actionList.begin(); it != _actionList.end();){
            if (name == (*it).first->GetName()){
                if (skip){
                    (*it).first->SetSkip();
                    (*it).first->OnLoop();
                }

                (*it).first->OnCleanup();
                delete (*it).first;
                (*it).first = NULL;
                it = _actionList.erase(it);
                __deleted = true;
            }
            else
                ++it;
        }

        if (__deleted){
            for (list<pair<CActionBaseClass*, bool> >::iterator it = _actionList.begin(); it != _actionList.end();){
                if ((*it).second)
                    ++it;
                else{
                    _iterator = it;
                    return true;
                }
            }

            _iterator = _actionList.begin();
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
        
        _actionList.push_back(pair<CActionBaseClass*, bool>(act, false));
        if (_actionList.size() < 1);
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

            for (list<pair<CActionBaseClass*, bool> >::iterator it = __actset->_actionList.begin();
                it != __actset->_actionList.end(); it++){

                if ((*it).first->GetType() == ACTION_SEQ ||
                    (*it).first->GetType() == ACTION_SIM ||
                    (*it).first->GetType() == ACTION_REP){
                    SetIsDelete((*it).first, b);
                }
            }
        }
    }
}

void CActionSet::OutAllActions()
{
    for (list<pair<CActionBaseClass*, bool> >::iterator it = _actionList.begin(); it != _actionList.end(); it++){
        (*it).first->OutAllActions();
    }

    for (list<CActionBaseClass*>::iterator it = _allActions.begin(); it != _allActions.end(); it++){
        if ((*it) == this){
            _allActions.erase(it);
            return;
        }
    }
}

void CActionSet::OnCleanup()
{
    if (_actionList.empty())
        return;

    for (list<pair<CActionBaseClass*, bool> >::iterator it = _actionList.begin(); it != _actionList.end(); it++){
        (*it).first->OnCleanup();
        delete (*it).first;
        (*it).first = NULL;
    }

    _actionList.clear();
}

bool CActionSet::CopyList(CActionSet* act)
{
    if (act && _actionList.size() > 0){
        for (list<pair<CActionBaseClass*, bool> >::iterator it = _actionList.begin(); it != _actionList.end(); it++)
            act->AddAction((*it).first->Copy());

        return true;
    }

    return false;
}
bool CActionSet::IsDelete() const
{
    return _isDelete;
}

void CActionSet::RestoreActionList()
{
    for (list<pair<CActionBaseClass*, bool> >::iterator it = _actionList.begin(); it != _actionList.end(); it++){
        (*it).second = false;

        if ((*it).first->GetType() == ACTION_SEQ ||
            (*it).first->GetType() == ACTION_SIM ||
            (*it).first->GetType() == ACTION_REP)
        {
            ((CActionSet*)(*it).first)->RestoreActionList();
        }
    }
}
