/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() {
    //CArea::AreaControl.OnCleanup();

 //   //--------------------------------------------------------------------------
 //   // Entities
 //   //--------------------------------------------------------------------------
 //   for(int i = 0;i < CEntity::EntityList.size();i++) {
 //       if(!CEntity::EntityList[i]) continue;
    //    
 //       CEntity::EntityList[i]->OnCleanup();
    //    delete CEntity::EntityList[i];
 //   }

 //   CEntity::EntityList.clear();

 //   //--------------------------------------------------------------------------
 //   // CharacterLayer
 //   //--------------------------------------------------------------------------
    //
    //{
    //    map<std::string, CCharacterLayer*>::iterator it;
    //    for ( it=CPositions::PositionsControl._characterList.begin() ; it != CPositions::PositionsControl._characterList.end(); it++ )
    //    {
    //        if(!(*it).second) continue;

    //        (*it).second->OnCleanup();
    //        delete (*it).second;
    //    }
    //    CPositions::PositionsControl._characterList.clear();
    //}
    //
    //{
    //    map<std::string, CImgLayer*>::iterator it;

    //    for ( it=CImgLayer::ImgLayerList.begin() ; it != CImgLayer::ImgLayerList.end(); it++ )
    //    {
    //        (*it).second->OnCleanup();
    //        delete (*it).second;
    //    }
    //    CImgLayer::ImgLayerList.clear();
    //}

    //CAnimationBank::animationbank.OnCleanup();
    ////CImgLayer::ImgLayerList.clear();
    //CBackground::background.OnCleanup();
    //CButtonControl::ButtonControl.OnCleanup();
    //CLogBox::logbox.CBox::OnCleanup();
    //CMessageBox::messagebox.CBox::OnCleanup();
    //CParser::parser.OnCleanup();
    //CMenuBox::menubox.CBox::OnCleanup();
    //CObjectInfoBox::objectinfobox.CBox::OnCleanup();
    //CEquipListBox::equiplistbox.CBox::OnCleanup();
    //CSkillListBox::skilllistbox.CBox::OnCleanup();
    //CItemListBox::itemlistbox.CBox::OnCleanup();
    //CMagicListBox::magiclistbox.CBox::OnCleanup();
    //CPlayerDataControl::playerdatacontrol.OnCleanup();

    //CCommon::common.SaveSysData();
    //CCommon::common.OnCleanup();

 //   SDL_FreeSurface(sf_Display);
    //
    //CSoundBank::SoundControl.OnCleanup();
 //   TTF_Quit(); 
    //Mix_CloseAudio();
 //   SDL_Quit();
}

//==============================================================================
