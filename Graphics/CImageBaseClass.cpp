/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImageBaseClass.h"

CImageBaseClass::CImageBaseClass(float x, float y)
{
    _sprite.setPosition(x,y);
    _Coordinate.x = x;
    _Coordinate.y = y;
    _Alpha = 0;
    _visible = false;
    _image.setSmooth(true);
}

CImageBaseClass::~CImageBaseClass()
{}

CObject* CImageBaseClass::Create(const char* filename)
{
    CImageBaseClass* __img = new CImageBaseClass();
    if (__img->LoadImg(filename))
        return __img;
    
    delete __img;
    return NULL;
}

bool CImageBaseClass::GetVisible() const
{
    return _visible;
}

bool CImageBaseClass::IsStandby()
{
    return _visible && Count()==0;
}

bool CImageBaseClass::LoadImg(const char* fileName)
{
    if (fileName == NULL)
        return false;

    if (!CSurface::OnLoad(fileName, _image))
        return false;

    _image.setSmooth(false);
    _sprite.setTexture(_image);
    return true;
}

void CImageBaseClass::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (_visible)
        Surf_Dest->draw(_sprite);
}

bool CImageBaseClass::OnLoop()
{
    bool __result = CAdderControl::OnLoop()>0 ? true : false;
    _visible = _Alpha > 0 ? true : false;

    if (_Alpha > 255)
        _Alpha = 255;
    else if (_Alpha < 0)
        _Alpha = 0;

    if (_sprite.getColor().a != _Alpha)
        _sprite.setColor(sf::Color(255,255,255,_Alpha));

    if (_Coordinate != _sprite.getPosition())
        _sprite.setPosition(_Coordinate);

    if (_sprite.getScale().x > 1.0f || _sprite.getScale().y > 1.0f)
        _image.setSmooth(true);
    else
        _image.setSmooth(false);

    return __result;
}
