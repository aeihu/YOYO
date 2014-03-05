/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include <string>
#include <map>
#include "../Animation/CAnimation.h"
#include "../Parser/CParser.h"
#include "../Graphics/CSequenceOfFrames.h"

using namespace std;
//The button
class CButton : public CSequenceOfFrames
{
    private:
        bool            _isMouseOver;
        bool            _isMouseDown;
        string          _seNameOfMouseOver;
        string          _seNameOfMouseDown;

        bool CheckList(map<string, string> list);
        bool SetProperty(map<string, string> list);
        bool Subclass_Loop();
    public:
        CAnimation      _AnimationControl;
        list<string>    _CmdList;

        CButton(float x=0.0f, float y=0.0f, int w=1, int h=1, int maxframes=1, int framerate=10);

        bool LoadButton(const char* FileName);
        void OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
};

#endif