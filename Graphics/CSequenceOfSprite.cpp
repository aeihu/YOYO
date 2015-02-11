/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSequenceOfSprite.h"

CSequenceOfSprite::CSequenceOfSprite(float x, float y, int left, int top, int width, int height):CImgLayer(x,y)
{
    _rect.top = left;
    _rect.left = top;
    _rect.width = width;
    _rect.height = height;
}

bool CSequenceOfSprite::LoadImg(const char* filename)
{
    if (CImgLayer::LoadImg(filename)){
        SetCurrentImageFrame(0);
        return true;
    }
    return false;
}

void CSequenceOfSprite::SetCurrentImageFrame(int frame)
{
    size_t TilesetWidth  = _image.getSize().x / _rect.width;

    if (TilesetWidth == 0)
        return;
    //int TilesetHeight  = _image.GetHeight() / _rect.GetHeight();
    //size_t Width = _rect.width;
    //size_t Height = _rect.height;

    _rect.left = (frame % TilesetWidth) * _rect.width;
    //_rect.Right = _rect.Left+Width;
    _rect.top = (frame / TilesetWidth) * _rect.height;
    //_rect.Bottom = _rect.Top+Height;

    _sprite.setTextureRect(_rect);
}

sf::Vector2f CSequenceOfSprite::GetPosition()
{
    return _sprite.getPosition();
}

void CSequenceOfSprite::SetWidth(int w)
{
    _rect.width = w;
}

void CSequenceOfSprite::SetHeight(int h)
{
    _rect.height = h;
}

int CSequenceOfSprite::GetWidth()
{
    return _rect.width;
}

int CSequenceOfSprite::GetHeight()
{
    return _rect.height;
}

bool CSequenceOfSprite::OnLoop()
{
    bool __result = CImgLayer::OnLoop();
    if (GetEnable()){
        SetCurrentImageFrame(GetCurrentFrame());
        OnAnimate(CCommon::_Common.GetTicks());
    }

    return __result;
}
void CSequenceOfSprite::TurnOff(int frame)
{
    CAnimation::TurnOff(frame);
    SetCurrentImageFrame(GetCurrentFrame());
}
