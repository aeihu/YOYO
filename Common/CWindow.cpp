/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CWindow.h"
#include "../Graphics/CSprite.h"
#include "../Graphics/CText.h"

CWindow::CWindow()
{}

CWindow::~CWindow()
{}

void CWindow::Draw(const CSprite sp, const sf::RenderStates &states)
{
    _renderWindow.draw(sp._sprite, states);
}

void CWindow::Draw(const CText &tx, const sf::RenderStates &states)
{
    _renderWindow.draw(tx._text, states);
}

void CWindow::SetFramerateLimit (unsigned int limit)
{
    _renderWindow.setFramerateLimit(limit);
}

void CWindow::Create(sf::VideoMode mode, const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings)
{
    _renderWindow.create(mode,title,style,settings);
}

void CWindow::Clear(const CColor color)
{
    _renderWindow.clear(sf::Color(color.r,color.g,color.b,color.a));
}

void CWindow::Display()
{
    _renderWindow.display();
}

bool CWindow::IsOpen() const
{
    return _renderWindow.isOpen();
}

bool CWindow::PollEvent(sf::Event &event)
{
    return _renderWindow.pollEvent(event);
}
