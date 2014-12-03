/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CResourceControl.h"
#include <algorithm>

CResourceControl  CResourceControl::_ResourceManager;

//bool sort_cmp(pair<string,CImageBaseClass*> obj1, pair<string,CImageBaseClass*> obj2)
//{
//    return obj1.second->GetLayerOrder() < obj2.second->GetLayerOrder();
//}

bool CResourceControl::AddVariable(string name, string val)
{
    if(_userVariableList.count("$"+name) > 0)
        return false;

    _userVariableList["$"+name] = val;
    return true;
}

bool CResourceControl::SetVariable(string name, string val)
{
    if(_userVariableList.count("$"+name) > 0){
        _userVariableList["$"+name] = val;
        return true;
    }

    return false;
}

string CResourceControl::GetVariable(string name)
{
    if(_userVariableList.count(name) > 0){
        return _userVariableList[name];
    }

    return "";
}

bool CResourceControl::DelVariable(string name)
{
    if(_userVariableList.count("$"+name) > 0){
        _userVariableList.erase("$"+name);
        return true;
    }

    return false;
}

bool CResourceControl::AddDrawableObject(string name, CImageBaseClass* obj)
{
    if (obj == NULL)
        return false;

    if (IsExists(name)){
        delete obj;
        return false;
    }

    _drawableObjectList.push_back(make_pair(name, obj));
    _isNeedSort = true;
    return true;
}

bool CResourceControl::DelDrawableObject(string name)
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

CImageBaseClass* CResourceControl::GetDrawableObject(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name)
            return _drawableObjectList[i].second;
    }

    return NULL;
}

void CResourceControl::SetDrawableObjectLayerOrder(string name, char layer)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name){
            _drawableObjectList[i].second->SetLayerOrder(layer);
            _isNeedSort = true;
            return;
        }
    }
}

bool CResourceControl::SetImageVisibility(std::string name, int alpha, size_t elapsed, bool pause)
{
   // if (incr == 0)
   //     incr = static_cast<float>(CCommon::_Common.INCREMENT);

    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));
    if (__obj != NULL){
		__obj->AddAction(&__obj->GetAlpha(), elapsed, alpha);
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

bool CResourceControl::SetLayerOrder(string name, char order)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));
    if (__obj != NULL){
        __obj->SetLayerOrder(order);
        return true;
    }
    return false;
}

bool CResourceControl::MoveX(string name, float x, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return false;
    
    __obj->AddActionOfMoveX(elapsed, x);
    return true;
}
        
bool CResourceControl::MoveY(string name, float y, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return false;
    
    __obj->AddActionOfMoveY(elapsed, y);
    return true;
}

bool CResourceControl::Move(string name, float x, float y, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return false;
    
    __obj->AddActionOfMove(elapsed, x ,y);
    return true;
}
        
char CResourceControl::Show(string name, float x, float y, char type, size_t elapsed, bool pause, int alpha)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return -1;

    if (__obj->GetVisible())
        return -2;

    float __i = elapsed == 0 ? 1 : elapsed / _interval;
    float __x = x;
    float __y = y;

    switch (type)
    {
        case 'u':
            __y += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'r':
            __x -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'd':
            __y -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'l':
            __x += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
    }

    __obj->GetPosition().x = __x;
    __obj->GetPosition().y = __y;
    if (Move(name, x, y, elapsed, pause)){
        SetImageVisibility(name, alpha, elapsed, pause);
        return 0;
    }

    return -1;
}
        
char CResourceControl::Hide(string name, char type, size_t elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return -1;

    if (!__obj->GetVisible())
        return -2;

    float __x = __obj->GetPosition().x;
    float __y = __obj->GetPosition().y;
    float __i = elapsed == 0 ? 1 : elapsed / _interval;

    switch (type)
    {
        case 'u':
            __y -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'r':
            __x += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'd':
            __y += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'l':
            __x -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
    }

    if (Move(name, __x, __y, elapsed, pause)){
        SetImageVisibility(name, 0, __obj->GetAlpha() / __i, pause);
        return 0;
    }

    return -1;
}

bool CResourceControl::OnLButtonUp(int mX, int mY)
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin() ; it != _drawableObjectList.end();it++)
        if ((*it).second->OnLButtonUp(mX, mY))
            return true;

    return false;
}

bool CResourceControl::OnLButtonDown(int mX, int mY)
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin() ; it != _drawableObjectList.end();it++)
        if ((*it).second->OnLButtonDown(mX, mY))
            return true;

    return false;
}

bool CResourceControl::OnMouseMove(int mX, int mY)
{
    //for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin() ; it != _drawableObjectList.end();it++)
    //    if ((*it).second->OnLButtonDown(mX, mY))
    //        return true;

    return false;
}

void CResourceControl::OnLoop(bool &pause)
{
    if (_isNeedSort){
        std::sort(_drawableObjectList.begin(), _drawableObjectList.end(), _sort);
        _isNeedSort = false;
    }

    vector<pair<string, CImageBaseClass*> >::iterator it;
    for ( it=_drawableObjectList.begin(); it !=_drawableObjectList.end(); it++ )
    {
        if((*it).second->OnLoop()) 
            pause=true;
    }
}

void CResourceControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    //unsigned long l = CCommon::_Common.GetTicks();
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++)
        (*it).second->OnRender(Surf_Dest);

    //cout << "time: " << CCommon::_Common.GetTicks()-l <<endl;
}

void CResourceControl::OnCleanup()
{
    for (vector<pair<string, CImageBaseClass*> >::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++){
            delete (*it).second;
    }

    _drawableObjectList.clear();
}

bool CResourceControl::IsExists(string name)
{
    for (size_t i=0; i<_drawableObjectList.size(); i++){
        if (_drawableObjectList[i].first == name)
            return true;
    }

    return _objectList.count(name) > 0;
}

void CResourceControl::OnSaveData()
{
    ofstream __savefile("./userdata/1.txt");
    Object __json;
    __json.reset();

    if(!__savefile){
        cout << "error" << endl;
        return;
    }

    for (size_t i=0; i<_drawableObjectList.size(); i++){
        cout << "_(:3J Z)_" <<endl;
        __savefile << "name=" << _drawableObjectList[i].first <<endl;
        _drawableObjectList[i].second->OnSaveData(__json);
        cout << "(:3[____]" <<endl;
    }

    __savefile.close();
}

void CResourceControl::OnLoadData()
{

}
