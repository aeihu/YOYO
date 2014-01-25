/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
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
    //SDL_Delay(CCommon::common.LOOP_INTERVAL);
    //
 //   CFPS::FPSControl.OnLoop();
    //
 //   char Buffer[255];
 //   sprintf(Buffer, CCommon::common.GAME_NAME.c_str(), CFPS::FPSControl.GetFPS());
    //SDL_WM_SetCaption(Buffer, NULL);

    //if (CAdderControl::AdderControl.Onloop(CCommon::common.GetTicks())<1)
 //   //--------------------------------------------------------------------------
 //   // Entities
 //   //--------------------------------------------------------------------------
    //int v = 0;
    //if (CCommon::common.EventFocus != 99)
    //{
    //    CArea::AreaControl.OnLoop();
    //    CCommon::common.EventFocus = MAP_FOCUS;

    //    v = CEntity::EntityList.size();
    //    if (v > 1)
    //        std::sort(CEntity::EntityList.begin(), CEntity::EntityList.end(),CEntityCompare);

    //    for(int i = 0;i < v;i++) {
    //        if(!CEntity::EntityList[i]) continue;
    //    
    //        CEntity::EntityList[i]->OnLoop();
    //    }
    //
    //    //Collision Events
    //    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
    //        CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
    //        CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;

    //        if(EntityA == NULL || EntityB == NULL) continue;

    //        if(EntityA->OnCollision(EntityB)) {
    //            EntityB->OnCollision(EntityA);
    //        }
    //    }

    //    CEntityCol::EntityColList.clear();
    //}
    //else
    //{
    //    CBattle::battle.OnLoop();
    //}
    //
    //if (CBackground::background.Visible)
    //{
    //    CBackground::background.OnLoop();
    //}
    //
    //v = CPositions::PositionsControl._CharacterList.size() - 1;
    //
    CResourceManager::_BackgroundLayerControl.OnLoop(__isPause);
    CResourceManager::_CharacterLayerControl.OnLoop(__isPause);
    CResourceManager::_ImgLayerControl.OnLoop(__isPause);
    CResourceManager::_MessageBoxControl.OnLoop(__isPause);
    CResourceManager::_ButtonControl.OnLoop(__isPause);

    CSoundBank::SoundControl.OnLoop();
    //if (CMessageBox::messagebox.Visible)

    //if (CMessageBox::messagebox.GetAnimateState() == 1)
    //    CCommon::common.EventFocus = MESSAGEBOX_FOCUS;

    //{
    //    map<std::string, CButton*>::iterator it;
    //    for ( it=CButtonControl::ButtonControl.ButtonList.begin() ; it != CButtonControl::ButtonControl.ButtonList.end(); it++ )
    //    {
    //        if ((*it).second->Visible)
    //            (*it).second->OnLoop();
    //        
    //        if ((*it).second->GetAnimateState() == 1)
    //            CCommon::common.EventFocus = BUTTON_FOCUS;
    //    }
    //}

    //if (CEquipListBox::equiplistbox.Visible)
    //    CEquipListBox::equiplistbox.OnLoop();
    //
    //if (CSkillListBox::skilllistbox.Visible)
    //    CSkillListBox::skilllistbox.OnLoop();
    //
    //if (CItemListBox::itemlistbox.Visible)
    //    CItemListBox::itemlistbox.OnLoop();
    //
    //if (CMagicListBox::magiclistbox.Visible)
    //    CMagicListBox::magiclistbox.OnLoop();

    //if (CObjectInfoBox::objectinfobox.Visible)
    //    CObjectInfoBox::objectinfobox.OnLoop();
    //
    //if (CMenuBox::menubox.Visible)
    //    CMenuBox::menubox.OnLoop();

    //if (CLogBox::logbox.Visible)
    //    CLogBox::logbox.OnLoop();

    //if (CLogBox::logbox.GetAnimateState() == 1)
    //    CCommon::common.EventFocus = LOGBOX_FOCUS;

    //if (CMessageBox::messagebox.GetPrintState() == PRINT_COMPLETE)
    //{
    //    CLogBox::logbox.AddLog(CMessageBox::messagebox.Cpoy_Surface_Message());
    //    CMessageBox::messagebox.SetPrintStateToIdel();
    //}

    //CAnimationBank::animationbank.OnLoop();
    if (CParser::parser.IsDeplaying() || __isPause)
        return;
    
    CParser::parser.OnLoop();
}

//==============================================================================
