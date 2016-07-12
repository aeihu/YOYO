/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CTextProcessing.h"
#include <string>

using namespace std;

CTextProcessing::CTextProcessing()
{
    _pAlpha = NULL;
    _coordinate.x = _coordinate.y = 0.0f;
    _status = CONFIRMED;
    _isSkip = false;
    _rowWidth =
    _index=
    _oldTime =
    _length = 0;
    _textOfShown =
    _text = "";
    _textColor.r = 255;
    _textColor.g = 255;
    _textColor.b = 255;
    _textColor.a = 255;
    
    _shadowColor.r = 10;
    _shadowColor.g = 10;
    _shadowColor.b = 10;
    _shadowColor.a = 200;

    _shadowPercent = 1.0f;
}

bool CTextProcessing::isWordOrNumber(char c)
{
    // There's a problem
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 43 && c <= 58);
}


void CTextProcessing::SetCharacterSize(size_t size)
{
    _sfText.setCharacterSize(size);
}

void CTextProcessing::SetPointAlpha(float* alpha)
{
    if (alpha)
        _pAlpha = alpha;
}

void CTextProcessing::SetRowWidth(size_t width)
{
    _rowWidth = width;
}

void CTextProcessing::SetFont(sf::Font& font)
{
    _sfText.setFont(font);
}
        
void CTextProcessing::SetTextColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    _textColor.r = r;
    _textColor.g = g;
    _textColor.b = b;
}
        
void CTextProcessing::SetShadowColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    _shadowColor.r = r;
    _shadowColor.g = g;
    _shadowColor.b = b;
}
        
void CTextProcessing::SetShadowPercent(float percent)
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

float CTextProcessing::GetShadowPercent() const
{
    return _shadowPercent;
}

void CTextProcessing::Clear()
{
    _textOfShown = "";
    _length =
    _index = 0;
    _text = "";
    _sfText.setString("");
}

void CTextProcessing::SetText(string msg)
{
    _status = RUNNING;
    _textOfShown = "";
    _length =
    _index = 0;
    _text = msg;
    Process();
}

string CTextProcessing::GetText()
{
    return _text;
}

void CTextProcessing::Process()
{
    size_t __index = 0;
    size_t __cursorPos = 0;
    size_t __fontSize = _sfText.getCharacterSize();

    while (__index < _text.length()){
        size_t __size = CTextFunction::SizeOfCharWithUTF8(_text[__index]);
        string __str = "";

        __cursorPos += __size==1?__fontSize>>1:__fontSize;

        if (__size == 1 && __index > 0){
            if (_text[__index] == '\n'){
                __cursorPos=0;
            }
            else if (!isWordOrNumber(_text[__index-1])){
                for (size_t i=__index; i<_text.length(); i++){
                    if (!isWordOrNumber(_text[i])){
                        if (__cursorPos+(i-__index)*(__fontSize>>1) > _rowWidth)
                            __str = "\n";
                        break;
                    }
                }
            }
        }
        else if (__cursorPos > _rowWidth)
            __str = "\n";

        _textOfShown += __str + _text.substr(__index, __size);

        if (__str == "\n"){
            __cursorPos=__size==1?__fontSize>>1:__fontSize;
            _length++;
        }

        __index += __size;
        _length++;
    }

    _text = _textOfShown;
    _textOfShown = "";
}

void CTextProcessing::OnLoop()
{
    _sfText.setPosition(_coordinate);
    if (_oldTime + CCommon::_Common.TEXT_FRAMERATE <= CCommon::_Common.GetTicks() || _isSkip){
        _oldTime = CCommon::_Common.GetTicks();
    }
    else
        return;

    if (_status == RUNNING){
        if (_index < _text.length()){
            if (_isSkip){
                _textOfShown = _text;
                _index = _text.length();
                _isSkip = false;
            }
            else{
                size_t __size = CTextFunction::SizeOfCharWithUTF8(_text[_index]);
                _textOfShown.append(_text.substr(_index, __size));
                _index += __size;
            }
            CTextFunction::SetString(_sfText, _textOfShown);
        }
        else{
            _status = FINISH;
        }
    }
}

void CTextProcessing::Confirm()
{
    _status = CONFIRMED;
}

void CTextProcessing::Skip()
{
    _isSkip = true;
}

void CTextProcessing::OnRender(sf::RenderTarget* Surf_Dest)
{
    sf::Vector2f __tmp = _sfText.getOrigin();
    _sfText.setOrigin(__tmp.x - 2.0f, __tmp.y - 2.0f);
    _sfText.setColor(sf::Color(_shadowColor.r, _shadowColor.g, _shadowColor.b, _pAlpha == NULL ? 200 : *_pAlpha * _shadowPercent));
    Surf_Dest->draw(_sfText);

    _sfText.setOrigin(__tmp);
    _sfText.setColor(sf::Color(_textColor.r, _textColor.g, _textColor.b, _pAlpha == NULL ? 255 : *_pAlpha));
    Surf_Dest->draw(_sfText);
}

CTextProcessing::EStatus CTextProcessing::GetStatus() const
{
    return _status;
}

float CTextProcessing::GetWidth()
{
    return _sfText.getGlobalBounds().width;
}

float CTextProcessing::GetHeight()
{
    return _sfText.getGlobalBounds().height;
}

sf::Vector2f CTextProcessing::GetLastCharacterPos()
{
    return _sfText.findCharacterPos(_length);
}

sf::Vector2f CTextProcessing::GetPosition()
{
    return _coordinate;
}

void CTextProcessing::SetPosition(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}

const sf::Color& CTextProcessing::GetTextColor() const
{
    return _textColor;
}
    
const sf::Color& CTextProcessing::GetShadowColor() const
{
    return _shadowColor;
}
