/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CLOGBOX_H_
    #define _CLOGBOX_H_

#include "../Gui/CBox.h"
#include "../Gui/CTextLog.h"
#include "../Gui/CScrollbar.h"
#include "../Common/CConfigFile.h"
#include <deque>

using namespace std;

class CLogBox : public CBox, public CScrollbar
{
    private:
        unsigned int                _logMax;
        unsigned int                _visNum;
        sf::Vector2f                _logOffset;
        sf::Vector2f                _scrollbarOffset;
        deque<CTextLog*>            _logList;
    protected:
        bool CheckList(map<string, string>& list);
        bool SetProperty(map<string, string>& list);
    public:
        CLogBox();

        void OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        bool OnRButtonDown(int x, int y);
        bool OnRButtonUp(int x, int y);
        bool OnLoop();
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();

        void AddLog(string text, sf::SoundBuffer* voice, sf::Font& font);
};

#endif
