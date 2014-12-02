/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCamera.h"
#include <iostream>

sf::View CCamera::_camera;
sf::Vector2f CCamera::_offset;

void CCamera::Reset(float x, float y, float w, float h)
{
    _offset.x = w/2; 
    _offset.y = h/2;
    std::cout << _offset.x << ":" << _offset.y << std::endl;
    _camera.reset(sf::FloatRect(x, y, w, h));
}

void CCamera::SetViewport(float x, float y, float w, float h)
{
    _camera.setViewport(sf::FloatRect(x, y, w, h));
}

void CCamera::SetCenter(float x, float y)
{
    //_offset.x -= x, _offset.y -= y;
    std::cout << _offset.x << ":" << _offset.y << std::endl;
    _camera.setCenter(x, y);
}
    
void CCamera::SetSize(float w, float h)
{
    _camera.setSize(w, h);
}
    
void CCamera::SetZoom(float zoom)
{
    _camera.zoom(zoom);
}

void CCamera::SetRotation(float angle)
{
    _camera.setRotation(angle);
}

void CCamera::Bind(sf::RenderWindow* window)
{
    if (window)
        window->setView(_camera);
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
