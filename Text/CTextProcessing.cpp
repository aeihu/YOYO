/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
    _length =
    _cursorPos = 0;

    _textOfShown =
    _text = "";
    _textColor.r = CCommon::common.CHAR_COLOR_RED;
    _textColor.g = CCommon::common.CHAR_COLOR_GREEN;
    _textColor.b = CCommon::common.CHAR_COLOR_BLUE;
    _textColor.a = CCommon::common.CHAR_COLOR_ALPHA;
    
    _shadowColor.r = CCommon::common.CHAR_SHADOW_COLOR_RED;
    _shadowColor.g = CCommon::common.CHAR_SHADOW_COLOR_GREEN;
    _shadowColor.b = CCommon::common.CHAR_SHADOW_COLOR_BLUE;
    _shadowColor.a = CCommon::common.CHAR_SHADOW_COLOR_ALPHA;
}

bool CTextProcessing::isWordOrNumber(char c)
{
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 121) || (c >= 43 && c <= 58);
}

bool CTextProcessing::OnInit(unsigned int width, unsigned int height)
{
    _rowWidth = width;
    if (!CFont::LoadFont(CCommon::common.FONT_PATH.c_str()))
        return false; 

    _sfText.setFont(_font);
    return true;
}

void CTextProcessing::Clear()
{
    _textOfShown = "";
    _cursorPos =
    _length =
    _index = 0;
    _text = "";
    _sfText.setString("");
}

void CTextProcessing::SetText(string msg, bool isAppend)
{
    if (isAppend){
        if (!_textOfShown.empty())
            _textOfShown += "\n\n";
    }
    else
        _textOfShown = "";

    _cursorPos =
    _length =
    _index = 0;
    _text = msg;
}

string CTextProcessing::GetText()
{
    return _text;
}

void CTextProcessing::OnLoop()
{
    do {
        _sfText.setPosition(_coordinate);
        if (_oldTime + CCommon::common.TEXT_FRAMERATE <= CCommon::common.GetTicks() || _isSkip){
            _oldTime = CCommon::common.GetTicks();
        }
        else
            return;

        if (_index < _text.length()){
            unsigned int __fontSize = _sfText.getCharacterSize();
            unsigned int __size = CCommon::common.SizeOfCharWithUTF8(_text[_index]);
            string __str = "";

            _cursorPos += __size==1?__fontSize>>1:__fontSize;

            if (__size == 1 && _index > 0){
                if (!isWordOrNumber(_text[_index-1]))
                    for (unsigned int i=_index; i<_text.length(); i++){
                        if (!isWordOrNumber(_text[i])){
                            if (_cursorPos+(i-_index)*(__fontSize>>1) > _rowWidth)
                                __str = "\n";
                            break;
                        }
                    }
            }
            else if (_cursorPos > _rowWidth)
                __str = "\n";

            _textOfShown += __str + _text.substr(_index, __size);

            if (__str == "\n"){
                _cursorPos=__size==1?__fontSize>>1:__fontSize;
                _length++;
            }

            _index += __size;
            _length++;

            CFont::SetString(_sfText, _textOfShown);
        }
        else
            _isSkip = false;
    }while (_isSkip);
}

void CTextProcessing::Skip()
{
    _isSkip = true;
}

void CTextProcessing::OnRender(sf::RenderWindow* Surf_Dest)
{
    _sfText.setOrigin(-2.0f, -2.0f);
    _sfText.setColor(sf::Color(200, 128, 0, 100));
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
