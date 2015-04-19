/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() 
{
    _display = new sf::RenderWindow();

    if (!CCommon::_Common.OnInit())
        return false;

    CParser::_Parser.SetRunning(&_running);
    _EndableOfIcon = CSurface::OnLoad(CCommon::_Common.GAME_ICON.c_str(), _icon);

    if (CCommon::_Common.FULL_SCREEN)
        SetFullScreen(true);
    else
        SetWindow(true);

    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if (!CResourceControl::_ResourceManager.OnInit(CCommon::_Common.GAME_PATH.c_str(), _display)){
        cout << "CApp::OnInit(): can't find script file \"" 
            << CCommon::_Common.GAME_PATH.c_str() << "\"." << endl;
        return false;
    }

    return true;
}

//==============================================================================
