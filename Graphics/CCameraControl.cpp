/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CCameraControl.h"

bool CCameraControl::AddCamera(string name, string filename)
{
    if(_cameraList.count(name) > 0)
        return false;
    
    _cameraList[name] = CCamera::Create(filename.c_str());
    if (_cameraList[name] == NULL)
    {
        _cameraList.erase(name);
        cout << "CCameraControl::AddCamera(): failed to create camera"
            << " \"" << name << "\"." << endl;
        return false;
    }
    return true;
}

bool CCameraControl::ResetCamera(string name)
{
    if(_cameraList.count(name) < 1)
        return false;
    
    _cameraList[name]->Reset();
    return true;
}

bool CCameraControl::DelCamera(string name)
{
    if(_cameraList.count(name) > 0){
        _cameraList[name]->OnCleanup();
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
    for (map<string, CCamera*>::iterator it = _cameraList.begin(); it != _cameraList.end(); it++)
        (*it).second->OnLoop();
}
        
void CCameraControl::OnCleanup()
{
    for (map<string, CCamera*>::iterator it = _cameraList.begin(); it != _cameraList.end(); it++){
        (*it).second->ClearActionList();
        delete (*it).second;
    }

    _cameraList.clear();
}

void CCameraControl::ClearActionList()
{
    for (map<string, CCamera*>::iterator it = _cameraList.begin(); it != _cameraList.end(); it++)
        (*it).second->ClearActionList();
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
    _currcentCamera = name;
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
        
void CCameraControl::UseDefaultCamera()
{
    if (_display == NULL)
        return;
    
    _currcentCamera = "";
    _display->setView(_display->getDefaultView());
}
        
void CCameraControl::OnSaveData(Object& json) const
{
    Object __obj;
    Array __array;

    if (!_currcentCamera.empty())
        __obj << "use_camera" << _currcentCamera;
    
    for (map<string, CCamera*>::const_iterator it=_cameraList.begin(); it!=_cameraList.end(); it++){
        Object __cam;
        (*it).second->OnSaveData(__cam);
        __cam << "name" << (*it).first;
        __array << __cam;
    }
    __obj << "camera" << __array;
    json << "camera" << __obj;
}
        
void CCameraControl::OnLoadData(Object json)
{
    Object& __obj = json.get<Object>("camera");
    Array& __array = __obj.get<Array>("camera");
    for (size_t i=0; i<__array.size(); i++){
        Object& __obj = __array.get<Object>(i);
        CCamera* __cam = GetCamera(__obj.get<String>("name"));
        if (__cam != NULL){
            __cam->OnLoadData(__obj);
        }
    }

    if (__obj.has<String>("use_camera"))
        UseCamera(__obj.get<String>("use_camera"));
    else
        UseDefaultCamera();
}
