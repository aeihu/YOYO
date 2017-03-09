/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CSequenceOfSprite.h"

CSequenceOfSprite::CSequenceOfSprite(float x, float y, int left, int top, int width, int height)
{
    SetPosition(x, y);
    _rect.top = left;
    _rect.left = top;
    _rect.width = width;
    _rect.height = height;
}

bool CSequenceOfSprite::LoadImg(string filename)
{
    if (CImgLayer::LoadImg(filename)){
        SetCurrentImageFrame(0);
        return true;
    }
    return false;
}

//================================
//property:
//* PATH,
//* WIDTH,
//* HEIGHT,
//* MAX_FRAMES,
//* FRAME_RATE,
//ORDER,
//SCALE,
//SCALE_X,
//SCALE_Y,
//ROTATION,
//ORIGIN_X,
//ORIGIN_Y,
//X,
//Y,
//RED,
//GREEN,
//BLUE,
//ALPHA,
//================================
bool CSequenceOfSprite::CheckList(const Object& json)
{
    bool result = CImgLayer::CheckList(json);

    if (!json.has<Number>("WIDTH")){
        cout << "can't find value of WIDTH." << endl;
        result = false;
    }

    if (!json.has<Number>("HEIGHT")){
        cout << "can't find value of HEIGHT." << endl;
        result = false;
    }

    if (!json.has<Number>("MAX_FRAMES")){
        cout << "can't find value of MAX_FRAMES." << endl;
        result = false;
    }

    if (!json.has<Number>("FRAME_RATE")){
        cout << "can't find value of FRAME_RATE." << endl;
        result = false;
    }

    return result;
}

bool CSequenceOfSprite::SetProperty(const Object& json, bool isLoad)
{
    SetWidth(json.get<Number>("WIDTH"));
    SetHeight(json.get<Number>("HEIGHT"));
    SetMaxFrames(json.get<Number>("MAX_FRAMES"));
    SetFrameRate(json.get<Number>("FRAME_RATE"));

    return CImgLayer::SetProperty(json, isLoad);
}

void CSequenceOfSprite::SetCurrentImageFrame(int frame)
{
    size_t TilesetWidth = _rect.width == 0 ? 0 : _texture->getSize().x / _rect.width;

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

void CSequenceOfSprite::OnLoop()
{
    CImgLayer::OnLoop();
    if (GetEnable()){
        SetCurrentImageFrame(GetCurrentFrame());
        OnAnimate(CCommon::_Common.GetTicks());
    }
}

void CSequenceOfSprite::TurnOff()
{
    CAnimation::TurnOff();
    SetCurrentImageFrame(GetCurrentFrame());
}
