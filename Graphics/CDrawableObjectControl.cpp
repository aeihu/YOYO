/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CDrawableObjectControl.h"
#include <algorithm>
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Sound/CSoundBank.h"
#include "../Gui/CButton.h"
#include "../Gui/CText.h"
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Effect/CParticleSystem.h"
#include "../GSM_Window/CLogBox.h"
#include "../GSM_Window/CMessageBox.h"

bool CDrawableObjectControl::IsExists(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name)
            return true;
    }

    return false;
}

bool CDrawableObjectControl::AddDrawableObject(string name, string objTypeName, string filename)
{
    if (IsExists(objTypeName+":"+name)){
        return false;
    }

    CDrawableClass* __obj = NULL;

    if (objTypeName == "Img") __obj = CImgLayer::Create(filename.c_str());
    else if (objTypeName == "Button") __obj = CButton::Create(filename.c_str());
    else if (objTypeName == "CharacterLayer") __obj = CCharacterLayer::Create(filename.c_str());
    else if (objTypeName == "LogBox") __obj = CLogBox::Create(filename.c_str());
    else if (objTypeName == "MessageBox") __obj = CMessageBox::Create(filename.c_str());
    else if (objTypeName == "ParticleSystem") __obj = CParticleSystem::Create(filename.c_str());
    else if (objTypeName == "ScrEffect") __obj = CScreenEffect::Create(CCommon::_Common.SCREEN_PIECE_NUM, CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT);
    else if (objTypeName == "Text"){ 
        __obj = CText::Create();
        CText* __txt = static_cast<CText*>(__obj);
        __txt->SetFont("Font:"+filename);
    }

    if (__obj != NULL){
        _drawableObjectList.push_back(make_pair(objTypeName+":"+name, __obj));
        _isNeedSort = true;
        return true;
    }
    else
        cout << "CResourceControl::AddDrawableObject(): failed to create " 
            << objTypeName << " \"" << name << "\"." <<endl;

    return false;
}
        
bool CDrawableObjectControl::ResetDrawableObject(string name, string objTypeName)
{
    if (!IsExists(objTypeName+":"+name))
        return false;
    
    if (objTypeName == "Img"){
        CImgLayer* __obj = static_cast<CImgLayer*>(GetDrawableObject(objTypeName+":"+name));
        __obj->Reset();
    }
    else if (objTypeName == "Button"){
        CButton* __obj = static_cast<CButton*>(GetDrawableObject(objTypeName+":"+name));
        __obj->Reset();
    }
    else if (objTypeName == "CharacterLayer"){
        CCharacterLayer* __obj = static_cast<CCharacterLayer*>(GetDrawableObject(objTypeName+":"+name));
        __obj->Reset();
    }
    else if (objTypeName == "LogBox"){
    }
    else if (objTypeName == "MessageBox"){
        CMessageBox* __obj = static_cast<CMessageBox*>(GetDrawableObject(objTypeName+":"+name));
        __obj->Reset();
    }
    else if (objTypeName == "ParticleSystem"){
    }
    else if (objTypeName == "ScrEffect"){
    }
    else if (objTypeName == "Text"){ 
    }

    return true;
}

bool CDrawableObjectControl::DelDrawableObject(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name){
            _drawableObjectList[i].second->OnCleanup();
            delete _drawableObjectList[i].second;
            _drawableObjectList.erase(_drawableObjectList.begin()+i);
            return true;
        }
    }

    return true;
}

CDrawableClass* CDrawableObjectControl::GetDrawableObject(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name)
            return _drawableObjectList[i].second;
    }

    return NULL;
}

void CDrawableObjectControl::OnLoop()
{
    if (_isNeedSort){
        std::sort(_drawableObjectList.begin(), _drawableObjectList.end(), _sort);
        _isNeedSort = false;
    }

    vector<pair<string, CDrawableClass*> >::iterator it;
    for ( it=_drawableObjectList.begin(); it !=_drawableObjectList.end(); it++ )
        (*it).second->OnLoop();
}

void CDrawableObjectControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    sf::View __tmpView = Surf_Dest->getView();
    bool __b = true;
    for (vector<pair<string, CDrawableClass*> >::iterator it=_drawableObjectList.begin(); 
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
    for (vector<pair<string, CDrawableClass*> >::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++){
        (*it).second->OnCleanup();
        delete (*it).second;
        (*it).second = NULL;
    }

    _drawableObjectList.clear();
}

void CDrawableObjectControl::CleanActionList()
{
    for (vector<pair<string, CDrawableClass*> >::iterator it = _drawableObjectList.begin();
        it != _drawableObjectList.end(); it++)
        (*it).second->CleanActionList();
}

void CDrawableObjectControl::OnSaveData(Object& json) const
{
    Array __array;
    for (vector<pair<string, CDrawableClass*> >::const_iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++){
        Object __obj;
        (*it).second->OnSaveData(__obj);
        __obj << "name" << (*it).first;
        __array << __obj;
    }
    json << "visual_obj" << __array;
}

void CDrawableObjectControl::OnLoadData(Object json)
{
    if (json.has<Array>("visual_obj")){
        Array& __visualArr = json.get<Array>("visual_obj");

        for (size_t i=0; i<__visualArr.size(); i++){
            Object& __obj = __visualArr.get<Object>(i);
            if (IsExists(__obj.get<String>("name"))){
                CDrawableClass* __dra = CDrawableObjectControl::GetDrawableObject(__obj.get<String>("name"));
                __dra->OnLoadData(__obj);
            }
        }
    }
}

//================================================

bool CDrawableObjectControl::OnLButtonUp(int mX, int mY)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnLButtonUp(mX, mY)){
#ifdef _DEBUG
        cout << "OnLButtonUp: " << (*it).first << endl;
#endif
        return true;
    }

    return false;
}

bool CDrawableObjectControl::OnLButtonDown(int mX, int mY)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnLButtonDown(mX, mY)){
#ifdef _DEBUG
        cout << "OnLButtonDown: " << (*it).first << endl;
#endif
        return true;
    }

    return false;
}

bool CDrawableObjectControl::OnRButtonUp(int mX, int mY)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnRButtonUp(mX, mY)){
#ifdef _DEBUG
        cout << "OnRButtonUp: " << (*it).first << endl;
#endif
        return true;
    }

    return false;
}

bool CDrawableObjectControl::OnRButtonDown(int mX, int mY)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnRButtonDown(mX, mY)){
#ifdef _DEBUG
        cout << "OnRButtonDown: " << (*it).first << endl;
#endif
        return true;
    }

    return false;
}

bool CDrawableObjectControl::OnMouseMove(int mX, int mY)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnMouseMove(mX, mY))
        return true;

    return false;
}

bool CDrawableObjectControl::OnMButtonDown(int mX, int mY)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnMButtonDown(mX, mY))
        return true;

    return false;
}

bool CDrawableObjectControl::OnMButtonUp(int mX, int mY)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnMButtonUp(mX, mY))
        return true;

    return false;
}

bool CDrawableObjectControl::OnMouseWheel(int delta)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnMouseWheel(delta))
        return true;

    return false;
}

bool CDrawableObjectControl::OnKeyDown(sf::Event::KeyEvent key)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnKeyDown(key))
        return true;

    return false;
}

bool CDrawableObjectControl::OnKeyUp(sf::Event::KeyEvent key)
{
    for (vector<pair<string, CDrawableClass*> >::reverse_iterator it = _drawableObjectList.rbegin(); it != _drawableObjectList.rend(); it++)
    if ((*it).second->OnKeyUp(key))
        return true;

    return false;
}
