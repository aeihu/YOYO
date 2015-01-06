/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CTEXTPROCESSING_H_
    #define _CTEXTPROCESSING_H_

#include <SFML/Graphics.hpp>
#include "CFont.h"
#include "CTextFunction.h"
#include <string>
#include <map>
#include "../Graphics/CSurface.h"
#include "../Common/CCommon.h"


class CTextProcessing
{
    private:
        sf::Vector2f        _coordinate;
        bool                _isSkip;
        string              _text;
        string              _textOfShown;
        sf::Text            _sfText;
        size_t              _rowWidth;
        size_t              _index;
        size_t              _length;
        sf::Color           _textColor;
        sf::Color           _shadowColor;
        unsigned long       _oldTime;

        bool isWordOrNumber(char c);
        void Process();
    public:
        CTextProcessing();

        void SetRowWidth(size_t width);
        virtual void SetFont(sf::Font& font);
        void OnLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);
        void Skip();
        void Clear();
        bool IsTextAllShown();

        virtual void SetText(string msg);
        string GetText();
        float GetWidth();
        float GetHeight();
        sf::Vector2f GetLastCharacterPos(); 
        sf::Vector2f GetPosition();
        void SetPosition(float x, float y);
};

#endif
