/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CText.h"
#include "../Common/CResourceControl.h"

CText::CText()
{
    _currcentFont = "";
    SetRed(255);
    SetGreen(255);
    SetBlue(255);
    SetAlpha(255);
    
    _shadowColor.r = 10;
    _shadowColor.g = 10;
    _shadowColor.b = 10;
    _shadowColor.a = 200;

    _shadowEnable = true;
    _shadowPercent = 1.0f;
}

void CText::SetShadowColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    _shadowColor.r = r;
    _shadowColor.g = g;
    _shadowColor.b = b;
}

const sf::Color& CText::GetShadowColor() const
{
    return _shadowColor;
}

void CText::SetString(string str)
{
    CTextFunction::SetString(_sfText, str);
}

string CText::GetString()
{
    return _sfText.getString();
}
        
void CText::SetCharacterSize(size_t size)
{
    _sfText.setCharacterSize(size);
}

float CText::GetShadowPercent() const
{
    return _shadowPercent;
}

void CText::SetShadowPercent(float percent)
{
    if (percent < 0.0f){
        _shadowPercent = 0.0f;
        return;
    }

    if (percent > 1.0f){
        _shadowPercent = 1.0f;
        return;
    }

    _shadowPercent = percent;
}

CText* CText::Create()
{
    CText* __text = new CText();
    __text->SetLayerOrder(105);
    __text->SetClassName("Text");

    return __text;
}

void CText::SetFont(string name)
{
    CFont* __fnt = NULL;
    CObject* __object = 
        CResourceControl::_ResourceManager._ObjectControl.GetObject("Font:" + name);
   
    if (__object != NULL){
        __fnt = static_cast<CFont*>(__object);
        _sfText.setFont(__fnt->GetFont());
        _currcentFont = name;
    }
}

void CText::SetShadowEnable(bool b)
{
    _shadowEnable = b;
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
    CBaiscProperties::OnLoop();

    if (_sfText.getColor().r != GetRed() ||
        _sfText.getColor().g != GetGreen() ||
        _sfText.getColor().b != GetBlue() ||
        _sfText.getColor().a != GetAlpha()){
        _sfText.setColor(sf::Color(GetRed(), GetGreen(), GetBlue(), GetAlpha()));
        _shadowColor.a = GetAlpha() * _shadowPercent;
    }

    Loop(&_sfText);
}

void CText::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (IsShowed()){
        if (_shadowEnable){
            sf::Color __color(_sfText.getColor());
            sf::Vector2f __tmp = _sfText.getOrigin();

            _sfText.setOrigin(__tmp.x - 2.0f, __tmp.y - 2.0f);
            _sfText.setColor(_shadowColor);

            if (_baseNode)
                Surf_Dest->draw(_sfText, _baseNode->GetTransform());
            else
                Surf_Dest->draw(_sfText);

            _sfText.setOrigin(__tmp);
            _sfText.setColor(__color);
        }
        
        if (_baseNode)
            Surf_Dest->draw(_sfText, _baseNode->GetTransform());
        else
            Surf_Dest->draw(_sfText);

        list<CImageBaseClass*>::iterator it;
        for (it = _childrenList.begin(); it != _childrenList.end(); it++)
            (*it)->OnRender(Surf_Dest);
    }
}

sf::Transform CText::GetTransform()
{
    if (_baseNode)
        return _sfText.getTransform() * _baseNode->GetTransform();

    return _sfText.getTransform();
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
    json << "font" << _currcentFont;
    json << "shadow_enable" << _shadowEnable;
    json << "shadow_red" << _shadowColor.r;
    json << "shadow_green" << _shadowColor.g;
    json << "shadow_blue" << _shadowColor.b;
    json << "shadow_alpha" << _shadowPercent;
    
    if (_sfText.getString() != "")
        json << "text" << _sfText.getString();
}
        
void CText::OnLoadData(Object json)
{
    CImageBaseClass::OnLoadData(json);
    SetFont(json.get<String>("font"));
    _shadowEnable = json.get<Boolean>("shadow_enable");
    _shadowColor.r = json.get<Number>("shadow_red");
    _shadowColor.g = json.get<Number>("shadow_green");
    _shadowColor.b = json.get<Number>("shadow_green");
    _shadowPercent = json.get<Number>("shadow_alpha");
    SetString(json.has<String>("text") ? json.get<String>("text") : "");
}
