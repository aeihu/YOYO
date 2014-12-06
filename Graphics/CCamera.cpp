/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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

void CCamera::Bind(sf::RenderWindow* window)
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

CCamera* CCamera::Create()
{
    CCamera* __Camera = new CCamera();
    __Camera->SetClassName("camera");
    return __Camera;
}
