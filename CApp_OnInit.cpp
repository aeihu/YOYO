/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
    CSoundBank::_SoundControl.OnInit();

    if (!CResourceManager::_FontControl.AddCFont("__main", CCommon::_Common.FONT_PATH.c_str()))
        return false;

    sf_Display->create(
        sf::VideoMode(CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT, 32), 
        CCommon::_Common.GAME_NAME);

    sf_Display->setFramerateLimit(CCommon::_Common.MAX_FPS);

    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if (!CParser::_Parser.LoadScript(CCommon::_Common.GAME_PATH.c_str(), "init"))
    {
        cout << "CApp::OnInit(): can't find script file \"" << CCommon::_Common.GAME_PATH.c_str()
            << "\" or section [init]." << endl;
        return false;
    }

    return true;
}

//==============================================================================
