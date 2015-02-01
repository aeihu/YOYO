/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSequenceOfFrames.h"

CSequenceOfFrames::CSequenceOfFrames(int left, int top, int width, int height)
{
    _rect.top = left;
    _rect.left = top;
    _rect.width = width;
    _rect.height = height;
    _destTexture = NULL;
}

CSequenceOfFrames::~CSequenceOfFrames()
{
    _destTexture = NULL;
}

bool CSequenceOfFrames::LoadImg(const char* filename)
{
    if (filename == NULL)
        return false;

    if (!CSurface::OnLoad(filename, _tile))
        return false;

    SetCurrentImageFrame(GetCurrentFrame());
    return true;
}

void CSequenceOfFrames::SetDestTexture(sf::Texture* pTexture)
{
    _destTexture = pTexture;
    if (pTexture)
        _imageOfTexture = pTexture->copyToImage();
}

void CSequenceOfFrames::SetCurrentImageFrame(int frame)
{
    size_t TilesetWidth  = _tile.getSize().x / _rect.width;

    if (TilesetWidth == 0)
        return;

    _rect.left = (frame % TilesetWidth) * _rect.width;
    _rect.top = (frame / TilesetWidth) * _rect.height;

    if (_destTexture != NULL){
        _image.copy(_imageOfTexture, _offset.x, _offset.y, _rect);
        _destTexture->update(_image, _offset.x, _offset.y);
        _image.copy(_tile, 0,0 ,_rect);
        _destTexture->update(_image, _offset.x, _offset.y);
    }
}

sf::Vector2i CSequenceOfFrames::GetOffset()
{
    return _offset;
}

void CSequenceOfFrames::SetOffset(int x, int y)
{
    _offset.x = x;
    _offset.y = y;
}

void CSequenceOfFrames::SetOffsetX(int x)
{
    _offset.x = x;
}

void CSequenceOfFrames::SetOffsetY(int y)
{
    _offset.y = y;
}

void CSequenceOfFrames::SetSize(int w, int h)
{
    _rect.width = w;
    _rect.height = h;
    _image.create(w,h);
}

int CSequenceOfFrames::GetWidth() const
{
    return _rect.width;
}

int CSequenceOfFrames::GetHeight() const
{
    return _rect.height;
}

void CSequenceOfFrames::TurnOff(int frame)
{
    CAnimation::TurnOff(frame);
    SetCurrentImageFrame(GetCurrentFrame());
}

void CSequenceOfFrames::OnLoop()
{
    if (GetEnable()){
        SetCurrentImageFrame(GetCurrentFrame());
        OnAnimate(CCommon::_Common.GetTicks());
    }
}
