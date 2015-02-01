/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CDrawableObjectControl.h"
#include <algorithm>
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Sound/CSoundBank.h"
#include "../Gui/CButton.h"
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Effect/CParticleSystem.h"
#include "../GSM_Window/CLogBox.h"

bool CDrawableObjectControl::IsExists(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name)
            return true;
    }

    return false;//_objectList.count(name) > 0;
}

bool CDrawableObjectControl::AddDrawableObject(string name, string objTypeName, string filename)
{
    CImageBaseClass* __obj = NULL;

    if (objTypeName == "Img") __obj = CImageBaseClass::Create(filename.c_str());
    else if (objTypeName == "Background") __obj = CImageBaseClass::Create(filename.c_str());
    else if (objTypeName == "Button") __obj = CButton::Create(filename.c_str());
    else if (objTypeName == "CharacterLayer") __obj = CCharacterLayer::Create(filename.c_str());
    else if (objTypeName == "LogBox") __obj = CLogBox::Create(filename.c_str());
    else if (objTypeName == "MessageBox") __obj = CMessageBox::Create(filename.c_str());
    else if (objTypeName == "ParticleSystem") __obj = CParticleSystem::Create(filename.c_str());

    if (__obj != NULL){
        //string __name = GetNameInFilename(filename);
        
        if (IsExists(name)){
            cout << "CResourceControl::AddDrawableObject(): " 
                << objTypeName << " \""<< name << "\" has existed." <<endl;
            delete __obj;
            return false;
        }

        _drawableObjectList.push_back(make_pair(objTypeName+":"+name, __obj));
        _isNeedSort = true;
        return true;
    }
    else
        cout << "CResourceControl::AddDrawableObject(): failed to create " 
            << objTypeName << "\"" << name << "\"." <<endl;

    return false;
}

bool CDrawableObjectControl::DelDrawableObject(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name){
            delete _drawableObjectList[i].second;
            _drawableObjectList.erase(_drawableObjectList.begin()+i);
            return true;
        }
    }

    return true;
}

CImageBaseClass* CDrawableObjectControl::GetDrawableObject(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name)
            return _drawableObjectList[i].second;
    }

    return NULL;
}

bool CDrawableObjectControl::SetDrawableObjectLayerOrder(string name, char layer)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name){
            _drawableObjectList[i].second->SetLayerOrder(layer);
            _isNeedSort = true;
            return true;
        }
    }
    return false;
}

bool CDrawableObjectControl::OnLButtonUp(int mX, int mY)
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin() ; it != _drawableObjectList.end();it++)
        if ((*it).second->OnLButtonUp(mX, mY))
            return true;

    return false;
}

bool CDrawableObjectControl::OnLButtonDown(int mX, int mY)
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin() ; it != _drawableObjectList.end();it++)
        if ((*it).second->OnLButtonDown(mX, mY))
            return true;

    return false;
}

bool CDrawableObjectControl::OnMouseMove(int mX, int mY)
{
    //for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin() ; it != _drawableObjectList.end();it++)
    //    if ((*it).second->OnLButtonDown(mX, mY))
    //        return true;

    return false;
}

void CDrawableObjectControl::OnLoop(bool &pause)
{
    if (_isNeedSort){
        std::sort(_drawableObjectList.begin(), _drawableObjectList.end(), _sort);
        _isNeedSort = false;
    }

    vector<pair<string, CImageBaseClass*> >::iterator it;
    for ( it=_drawableObjectList.begin(); it !=_drawableObjectList.end(); it++ ){
        if((*it).second->OnLoop()) 
            pause=true;
    }
}

void CDrawableObjectControl::OnRender(sf::RenderTarget* Surf_Dest)
{
    sf::View __tmpView = Surf_Dest->getView();
    bool __b = true;
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++){
            if ((*it).second->GetLayerOrder() < 100){
                (*it).second->OnRender(Surf_Dest);
            }
            else{
                if (__b){
                    Surf_Dest->setView(Surf_Dest->getDefaultView());
                    __b = false;
                }
                (*it).second->OnRender(Surf_Dest);
            }
    }
    Surf_Dest->setView(__tmpView);
}

void CDrawableObjectControl::OnCleanup()
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++){
            delete (*it).second;
    }

    _drawableObjectList.clear();
}
