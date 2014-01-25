/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CText.h"
#include "../Text/CFont.h"

CText::CText()
{}

CText::~CText()
{}

void CText::SetOrigin (CCoordinate2f origin)
{
    _text.setOrigin(origin.x, origin.y);
}

void CText::SetOrigin (float x, float y)
{
    _text.setOrigin(x,y);
}

void CText::SetColor (const CColor color)
{
    _text.setColor(sf::Color(color.r,color.g,color.b,color.a));
}

void CText::SetFont(CFont& font)
{
    _text.setFont(font._font);
}

void CText::SetString(std::string str)
{
    sf::Uint32* __uft32String = new sf::Uint32[str.length()];
    sf::Utf8::toUtf32(str.begin(), str.end(), __uft32String);
    _text.setString(__uft32String);
    delete[] __uft32String;
}

void CText::SetPosition(float x, float y)
{
    _text.setPosition(x,y);
}

void CText::SetPosition(CCoordinate2f pos)
{
    _text.setPosition(pos.x, pos.y);
}

CCoordinate2f CText::FindCharacterPos(std::size_t index) const
{
    CCoordinate2f __result;
    __result = _text.findCharacterPos(index);
    return __result;
}

unsigned int CText::GetCharacterSize() const
{
    return _text.getCharacterSize();
}

CFloatRect CText::GetLocalBounds() const
{
    CFloatRect __result;
    __result = _text.getLocalBounds();
    return __result;
}

CFloatRect CText::GetGlobalBounds() const
{
    CFloatRect __result;
    __result = _text.getGlobalBounds();
    return __result;
}