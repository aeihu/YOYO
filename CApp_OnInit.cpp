/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() 
{
    sf_Display = new sf::RenderWindow();

    if (!CCommon::_Common.OnInit())
        return false;

    CParser::_Parser.SetRunning(&Running);
    
    sf_Display->create(
        sf::VideoMode(CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT, 32), 
        CCommon::_Common.GAME_NAME,sf::Style::Close);

    sf_Display->setFramerateLimit(CCommon::_Common.MAX_FPS);

    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if (!CResourceControl::_ResourceManager.OnInit(CCommon::_Common.GAME_PATH.c_str(), sf_Display))
    {
        cout << "CApp::OnInit(): can't find script file \"" 
            << CCommon::_Common.GAME_PATH.c_str() << "\"." << endl;
        return false;
    }

    //sf::View _view;
    //_view.reset(sf::FloatRect(0, 0, CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT));
    //CCamera::Reset(0, 0, CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT);
    //_view.setViewport(sf::FloatRect(0, 0, 1, 1));
    //cout << _view.getCenter().x << ":" << _view.getCenter().y << endl;
    //cout << _view.getSize().x << ":" << _view.getSize().y << endl;
    //_view.zoom(2);
    //CCamera::SetCenter(CCommon::_Common.WWIDTH/2,CCommon::_Common.WHEIGHT/2);
    //CCamera::SetCenter(0,CCommon::_Common.WHEIGHT/2);
    //_view.setCenter(0,CCommon::_Common.WHEIGHT/2);
    //_view.setRotation(90);
    //CCamera::Bind(sf_Display);
    //sf_Display->setView(_view);
    return true;
}

//==============================================================================
