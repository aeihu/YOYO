/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBUTTONBASE_H_
    #define _CBUTTONBASE_H_

#include <string>
#include <map>
#include "../Animation/CAnimation.h"
#include "../Parser/CParser.h"
#include "../Graphics/CSequenceOfFrames.h"

using namespace std;

class CButtonBase : public CSequenceOfFrames
{
    private:
        bool            _isMouseOver;
        bool            _isMouseDown;
        string          _seNameOfMouseOver;
        string          _seNameOfMouseDown;

        bool CheckList(map<string, string>& list);
        virtual bool Subclass_CheckList(map<string, string>& list){return true;}
        bool SetProperty(map<string, string>& list);
        virtual bool Subclass_SetProperty(map<string, string>& list){return true;}

        bool Subclass_Loop();
        virtual void Exec(void* data=NULL)=0;
    public:
        CAnimation      _AnimationControl;

        CButtonBase(float x=0.0f, float y=0.0f, int w=1, int h=1, int maxframes=1, int framerate=10);

        bool LoadButton(const char* FileName);
        void OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        bool IsMouseOver() const;
        bool IsMouseDown() const;
};

#endif