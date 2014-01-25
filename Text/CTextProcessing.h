/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CTEXTPROCESSING_H_
    #define _CTEXTPROCESSING_H_

#include <SFML/Graphics.hpp>
#include "CFont.h"
#include <string>
#include <map>
#include "../Graphics/CSurface.h"
#include "../Common/CCommon.h"


class CTextProcessing
{
  private:
        sf::Vector2f   _coordinate;
        bool            _isSkip;
        string          _text;
        string          _textOfShown;
        sf::Text           _sfText;
        unsigned int    _rowWidth;
        unsigned int    _cursorPos;
        unsigned int    _index;
        sf::Color          _textColor;
        sf::Color          _shadowColor;
        unsigned long   _oldTime;
        CFont           _font;

        bool isWordOrNumber(char c);
    public:
        CTextProcessing();

        bool OnInit(unsigned int width, unsigned int height=0);
        void OnLoop();
        void OnRender(sf::RenderWindow* Surf_Dest);
        void Skip();
        void Clear();
        bool IsTextAllShown();

        virtual void SetText(string msg, bool isAppend=false);
        string GetText();
        float GetWidth();
        float GetHeight();
        sf::Vector2f GetCharacterPos(unsigned int index); 
        sf::Vector2f GetPosition();
        void SetPosition(float x, float y);
};

#endif
