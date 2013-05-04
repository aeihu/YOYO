/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSequenceOfFrames.h"

CSequenceOfFrames::CSequenceOfFrames(float x, float y, int left, int top, int right, int bottom):CImageBaseClass(x,y)
{
    _rect.Top = left;
    _rect.Left = top;
    _rect.Right = right;
    _rect.Bottom = bottom;
}

bool CSequenceOfFrames::LoadImg(const char* filename)
{
    if (CImageBaseClass::LoadImg(filename)){
        SetCurrentImageFrame(0);
        return true;
    }
    return false;
}

void CSequenceOfFrames::SetCurrentImageFrame(int frame)
{
    int TilesetWidth  = _image.GetWidth() / _rect.GetWidth();
    //int TilesetHeight  = _image.GetHeight() / _rect.GetHeight();
    int Width = _rect.GetWidth();
    int Height = _rect.GetHeight();

    _rect.Left = (frame % TilesetWidth) * _rect.GetWidth();
    _rect.Right = _rect.Left+Width;
    _rect.Top = (frame / TilesetWidth) * _rect.GetHeight();
    _rect.Bottom = _rect.Top+Height;

    _sprite.SetSubRect(_rect);
}

sf::Vector2f CSequenceOfFrames::GetPosition()
{
    return _sprite.GetPosition();
}

void CSequenceOfFrames::SetWidth(int w)
{
    _rect.Right = _rect.Left + w;
}

void CSequenceOfFrames::SetHeight(int h)
{
    _rect.Bottom = _rect.Top + h;
}

int CSequenceOfFrames::GetWidth()
{
    return _rect.GetWidth();
}

int CSequenceOfFrames::GetHeight()
{
    return _rect.GetHeight();
}

void CSequenceOfFrames::SetPosition(float x, float y)
{
    _sprite.SetPosition(x,y);
}
