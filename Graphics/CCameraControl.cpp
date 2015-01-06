/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCameraControl.h"

bool CCameraControl::AddCamera(string name, string filename)
{
    if(_cameraList.count(name) > 0)
        return false;
    
    _cameraList[name] = CCamera::Create(filename.c_str());
    return true;
}

bool CCameraControl::DelCamera(string name)
{
    if(_cameraList.count(name) > 0){
        delete _cameraList[name];
        _cameraList.erase(name);
        return true;
    }

    return false;
}

CCamera* CCameraControl::GetCamera(string name)
{
    if(_cameraList.count(name) > 0){
        return _cameraList[name];
    }
    return NULL;
}

void CCameraControl::OnLoop(bool &pause)
{
    map<string, CCamera*>::iterator it;
    for ( it=_cameraList.begin(); it !=_cameraList.end(); it++ ){
        if((*it).second->OnLoop()) 
            pause=true;
    }
}

//
//bool CCameraControl::MoveX(string name, float x, size_t elapsed, bool pause, bool reset)
//{
//    CCamera* __obj = GetCamera(name);
//
//    if (__obj == NULL)
//        return false;
//    
//    __obj->AddAction(__obj->CreateActionOfMoveX(elapsed, x, pause));
//    return true;
//}
//        
//bool CCameraControl::MoveY(string name, float y, size_t elapsed, bool pause, bool reset)
//{
//    CCamera* __obj = GetCamera(name);
//
//    if (__obj == NULL)
//        return false;
//    
//    __obj->AddAction(__obj->CreateActionOfMoveY(elapsed, y, pause));
//    return true;
//}
//
//bool CCameraControl::Move(string name, float x, float y, size_t elapsed, bool pause, bool reset)
//{
//    CCamera* __obj = GetCamera(name);
//
//    if (__obj == NULL)
//        return false;
//    
//    __obj->AddAction(__obj->CreateActionOfMove(elapsed, x, y, pause));
//    return true;
//}
//
//bool CCameraControl::Zoom(string name, float zoom, size_t elapsed, bool pause, bool reset)
//{
//    CCamera* __obj = GetCamera(name);
//
//    if (__obj == NULL)
//        return false;
//    
//    __obj->AddAction(__obj->CreateActionOfScaleX(elapsed, zoom, pause));
//    return true;
//}
//
//bool CCameraControl::Rotation(string name, float rotation, size_t elapsed, bool pause, bool reset)
//{
//    CCamera* __obj = GetCamera(name);
//
//    if (__obj == NULL)
//        return false;
//    
//    __obj->AddActionOfRotation(elapsed, rotation, pause, reset);
//    return true;
//}

bool CCameraControl::UseCamera(string name)
{
    CCamera* __obj = GetCamera(name);
    
    if (__obj == NULL)
        return false;

    __obj->Bind(_display);
    return true;
}

bool CCameraControl::OnInit(sf::RenderTarget* display)
{
    if (display != NULL){
        _display = display;
        return true;
    }
    
    return false;
}
        
bool CCameraControl::UseDefaultCamera()
{
    if (_display == NULL)
        return false;

    _display->setView(_display->getDefaultView());
    return true;
}