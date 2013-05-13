/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSequenceOfFrames.h"

CSequenceOfFrames::CSequenceOfFrames(float x, float y, int left, int top, int width, int height):CImageBaseClass(x,y)
{
    _rect.top = left;
    _rect.left = top;
    _rect.width = width;
    _rect.height = height;
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
    unsigned int TilesetWidth  = _image.GetWidth() / _rect.width;
    //int TilesetHeight  = _image.GetHeight() / _rect.GetHeight();
    unsigned int Width = _rect.width;
    unsigned int Height = _rect.height;

    _rect.left = (frame % TilesetWidth) * _rect.width;
    //_rect.Right = _rect.Left+Width;
    _rect.top = (frame / TilesetWidth) * _rect.height;
    //_rect.Bottom = _rect.Top+Height;

    _sprite.SetTextureRect(_rect);
}

CCoordinate2f CSequenceOfFrames::GetPosition()
{
    return _sprite.GetPosition();
}

void CSequenceOfFrames::SetWidth(int w)
{
    _rect.width = w;
}

void CSequenceOfFrames::SetHeight(int h)
{
    _rect.height = h;
}

int CSequenceOfFrames::GetWidth()
{
    return _rect.width;
}

int CSequenceOfFrames::GetHeight()
{
    return _rect.height;
}

void CSequenceOfFrames::SetPosition(float x, float y)
{
    _sprite.SetPosition(x,y);
}
