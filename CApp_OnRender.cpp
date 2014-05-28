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
void CApp::OnRender() {
    sf_Display->clear();
    //SDL_FillRect(sf_Display, &Rect, 0);
    //
    //if (CCommon::_Common._EventFocus != 99)
    //{
    //    CArea::AreaControl.OnRender(sf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
    //
    //    //--------------------------------------------------------------------------
    //    // Entities
    //    //--------------------------------------------------------------------------
    //    int v = CEntity::EntityList.size();

    //    for(int i = 0;i < v;i++) {
    //        if(!CEntity::EntityList[i]) continue;

    //        CEntity::EntityList[i]->OnRender(sf_Display);
    //    }
    //}
    //else
    //{
    //    CBattle::battle.OnRender(sf_Display);
    //}
    

    //CResourceManager::_BackgroundLayerControl.OnRender(sf_Display);
    //CResourceManager::_ParticleSystemControl.OnRender(sf_Display, 0);
    //CResourceManager::_CharacterLayerControl.OnRender(sf_Display);
    //CResourceManager::_ParticleSystemControl.OnRender(sf_Display, 1);
    //CResourceManager::_ImgLayerControl.OnRender(sf_Display);
    //CResourceManager::_MessageBoxControl.OnRender(sf_Display);
    //CResourceManager::_ButtonControl.OnRender(sf_Display);
    //CResourceManager::_LogBoxControl.OnRender(sf_Display);
    CControlOfImageBaseClass::_ResourceManager.OnRender(sf_Display);
    sf_Display->display();
}


//==============================================================================
