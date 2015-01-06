/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CTextProcessing.h"
#include <string>

using namespace std;

CTextProcessing::CTextProcessing()
{
    _coordinate.x = _coordinate.y = 0.0f;
    _isSkip = false;
    _rowWidth =
    _index=
    _oldTime =
    _length = 0;

    _textOfShown =
    _text = "";
    _textColor.r = CCommon::_Common.CHAR_COLOR_RED;
    _textColor.g = CCommon::_Common.CHAR_COLOR_GREEN;
    _textColor.b = CCommon::_Common.CHAR_COLOR_BLUE;
    _textColor.a = CCommon::_Common.CHAR_COLOR_ALPHA;
    
    _shadowColor.r = CCommon::_Common.CHAR_SHADOW_COLOR_RED;
    _shadowColor.g = CCommon::_Common.CHAR_SHADOW_COLOR_GREEN;
    _shadowColor.b = CCommon::_Common.CHAR_SHADOW_COLOR_BLUE;
    _shadowColor.a = CCommon::_Common.CHAR_SHADOW_COLOR_ALPHA;
}

bool CTextProcessing::isWordOrNumber(char c)
{
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 121) || (c >= 43 && c <= 58);
}

void CTextProcessing::SetRowWidth(size_t width)
{
    _rowWidth = width;
}

void CTextProcessing::SetFont(sf::Font& font)
{
    _sfText.setFont(font);
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
    //if (isAppend){
    //    if (!_textOfShown.empty())
    //        _textOfShown += "\n\n";
    //}
    //else
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
            if (!isWordOrNumber(_text[__index-1]))
                for (size_t i=__index; i<_text.length(); i++){
                    if (!isWordOrNumber(_text[i])){
                        if (__cursorPos+(i-__index)*(__fontSize>>1) > _rowWidth)
                            __str = "\n";
                        break;
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
}

void CTextProcessing::Skip()
{
    _isSkip = true;
}

void CTextProcessing::OnRender(sf::RenderTarget* Surf_Dest)
{
    _sfText.setOrigin(-2.0f, -2.0f);
    _sfText.setColor(_shadowColor);
    Surf_Dest->draw(_sfText);

    _sfText.setOrigin(0.0f, 0.0f);
    _sfText.setColor(_textColor);
    Surf_Dest->draw(_sfText);
}

bool CTextProcessing::IsTextAllShown()
{
    return _index>=_text.length();
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
