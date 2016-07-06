/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CText.h"

CText::CText()
{
    _currcentFont = "";
    _textColor.r = 255;
    _textColor.g = 255;
    _textColor.b = 255;
    _textColor.a = 255;
    
    _shadowColor.r = 10;
    _shadowColor.g = 10;
    _shadowColor.b = 10;
    _shadowColor.a = 200;

    _shadowEnable = true;
    _shadowPercent = 1.0f;
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
        
void CText::SetShadowPercent(vector<string> args)
{
    if (args.size() > 0){
        SetShadowPercent(atof(args[0].c_str()));
    }
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
        CResourceControl::_ResourceManager._ObjectControl.GetObject(name);
   
    if (__object != NULL){
        __fnt = static_cast<CFont*>(__object);
        _sfText.setFont(__fnt->GetFont());
        _currcentFont = name;
    }
}

void CText::SetFont(vector<string> args)
{
    if (args.size() > 0){
        SetFont(args[0]);
    }
}

void CText::SetShadowEnable(bool b)
{
    _shadowEnable = b;
}

void CText::SetShadowEnable(vector<string> args)
{
    if (args.size() > 0)
        SetShadowEnable(true);
    else
        SetShadowEnable(false);
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
	CBaiscProperties::_actionList.OnLoop();
    _isShowed = _alpha > 0 ? true : false;

    if (_sfText.getColor().a != _alpha){
        _textColor.a = _alpha;
        _shadowColor.a = _alpha * _shadowPercent;
    }
    
    if (_sfText.getColor().r != _red ||
        _sfText.getColor().g != _green ||
        _sfText.getColor().b != _blue){
        _textColor.r = _red; 
        _textColor.g = _green;
        _textColor.b = _blue;
    }

    if (_isShowed){
        if (_coordinate != _sfText.getPosition())
            _sfText.setPosition(_coordinate);
        
        if ((_origin.x * _sfText.getLocalBounds().width != _sfText.getOrigin().x) ||
            (_origin.y * _sfText.getLocalBounds().height != _sfText.getOrigin().y)){
            _sfText.setOrigin(_origin.x * _sfText.getLocalBounds().width,
                _origin.y * _sfText.getLocalBounds().height);
        }
        
        if (_scale != _sfText.getScale())
            _sfText.setScale(_scale);

        if (_rotation != _sfText.getRotation())
            _sfText.setRotation(_rotation);
    }
}

void CText::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_isShowed){
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
