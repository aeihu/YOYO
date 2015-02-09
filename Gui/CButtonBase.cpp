/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CButtonBase.h"
#include "../Sound/CSoundBank.h"

CButtonBase::CButtonBase(float x, float y, int w, int h, int maxframes, int framerate):CSequenceOfSprite(x,y,0,0,w,h)
{
    SetMaxFrames(maxframes);
    SetFrameRate(framerate);
    SetCurrentFrame(0);
    _AnimationControl._Type = CAnimation::Backward;
    _isMouseDown = false;
    _isMouseOver = false;
    _seNameOfMouseOver = CCommon::_Common.MOUSEOVER_SE;
    _seNameOfMouseDown = CCommon::_Common.MOUSEDOWN_SE;
    SetPosition(x, y);
}

bool CButtonBase::OnLButtonDown(int x, int y)
{
    if (_visible)
        if (_isMouseOver)
        {
            _isMouseDown = true;
            SetCurrentImageFrame(GetMaxFrames());
            _AnimationControl.SetCurrentFrame(GetMaxFrames()-1);
            CResourceControl::_ResourceManager._SoundControl.PlaySE(_seNameOfMouseDown);
            return true;
        }

    return false;
}

bool CButtonBase::OnLButtonUp(int x, int y)
{
    if (_visible){
        if(_isMouseOver){
            _isMouseDown = false;
            SetCurrentImageFrame(GetMaxFrames()-1);
            Exec();
            return true;
        }
        else{
            SetCurrentImageFrame(_AnimationControl.GetCurrentFrame());
        }
    }

    return false;
}

bool CButtonBase::OnSubLoop()
{
    //bool __result = CImageBaseClass::OnLoop();

    if (!_isMouseDown){
        return CSequenceOfSprite::OnSubLoop();
    }

    return false;
}

bool CButtonBase::IsMouseOver() const
{
    return _isMouseOver;
}

bool CButtonBase::IsMouseDown() const
{
    return _isMouseDown;
}

bool CButtonBase::OnMouseMove(int x, int y)
{
    if (_visible){
        if(( x > GetPosition().x ) && ( x < GetPosition().x + GetWidth()) && 
            ( y > GetPosition().y ) && ( y < GetPosition().y + GetHeight())){
            if (!_isMouseOver)
            _isMouseOver = true;
            _AnimationControl._Type = CAnimation::Forward;
            return true;
        }
        else{
            _isMouseOver = false;
            _isMouseDown = false;
            _AnimationControl._Type = CAnimation::Backward;
        }
    }
    return false;
}

bool CButtonBase::CheckList(Object json) 
{
    bool result = true;
    if (!json.has<String>("TILESET_PATH")){
        cout << "can't find value of TILESET_PATH." << endl;
        result = false;
    }

    if (!json.has<Number>("WIDTH")){
        cout << "can't find value of WIDTH." << endl;
        result = false;
    }

    if (!json.has<Number>("HEIGHT")){
        cout << "can't find value of HEIGHT." << endl;
        result = false;
    }

    if (!json.has<Number>("MAX_FRAMES")){
        cout << "can't find value of MAX_FRAMES." << endl;
        result = false;
    }

    if (!json.has<Number>("FRAME_RATE")){
        cout << "can't find value of FRAME_RATE." << endl;
        result = false;
    }

    if (!json.has<Number>("X")){
        cout << "can't find value of X." << endl;
        result = false;
    }

    if (!json.has<Number>("Y")){
        cout << "can't find value of Y." << endl;
        result = false;
    }

    return result;
}

bool CButtonBase::SetProperty(Object json)
{    
    SetWidth(json.get<Number>("WIDTH"));
    SetHeight(json.get<Number>("HEIGHT"));
    if (!LoadImg(json.get<String>("TILESET_PATH").c_str()))
        return false;

    SetMaxFrames(json.get<Number>("MAX_FRAMES"));
    SetFrameRate(json.get<Number>("FRAME_RATE"));
    SetPosition(json.get<Number>("X"), json.get<Number>("Y"));

    return true;
}
