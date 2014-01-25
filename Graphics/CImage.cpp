/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImage.h"

CImage::CImage()
{}

CImage::~CImage()
{}

void CImage::Create(unsigned int width, unsigned int height)
{
    _texture.create(width, height);
}

bool CImage::LoadFromFile(const std::string &filename, const sf::IntRect &area)
{
    return _texture.loadFromFile(filename, area);
}

bool CImage::LoadFromMemory (const void *data, std::size_t size, const sf::IntRect &area)
{
    return _texture.loadFromMemory(data, size, area);
}

bool CImage::LoadFromImage (const sf::Image &image, const sf::IntRect &area)
{
    return _texture.loadFromImage(image, area);
}

void CImage::SetSmooth (bool smooth)
{
    _texture.setSmooth (smooth);
}

bool CImage::IsSmooth () const
{
    return _texture.isSmooth();
}

unsigned int CImage::GetWidth()
{
    return _texture.getSize().x;
}

unsigned int CImage::GetHeight()
{
    return _texture.getSize().y;
}