/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
            cout << "CResourceControl::AddDrawableObject" << objTypeName 
                <<"(): " << objTypeName << " \""<< name << "\" has existed." <<endl;
            delete __obj;
            return false;
        }

        _drawableObjectList.push_back(make_pair(objTypeName+":"+name, __obj));
        _isNeedSort = true;
        return true;
    }
    else
        cout << "CResourceControl::AddDrawableObject" << objTypeName 
            << "(): failed to create " << objTypeName << "." <<endl;

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

void CDrawableObjectControl::SetDrawableObjectLayerOrder(string name, char layer)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name){
            _drawableObjectList[i].second->SetLayerOrder(layer);
            _isNeedSort = true;
            return;
        }
    }
}

bool CDrawableObjectControl::SetImageVisibility(std::string name, int alpha, size_t elapsed, bool pause)
{
   // if (incr == 0)
   //     incr = static_cast<float>(CCommon::_Common.INCREMENT);

    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));
    if (__obj != NULL){
		__obj->AddAction(&__obj->GetAlpha(), elapsed, alpha, pause);
        //__obj->Insert(0,
        //    alpha, pause,
        //    &__obj->GetAlpha(),
        //    incr);

        return true;
    }

    return false;
}

//bool CResourceControl::SetImageVisibility(string name, int alpha, size_t elapsed, bool pause)
//{
//    float __i = elapsed / _interval == 0 ? 1 : elapsed / _interval;
//    return SetImageVisibility(name, alpha, __i, pause);
//}

bool CDrawableObjectControl::SetLayerOrder(string name, char order)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));
    if (__obj != NULL){
        __obj->SetLayerOrder(order);
        return true;
    }
    return false;
}

bool CDrawableObjectControl::MoveX(string name, float x, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return false;
    
    __obj->AddActionOfMoveX(elapsed, x, pause);
    return true;
}
        
bool CDrawableObjectControl::MoveY(string name, float y, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return false;
    
    __obj->AddActionOfMoveY(elapsed, y, pause);
    return true;
}

bool CDrawableObjectControl::Move(string name, float x, float y, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return false;
    
    __obj->AddActionOfMove(elapsed, x ,y, pause);
    return true;
}
        
char CDrawableObjectControl::Show(string name, float x, float y, char type, size_t elapsed, bool pause, int alpha)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return -1;

    if (__obj->GetVisible())
        return -2;

    float __x = x;
    float __y = y;

    //switch (type)
    //{
    //    case 'u':
    //        __y += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //    case 'r':
    //        __x -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //    case 'd':
    //        __y -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //    case 'l':
    //        __x += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //}

    __obj->GetPosition().x = __x;
    __obj->GetPosition().y = __y;
    if (Move(name, x, y, elapsed, pause)){
        SetImageVisibility(name, alpha, elapsed, pause);
        return 0;
    }

    return -1;
}
        
char CDrawableObjectControl::Hide(string name, char type, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return -1;

    if (!__obj->GetVisible())
        return -2;

    float __x = __obj->GetPosition().x;
    float __y = __obj->GetPosition().y;
    //float __i = elapsed == 0 ? 1 : elapsed / _interval;

    //switch (type)
    //{
    //    case 'u':
    //        __y -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //    case 'r':
    //        __x += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //    case 'd':
    //        __y += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //    case 'l':
    //        __x -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    //    break;
    //}

    if (Move(name, __x, __y, elapsed, pause)){
        SetImageVisibility(name, 0, __obj->GetAlpha(), pause);
        return 0;
    }

    return -1;
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

void CDrawableObjectControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++)
        (*it).second->OnRender(Surf_Dest);
}

void CDrawableObjectControl::OnCleanup()
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++){
            delete (*it).second;
    }

    _drawableObjectList.clear();
}
