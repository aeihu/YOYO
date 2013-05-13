/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImageBaseClass.h"

CImageBaseClass::CImageBaseClass(float x, float y)
{
    _sprite.SetPosition(x,y);
    _Coordinate.x = x;
    _Coordinate.y = y;
    _Alpha = 0;
    _visible = false;
}

CImageBaseClass::~CImageBaseClass()
{}

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

    _image.SetSmooth(false);
    _sprite.SetTexture(_image);
    return true;
}

void CImageBaseClass::OnRender(CWindow* Surf_Dest)
{
    if (!_visible) return;
    Surf_Dest->Draw(_sprite);
    Subclass_Render(Surf_Dest);
}

bool CImageBaseClass::OnLoop()
{
    bool __result = CAdderControl::OnLoop()>0?true:false;
    _visible = _Alpha > 0 ? true : false;

    if (_Alpha > 255)
        _Alpha = 255;
    else if (_Alpha < 0)
        _Alpha = 0;

    if (_sprite.GetColor().a != _Alpha)
        _sprite.SetColor(CColor(255,255,255,_Alpha));

    if (_Coordinate != _sprite.GetPosition())
        _sprite.SetPosition(_Coordinate);

    if (_sprite.GetScale().x > 1.0f || _sprite.GetScale().y > 1.0f)
        _image.SetSmooth(true);
    else
        _image.SetSmooth(false);

    __result = Subclass_Loop() ? true : __result;
    return __result;
}
