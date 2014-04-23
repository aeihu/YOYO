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
void CApp::OnCleanup() {
    CResourceManager::_BackgroundLayerControl.OnCleanup();
    CResourceManager::_CharacterLayerControl.OnCleanup();
    CResourceManager::_ImgLayerControl.OnCleanup();
    CResourceManager::_MessageBoxControl.OnCleanup();
    CResourceManager::_ButtonControl.OnCleanup();
    CSoundBank::_SoundControl.OnCleanup();
}

//==============================================================================
