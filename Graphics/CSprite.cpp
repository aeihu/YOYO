/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CSprite.h"
#include "CImage.h"

CSprite::CSprite()
{}

CSprite::~CSprite()
{}

void CSprite::SetTexture(const CImage &image, bool resetRect)
{
    _sprite.setTexture(image._texture, resetRect);
}

void CSprite::SetTextureRect(const CIntRect &rectangle)
{
    _sprite.setTextureRect((sf::IntRect)rectangle);
}

void CSprite::SetPosition(float x, float y)
{
    _sprite.setPosition(x, y);
}

void CSprite::SetPosition(CCoordinate2f pos)
{
    _sprite.setPosition(pos.x, pos.y);
}

void CSprite::SetScale(float factorX, float factorY)
{
    _sprite.setScale(factorX, factorY);
}

void CSprite::SetScale(CCoordinate2f factors)
{
    _sprite.setScale(factors.x, factors.y);
}

void CSprite::SetRotation(float angle)
{
    _sprite.setRotation(angle);
}

void CSprite::SetColor(CColor color)
{
    _sprite.setColor(sf::Color(color.r,color.g,color.b,color.a));
}

CCoordinate2f CSprite::GetPosition() const
{
    CCoordinate2f __result;
    __result = _sprite.getPosition();
    return __result;
}

CColor CSprite::GetColor() const
{
    CColor __result;
    __result = _sprite.getColor();
    return __result;
}

CCoordinate2f CSprite::GetScale() const
{
    CCoordinate2f __result;
    __result = _sprite.getScale();
    return __result;
}

float CSprite::GetRotation() const
{
    return _sprite.getRotation();
}

CFloatRect CSprite::GetLocalBounds() const
{
    CFloatRect __result;
    __result = _sprite.getLocalBounds();
    return __result;
}

CFloatRect CSprite::GetGlobalBounds() const
{
    CFloatRect __result;
    __result = _sprite.getGlobalBounds();
    return __result;
}
