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

    _shadowEnable = true;
}
        
sf::Color CText::GetColor() const
{
    return _textColor;
}
        
const sf::Vector2f& CText::GetGlobalPosition() const
{
    return _sfText.getPosition();
}

void CText::SetColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    _textColor.r = r;
    _textColor.g = g;
    _textColor.b = b;

    _sfText.setColor(_textColor);
}
        
void CText::SetColor(vector<string> args)
{
    if (args.size() > 0){
        SetColor(
            atoi(args[0].c_str()),
            atoi(args[1].c_str()),
            atoi(args[2].c_str()));
    }
}
        

void CText::SetString(string str)
{
    CTextFunction::SetString(_sfText, str);
}
        
void CText::SetString(vector<string> args)
{
    if (args.size() > 0){
        SetString(args[0]);
    }
}
        
void CText::SetCharacterSize(size_t size)
{
    _sfText.setCharacterSize(size);
}

void CText::SetCharacterSize(vector<string> args)
{
    if (args.size() > 0){
        SetCharacterSize(atoi(args[0].c_str()));
    }
}

CText* CText::Create()
{
    CText* __text = new CText();
    __text->SetLayerOrder(105);
    __text->SetClassName("text");

    return __text;
}

void CText::SetFont(string name)
{
    CFont* __fnt = NULL;
    CObject* __object = 
        CResourceControl::_ResourceManager._ObjectControl.GetObject(name);
   
    if (__object != NULL){
        __fnt = static_cast<CFont*>(__object);
         _sfText.setFont(__fnt->GetFont());
    }
}

void CText::SetFont(vector<string> args)
{
    if (args.size() > 0){
        SetFont(args[0]);
    }
}
        
void CText::SetStyle(size_t flag)
{
    _sfText.setStyle(flag);
}
        
void CText::SetStyle(vector<string> args)
{
    if (args.size() > 0){
        size_t __flag = 0;

        for (size_t i=0; i<args.size(); i++){
            if (args[i] == "-sb")
                __flag |= sf::Text::Bold;
            else if (args[i] == "-si")
                __flag |= sf::Text::Italic;
            else if (args[i] == "-su")
                __flag |= sf::Text::Underlined;
            else if (args[i] == "-ss")
                __flag |= sf::Text::StrikeThrough;
            else if (args[i] == "-sr")
                __flag = sf::Text::Regular;
        }
        SetStyle(__flag);
    }
}

void CText::OnLoop()
{
    float __a = _alpha * _argOfCtrlForAlpha;
    _visible = __a > 0 ? true : false;

    if (_sfText.getColor().a != __a)
        _shadowColor.a = _textColor.a = __a;
    
    if (_sfText.getColor().r != _red ||
        _sfText.getColor().g != _green ||
        _sfText.getColor().b != _blue){
        _textColor.r = _red; 
        _textColor.g = _green;
        _textColor.b = _blue;
    }

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
}

void CText::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_visible){
        if (_shadowEnable){
            sf::Vector2f __tmp = _sfText.getOrigin();
            _sfText.setOrigin(__tmp.x - 2.0f, __tmp.y - 2.0f);
            _sfText.setColor(_shadowColor);
            Surf_Dest->draw(_sfText);

            _sfText.setOrigin(__tmp);
        }

        _sfText.setColor(_textColor);
        Surf_Dest->draw(_sfText);
    }
}

//void CText::FlipX()
//{
//
//}
//
//void CText::FlipY()
//{
//
//}

void CText::OnSaveData(Object& json) const
{
    CImageBaseClass::OnSaveData(json);
    json << "shadow_enable" << _shadowEnable;
    json << "shadow_red" << _shadowColor.r;
    json << "shadow_green" << _shadowColor.g;
    json << "shadow_blue" << _shadowColor.b;
}
