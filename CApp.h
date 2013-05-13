/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SFML/Window.hpp>
#include "Common/CCommon.h"
#include "Common/CAdder.h"
#include <algorithm>
#include "Common/CFPS.h"
#include "Common/Define.h"
#include "Stage_Action/CArea.h"
#include "Battlefield/CBattle.h"
#include "Stage_Action/CCamera.h"
#include "Stage_Action/CEntity.h"
#include "Common/CEvent.h"
//#include "CSurface.h"
#include "GSM_Window/CMessageBox.h"
#include "Stage_Action/CPlayer.h"
#include "Stage_Talk/CCharacterLayer.h"
#include "Parser/CParser.h"
#include "Parser/CScriptCommand.h"
#include "Sound/CSoundBank.h"
#include "Gui/CButton.h"
#include "GSM_Window/CObjectInfoBox.h"
#include "GSM_Window/CMenuBox.h"
#include "Battlefield/CCharacterData.h"
#include "Animation/CAnimationBank.h"
#include "GSM_Window/CEquipListBox.h"
#include "GSM_Window/CSkillListBox.h"
#include "GSM_Window/CItemListBox.h"
#include "GSM_Window/CMagicListBox.h"
#include "GSM_Window/CLogBox.h"
#include "Common/CResourceManager.h"

//==============================================================================

class CApp : public CEvent {
    private:
        bool                        Running;

        CWindow*                    sf_Display;

        bool                        FullScreen;

    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(sf::Event* Event);

        void OnKeyDown(sf::Event::KeyEvent key);

        void OnKeyUp(sf::Event::KeyEvent key);

        void OnLButtonDown(int mX, int mY);
        
        void OnLButtonUp(int mX, int mY);
                
        void OnRButtonDown(int mX, int mY);

        void OnRButtonUp(int mX, int mY);

        void OnMouseMove(int mX, int mY);

        void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

//==============================================================================

#endif
