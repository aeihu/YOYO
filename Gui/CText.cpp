/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CText.h"

CText::CText()
{
    _textColor.r = CCommon::_Common.CHAR_COLOR_RED;
    _textColor.g = CCommon::_Common.CHAR_COLOR_GREEN;
    _textColor.b = CCommon::_Common.CHAR_COLOR_BLUE;
    _textColor.a = CCommon::_Common.CHAR_COLOR_ALPHA;
    
    _shadowColor.r = CCommon::_Common.CHAR_SHADOW_COLOR_RED;
    _shadowColor.g = CCommon::_Common.CHAR_SHADOW_COLOR_GREEN;
    _shadowColor.b = CCommon::_Common.CHAR_SHADOW_COLOR_BLUE;
    _shadowColor.a = CCommon::_Common.CHAR_SHADOW_COLOR_ALPHA;
}
        
void CText::SetColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    _textColor.r = r;
    _textColor.g = g;
    _textColor.b = b;

    _sfText.setColor(_textColor);
}

void CText::SetString(string str)
{
    _sfText.setString(str);
}
        
void CText::SetCharacterSize(size_t size)
{
    _sfText.setCharacterSize(size);
}

CText* CText::Create()
{
    CText* __text = new CText();
    __text->SetLayerOrder(105);
    __text->SetClassName("text");

    return __text;
}

void CText::SetFont(sf::Font& font)
{
    _sfText.setFont(font);
}
        
void CText::SetStyle(size_t flag)
{
    _sfText.setStyle(flag);
}

bool CText::OnLoop()
{
    bool __result = false;
    _visible = _alpha > 0 ? true : false;

    if (_sfText.getColor().a != _alpha)
        _sfText.setColor(sf::Color(
            _sfText.getColor().r,
            _sfText.getColor().g,
            _sfText.getColor().b,
            _alpha));

    if (_visible){
        if (_coordinate != _sfText.getPosition())
            _sfText.setPosition(_coordinate);
        
        if (_origin != _sfText.getOrigin())
            _sfText.setOrigin(_origin);
        
        if (_scale != _sfText.getScale())
            _sfText.setScale(_scale);

        if (_rotation != _sfText.getRotation())
            _sfText.setRotation(_rotation);
    }

    return __result;
}

void CText::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_visible){
        sf::Vector2f __tmp = _sfText.getOrigin();
        _sfText.setOrigin(__tmp.x - 2.0f, __tmp.y - 2.0f);
        _sfText.setColor(_shadowColor);
        Surf_Dest->draw(_sfText);

        _sfText.setOrigin(__tmp);
        _sfText.setColor(_textColor);
        Surf_Dest->draw(_sfText);
    }
}