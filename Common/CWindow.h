/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CWINDOW_H_
    #define _CWINDOW_H_

#include "../Common/Define.h"

class CSprite;
class CText;

class CWindow
{
    private:
        sf::RenderWindow    _renderWindow;
    public:
        CWindow();
        ~CWindow();

        void Draw(const CSprite sp, const sf::RenderStates &states=sf::RenderStates::Default);
        void Draw(const CText &tx, const sf::RenderStates &states=sf::RenderStates::Default);

        void SetFramerateLimit (unsigned int limit);
        void Create(sf::VideoMode mode, const sf::String &title, sf::Uint32 style=sf::Style::Default, const sf::ContextSettings &settings=sf::ContextSettings());
        void Clear(const CColor color=CColor(0, 0, 0, 255));
        void Display();
        bool IsOpen() const;
        bool PollEvent(sf::Event &event);
};

#endif
