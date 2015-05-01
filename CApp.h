/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SFML/Window.hpp>
#include "Common/CCommon.h"
#include <algorithm>
#include "Common/CEvent.h"
#include "GSM_Window/CMessageBox.h"
#include "Stage_Talk/CCharacterLayer.h"
#include "Parser/CParser.h"
#include "Parser/CScriptCommand.h"
#include "Sound/CSoundBank.h"
#include "Gui/CButton.h"
#include "Effect/CParticleSystem.h"
#include "Common/CResourceControl.h"
#include "Graphics/CCamera.h"

//==============================================================================

class CApp : public CEvent {
    private:
        bool                        _running;
        bool                        _EndableOfIcon;
        sf::RenderWindow*           _display;
        sf::Image                   _icon;

        void SetWindow(bool isFirst=false);
        void SetFullScreen(bool isFirstt=false);
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
