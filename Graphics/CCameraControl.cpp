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

void CCameraControl::OnLoop()
{
    map<string, CCamera*>::iterator it;
    for ( it=_cameraList.begin(); it !=_cameraList.end(); it++ )
        (*it).second->OnLoop();
}

bool CCameraControl::UseCamera(string name)
{
    CCamera* __obj = GetCamera(name);
    
    if (__obj == NULL)
        return false;

    map<string, CCamera*>::iterator it;
    for ( it=_cameraList.begin(); it !=_cameraList.end(); it++ ){
        (*it).second->UnBind();
    }
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