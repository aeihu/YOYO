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

    if (!CCommon::common.OnInit()){
        return false;
    }

    CParser::parser.SetRunning(&Running);

    sf_Display->create(
        sf::VideoMode(CCommon::common.WWIDTH, CCommon::common.WHEIGHT, 32), 
        CCommon::common.GAME_NAME);

    sf_Display->setFramerateLimit(CCommon::common.MAX_FPS);

    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if (!CParser::parser.LoadScript(CCommon::common.GAME_PATH.c_str(), "init"))
    {
        cout << "CApp::OnInit(): can't find script file \"" << CCommon::common.GAME_PATH.c_str()
            << "\" or section [init]." << endl;
        return false;
    }

    return true;
}

//==============================================================================
