/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CCamera.h"

CCamera::CCamera()
{
    _window = NULL;
    _zoom = 1.0f;
}

void CCamera::SetCamera(float x, float y, float w, float h)
{
    SetPosition(x, y);
    _orgSize.x = w;
    _orgSize.y = h;
    _camera.reset(sf::FloatRect(x, y, w, h));
}

void CCamera::SetViewport(float x, float y, float w, float h)
{
    _camera.setViewport(sf::FloatRect(x, y, w, h));
}

void CCamera::SetCenter(float x, float y)
{
    SetPosition(x, y);
}
    
//void CCamera::SetSize(float w, float h)
//{
//    _size.x = w;
//    _size.y = h;
//    _orgSize = _size;
//}
    
void CCamera::SetZoom(float zoom)
{
    SetScaleX(zoom);
    _camera.setSize(_orgSize);
    _zoom = zoom;
    _camera.zoom(zoom);
}

void CCamera::Bind(sf::RenderTarget* window)
{
    if (window){
        window->setView(_camera);
        _window = window;
    }
}
     
void CCamera::UnBind()
{
    _window = NULL;
}

void CCamera::OnLoop()
{
    CBaiscProperties::OnLoop();
    bool __isChanged = false;
    
    if (GetPosition() != _camera.getCenter()){
        _camera.setCenter(GetPosition());
        __isChanged = true;
    }

    if (GetRotation() != _camera.getRotation()){
        _camera.setRotation(GetRotation());
        __isChanged = true;
    }

    //if (_size != _camera.getSize()){
    //    _camera.setSize(_size);
    //    __isChanged = true;
    //}

    if (_zoom != GetScale().x){
        SetZoom(GetScale().x);
        __isChanged = true;
    }

    if (__isChanged && _window != NULL)
        _window->setView(_camera);
}

sf::Vector2f CCamera::GetCenter()
{
    return _camera.getCenter();
}

sf::Vector2f CCamera::GetPosition()
{
    std::cout << _camera.getCenter().x << ":" << _camera.getCenter().y << std::endl;
    return _camera.getCenter();
}

void CCamera::OnSaveData(Object& json) const
{
    CBaiscProperties::OnSaveData(json);
    //json << "width" << _size.x;
    //json << "height" << _size.y;
    json << "zoom" << _zoom;
    json << "org_width" << _orgSize.x;
    json << "org_height" << _orgSize.y;
}

void CCamera::OnLoadData(Object json)
{
    CBaiscProperties::OnLoadData(json);
    _orgSize.x = json.get<Number>("org_width");
    _orgSize.y = json.get<Number>("org_height");
    //_size.x = json.get<Number>("width");
    //_size.y = json.get<Number>("height");
    SetZoom(json.get<Number>("zoom"));
}

CCamera* CCamera::Create(const char* filename)
{
    CCamera* __camera = new CCamera();
    if (__camera->LoadConfigFile(filename)){
        __camera->SetClassName("camera");
        __camera->SetPath(filename);
        return __camera;
    }
    
    delete __camera;
    return NULL;
}


//================================
//property:
//* X,
//* Y,
//* ZOOM,
//* ROTATION,
//WIDTH,
//HEIGHT,
//================================

bool CCamera::CheckList(Object json) 
{
    bool result = true;
    if (!json.has<Number>("X")){
        cout << "can't find value of X." << endl;
        result = false;
    }

    if (!json.has<Number>("Y")){
        cout << "can't find value of Y." << endl;
        return false;
    }

    if (!json.has<Number>("ZOOM")){
        cout << "can't find value of ZOOM." << endl;
        return false;
    }

    if (!json.has<Number>("ROTATION")){
        cout << "can't find value of ROTATION." << endl;
        return false;
    }

    return result;
}

bool CCamera::SetProperty(Object json, bool isLoad)
{
    float __w = CCommon::_Common.WWIDTH;
    float __h = CCommon::_Common.WHEIGHT;

    if (json.has<Number>("WIDTH")){
        __w = json.get<Number>("WIDTH");
    }

    if (json.has<Number>("HEIGHT")){
        __h = json.get<Number>("HEIGHT");
    }

    SetCamera(json.get<Number>("X"), json.get<Number>("Y"), __w, __h);
    SetZoom(json.get<Number>("ZOOM"));
    SetRotation(json.get<Number>("ROTATION"));

    return true;
}