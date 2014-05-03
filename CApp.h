/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
//#include "Common/Define.h"
#include "Common/CEvent.h"
//#include "CSurface.h"
#include "GSM_Window/CMessageBox.h"
#include "Stage_Talk/CCharacterLayer.h"
#include "Parser/CParser.h"
#include "Parser/CScriptCommand.h"
#include "Sound/CSoundBank.h"
#include "Gui/CButton.h"
#include "Effect/CParticleSystem.h"
#include "Common/CResourceManager.h"

//==============================================================================

class CApp : public CEvent {
    private:
        bool                          Running;

        sf::RenderWindow*    sf_Display;

        bool                          FullScreen;
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
