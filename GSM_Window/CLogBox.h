/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
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

class CLogBox : public CBox
{
    private:
        size_t                      _logMax;
        size_t                      _logRowHeight;
        size_t                      _visNum;
        sf::Vector2f                _logOffset;
        deque<CTextLog*>            _logList;
        CScrollbar                  _scrollbar;
    protected:
        bool CheckList(Object json);
        bool SetProperty(Object json);
    public:
        CLogBox();
        
        static CLogBox* Create(const char* filename);
        bool OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        bool OnRButtonDown(int x, int y);
        bool OnRButtonUp(int x, int y);
        void OnSubLoop();
        void OnSubRender(sf::RenderTarget* Surf_Dest);
        void OnCleanup();

        void AddLog(string text, sf::SoundBuffer* voice, sf::Font& font);
        void AddLog(string text, sf::SoundBuffer* voice);
};

#endif
