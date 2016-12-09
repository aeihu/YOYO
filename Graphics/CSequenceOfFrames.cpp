/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CSequenceOfFrames.h"

CSequenceOfFrames::CSequenceOfFrames(int left, int top, int width, int height)
{
    _rect.top = left;
    _rect.left = top;
    _rect.width = width;
    _rect.height = height;
    _destOriImage = NULL;
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

void CSequenceOfFrames::SetTexture(sf::Image& image)
{
    _tile = image;
    SetCurrentImageFrame(GetCurrentFrame());
}

void CSequenceOfFrames::SetDestTexture(sf::Texture* pTexture, sf::IntRect rect, sf::Image* pImg)
{
    if (pImg != NULL)
    {
        _offset.x = rect.left;
        _offset.y = rect.top;
        _destTexture = pTexture;
        _destOriImage = pImg;
        _rect.width = rect.width;
        _rect.height = rect.height;
        _image.create(rect.width, rect.height);
    }
}

void CSequenceOfFrames::SetDestTexture(sf::Texture* pTexture, sf::Image* pImg)
{
    if (pImg != NULL)
    {
        _destTexture = pTexture;
        _destOriImage = pImg;
    }
}

void CSequenceOfFrames::SetDestTexture(sf::Texture* pTexture, sf::IntRect rect)
{
    _destTexture = pTexture;
    _destOriImage = NULL;
    _offset.x = rect.left;
    _offset.y = rect.top;
    _rect.width = rect.width;
    _rect.height = rect.height;
    _image.create(rect.width, rect.height);
}

void CSequenceOfFrames::SetCurrentImageFrame(int frame)
{
    if (_destTexture != NULL){
        size_t TilesetWidth  = _tile.getSize().x / _rect.width;

        if (TilesetWidth == 0)
            return;

        _rect.left = (frame % TilesetWidth) * _rect.width;
        _rect.top = (frame / TilesetWidth) * _rect.height;

        if ((_tile.getSize().x >= _rect.left + _rect.width)
            &&
            (_tile.getSize().y >= _rect.top + _rect.height)){
            _image.copy(_tile, 0,0 ,_rect);

            if (_destOriImage)
                _destTexture->update(*_destOriImage, _offset.x, _offset.y);

            _destTexture->update(_image, _offset.x, _offset.y);
        }
    }
}

sf::Vector2i CSequenceOfFrames::GetOffset()
{
    return _offset;
}

int CSequenceOfFrames::GetWidth() const
{
    return _rect.width;
}

int CSequenceOfFrames::GetHeight() const
{
    return _rect.height;
}

void CSequenceOfFrames::TurnOff()
{
    CAnimation::TurnOff();
    SetCurrentImageFrame(GetCurrentFrame());
}

void CSequenceOfFrames::OnLoop()
{
    if (GetEnable()){
        SetCurrentImageFrame(GetCurrentFrame());
        OnAnimate(CCommon::_Common.GetTicks());
    }
}
