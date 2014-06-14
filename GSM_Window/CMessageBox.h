/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CMESSAGEBOX_H_
    #define _CMESSAGEBOX_H_

#include "../Gui/CBox.h"
#include "../Text/CTextProcessing.h"
#include <string>
#include <cstdio>
#include "../Common/CCommon.h"
#include "../Animation/CAnimation.h"
#include "../Graphics/CSequenceOfSprite.h"
#include "../Common/CResourceControl.h"

class CMessageBox : public CBox , public CTextProcessing
{        
    private:
        sf::Vector2f        _speakerNameOffset;
        sf::Vector2f        _msgOffset;
        sf::Text            _speakerName;
        CSequenceOfSprite   _frames;
        bool                _isPaused;

        bool CheckList(map<string, string>& list);
        bool SetProperty(map<string, string>& list);
    protected:
        using CBox::_visible;
    public:
        CMessageBox();
        
        static CMessageBox* Create(const char* filename);
        void SetText(string msg);
        void SetFont(sf::Font& font);
        void SetSpeakerName(string name);

        void OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        bool OnRButtonDown(int x, int y);
        bool OnRButtonUp(int x, int y);
        bool OnLoop();
        void OnRender(sf::RenderWindow* Surf_Dest);
};
#endif
