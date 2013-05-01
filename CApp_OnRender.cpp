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
void CApp::OnRender() {
	sf_Display->Clear();
	//SDL_FillRect(sf_Display, &Rect, 0);
	//
	//if (CCommon::common.EventFocus != 99)
	//{
	//	CArea::AreaControl.OnRender(sf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	//
	//	//--------------------------------------------------------------------------
	//	// Entities
	//	//--------------------------------------------------------------------------
	//	int v = CEntity::EntityList.size();

	//	for(int i = 0;i < v;i++) {
	//		if(!CEntity::EntityList[i]) continue;

	//		CEntity::EntityList[i]->OnRender(sf_Display);
	//	}
	//}
	//else
	//{
	//	CBattle::battle.OnRender(sf_Display);
	//}
	

	CResourceManager::_BackgroundLayerControl.OnRender(sf_Display);
	CResourceManager::_CharacterLayerControl.OnRender(sf_Display);
	CResourceManager::_ImgLayerControl.OnRender(sf_Display);
	CResourceManager::_MessageBoxControl.OnRender(sf_Display);
	CResourceManager::_ButtonControl.OnRender(sf_Display);
	//{
	//	map<std::string, CButton*>::iterator it;
	//	for ( it=CButtonControl::ButtonControl.ButtonList.begin() ; it != CButtonControl::ButtonControl.ButtonList.end(); it++ )
	//	{
	//		if ((*it).second->Visible)
	//			(*it).second->OnRender(sf_Display);
	//	}
	//}	

	//if (CEquipListBox::equiplistbox.Visible)
	//	CEquipListBox::equiplistbox.OnRender(sf_Display);
	//
	//if (CSkillListBox::skilllistbox.Visible)
	//	CSkillListBox::skilllistbox.OnRender(sf_Display);
	//
	//if (CItemListBox::itemlistbox.Visible)
	//	CItemListBox::itemlistbox.OnRender(sf_Display);
	//
	//if (CMagicListBox::magiclistbox.Visible)
	//	CMagicListBox::magiclistbox.OnRender(sf_Display);

	//if (CObjectInfoBox::objectinfobox.Visible)
	//	CObjectInfoBox::objectinfobox.OnRender(sf_Display);

	//if (CMenuBox::menubox.Visible)
	//	CMenuBox::menubox.OnRender(sf_Display);
	//
	//if (CMessageBox::messagebox.Visible)
	//	CMessageBox::messagebox.OnRender(sf_Display);
	//
	//if (CLogBox::logbox.Visible)
	//	CLogBox::logbox.OnRender(sf_Display);

	//CAnimationBank::animationbank.OnRender(sf_Display);

	//SDL_Flip(sf_Display);
	sf_Display->Display();
}


//==============================================================================
