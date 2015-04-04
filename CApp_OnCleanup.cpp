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
void CApp::OnCleanup() {
    CResourceControl::_ResourceManager.OnCleanup();

    _display->close();
    delete _display;
    _display = NULL;
}

//==============================================================================
