/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
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
    public:
        enum EStatus
        {
            RUNNING,
            FINISH,
            CONFIRMED,
        };
    private:
        sf::Vector2f        _coordinate;
        bool                _isSkip;
        EStatus             _status;
        string              _text;
        string              _textOfShown;
        sf::Text            _sfText;
        size_t              _rowWidth;
        size_t              _index;
        size_t              _length;
        sf::Color           _textColor;
        sf::Color           _shadowColor;
        unsigned long       _oldTime;
        float               _shadowPercent;
        float*              _pAlpha;

        bool isWordOrNumber(char c);
        void Process();
    public:
        CTextProcessing();

        void SetCharacterSize(size_t size);
        void SetPointAlpha(float* alpha);
        void SetRowWidth(size_t width);
        virtual void SetFont(sf::Font& font);
        void OnLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);
        void Skip();
        void Clear();
        void Confirm();

        virtual void SetText(string msg);
        EStatus GetStatus() const;
        string GetText();
        float GetWidth();
        float GetHeight();
        sf::Vector2f GetLastCharacterPos(); 
        sf::Vector2f GetPosition();
        void SetPosition(float x, float y);
        
        void SetShadowPercent(float percent);
        float GetShadowPercent() const;

        void SetTextColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
        void SetShadowColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
        const sf::Color& GetTextColor() const;
        const sf::Color& GetShadowColor() const;
};

#endif
