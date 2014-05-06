/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CApp.h"

#include <iostream>
#include <exception>
//==============================================================================
void CApp::OnLoop() {
    bool __isPause = false;

    CResourceManager::_BackgroundLayerControl.OnLoop(__isPause);
    CResourceManager::_CharacterLayerControl.OnLoop(__isPause);
    CResourceManager::_ImgLayerControl.OnLoop(__isPause);
    CResourceManager::_ParticleSystemControl.OnLoop(__isPause);
    CResourceManager::_MessageBoxControl.OnLoop(__isPause);
    CResourceManager::_ButtonControl.OnLoop(__isPause);

    CSoundBank::_SoundControl.OnLoop();

    if (CParser::_Parser.IsDeplaying() || __isPause)
        return;
    
    CParser::_Parser.OnLoop();
}

//==============================================================================
