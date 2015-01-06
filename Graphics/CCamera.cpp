/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCamera.h"
//#include <iostream>

void CCamera::Reset(float x, float y, float w, float h)
{
    _offset.x = w/2; 
    _offset.y = h/2;
    _coordinate.x = x;
    _coordinate.y = y;
    _size.x = w;
    _size.y = h;
    //std::cout << _offset.x << ":" << _offset.y << std::endl;
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
    //_camera.setCenter(_size);
}
    
void CCamera::SetSize(float w, float h)
{
    _size.x = w;
    _size.y = h;
    //_camera.setSize(_size);
}
    
void CCamera::SetZoom(float zoom)
{
    _scale.x = zoom;
    _camera.zoom(zoom);
}

void CCamera::SetRotation(float angle)
{
    _rotation = angle;
    //_camera.setRotation(_rotation);
}

void CCamera::Bind(sf::RenderTarget* window)
{
    if (window)
        window->setView(_camera);
}

bool CCamera::OnLoop()
{
    bool __result = CBaiscProperties::OnLoop();
    
    if (_coordinate != _camera.getCenter())
        _camera.setCenter(_coordinate);

    if (_rotation != _camera.getRotation())
        _camera.setRotation(_rotation);

    if (_size != _camera.getSize())
        _camera.setSize(_size);

    _camera.zoom(_scale.x);
    
    return __result;
}

sf::Vector2f CCamera::GetCenter()
{
    return _camera.getCenter();
}

sf::Vector2f CCamera::GetPosition()
{
    std::cout << _camera.getCenter().x << ":" << _camera.getCenter().y << std::endl;
    return _camera.getCenter() - _offset;
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
        __h = json.get<Number>("WIDTH");
    }

    Reset(json.get<Number>("X"), json.get<Number>("Y"), __w, __h);
    SetZoom(json.get<Number>("ZOOM"));
    SetRotation(json.get<Number>("ROTATION"));

    return true;
}