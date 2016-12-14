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
    _status = CONFIRMED;
    _isSkip = false;
    _rowWidth =
    _index=
    _oldTime =
    _length = 0;
    _textOfShown =
    _text = "";
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

void CTextProcessing::SetRowWidth(size_t width)
{
    _rowWidth = width;
}

void CTextProcessing::Clear()
{
    _textOfShown = "";
    _length =
    _index = 0;
    _text = "";
    _sfText.setString("");
}

void CTextProcessing::SetString(string msg)
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
    CText::OnLoop();

    if (IsShowed()){
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
}

void CTextProcessing::Confirm()
{
    _status = CONFIRMED;
}

void CTextProcessing::Skip()
{
    _isSkip = true;
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
