/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CTEXT_H_
    #define _CTEXT_H_

#include "../Common/Define.h"
#include "../Common/CWindow.h"

class CFont;

class CText
{
    private: 
        sf::Text    _text;
        friend void CWindow::Draw(const CText &tx, const sf::RenderStates &states);
    public:
        CText();
        ~CText();

        void SetOrigin(CCoordinate2f origin);
        void SetOrigin(float x, float y);
        void SetColor(const CColor color);
        void SetFont(CFont& font);
        void SetString(std::string str);
        void SetPosition(float x, float y);
        void SetPosition(CCoordinate2f pos);

        unsigned int GetCharacterSize() const;
        CFloatRect GetLocalBounds() const; 
        CFloatRect GetGlobalBounds() const; 

        CCoordinate2f FindCharacterPos(std::size_t index) const;

        //bool LoadFromFile(const std::string &filename, const sf::IntRect &area=sf::IntRect());
        //bool LoadFromMemory (const void *data, std::size_t size, const sf::IntRect &area=sf::IntRect());
        //bool LoadFromImage (const sf::Image &image, const sf::IntRect &area=sf::IntRect());

        //void SetSmooth (bool smooth);
        //bool IsSmooth () const;
        //unsigned int GetWidth();
        //unsigned int GetHeight();
};

#endif
