/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CBUTTONBASE_H_
    #define _CBUTTONBASE_H_

#include <string>
#include <map>
#include "../Animation/CAnimation.h"
#include "../Graphics/CSequenceOfSprite.h"
#include "../Common/CConfigFile.h"
#include "../Common/CResourceControl.h"

using namespace std;

class CButtonBase : public CSequenceOfSprite
{
    private:
        bool            _isMouseOver;
        bool            _isMouseDown;
        string          _seNameOfMouseOver;
        string          _seNameOfMouseDown;
    protected:
        virtual bool CheckList(Object json);
        virtual bool SetProperty(Object json, bool isLoad=true);
        virtual void Exec(void* data=NULL)=0;
    public:
        CAnimation      _AnimationControl;

        CButtonBase(float x=0.0f, float y=0.0f, int w=1, int h=1, int maxframes=1, int framerate=10);

        bool IsMouseOver() const;
        bool IsMouseDown() const;

        virtual void OnLoop();
        virtual bool OnMouseMove(int x, int y);
        virtual bool OnLButtonDown(int x, int y);
        virtual bool OnLButtonUp(int x, int y);
};

#endif