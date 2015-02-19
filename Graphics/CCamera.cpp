/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCamera.h"

CCamera::CCamera()
{
    _window = NULL;
    _zoom = 1.0f;
}

void CCamera::Reset(float x, float y, float w, float h)
{
    _coordinate.x = x;
    _coordinate.y = y;
    _size.x = w;
    _size.y = h;
    _orgSize = _size;
    _camera.reset(sf::FloatRect(x, y, w, h));
}

void CCamera::SetViewport(float x, float y, float w, float h)
{
    _camera.setViewport(sf::FloatRect(x, y, w, h));
}

void CCamera::SetCenter(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}
    
void CCamera::SetSize(float w, float h)
{
    _size.x = w;
    _size.y = h;
    _orgSize = _size;
}
    
void CCamera::SetZoom(float zoom)
{
    _camera.setSize(_orgSize);
    _zoom = _scale.x = zoom;
    _camera.zoom(zoom);
    _size = _camera.getSize();
}

void CCamera::SetRotation(float angle)
{
    _rotation = angle;
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
    bool __isChanged = false;
    
    if (_coordinate != _camera.getCenter()){
        _camera.setCenter(_coordinate.x, _coordinate.y);
        __isChanged = true;
    }

    if (_rotation != _camera.getRotation()){
        _camera.setRotation(_rotation);
        __isChanged = true;
    }

    if (_size != _camera.getSize()){
        _camera.setSize(_size);
        __isChanged = true;
    }

    if (_zoom != _scale.x){
        SetZoom(_scale.x);
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
    json << "width" << _size.x;
    json << "height" << _size.y;
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

bool CCamera::SetProperty(Object json)
{
    float __w = CCommon::_Common.WWIDTH;
    float __h = CCommon::_Common.WHEIGHT;

    if (json.has<Number>("WIDTH")){
        __w = json.get<Number>("WIDTH");
    }

    if (json.has<Number>("HEIGHT")){
        __h = json.get<Number>("HEIGHT");
    }

    Reset(json.get<Number>("X"), json.get<Number>("Y"), __w, __h);
    SetZoom(json.get<Number>("ZOOM"));
    SetRotation(json.get<Number>("ROTATION"));

    return true;
}