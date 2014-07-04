/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CAnimation.h"

//==============================================================================
CAnimation::CAnimation() 
{
    _currentFrame = 0;
    _maxFrames = 0;
    _frameInc = 1;
    _frameRate = 100; //Milliseconds
    _oldTime = 0;
    _counter = -1;
    _Type = Forward;
    _enable = false;
}

//------------------------------------------------------------------------------
void CAnimation::OnAnimate(unsigned long time) 
{
    if(_oldTime+_frameRate>time || !_enable) 
        return;

    _oldTime = time;

    switch(_Type){
        case Oscillate:
            OnOscillate();
        break;
        case Loop:
            OnALoop();
        break;
        case Forward:
            OnForWard();
        break;
        case Backward:
            OnBackWard();
        break;
    }
}

void CAnimation::OnOscillate()
{
    _currentFrame += _frameInc;
    if(_frameInc > 0) {
        if(_currentFrame >= _maxFrames) {
            _frameInc = -_frameInc;
            _currentFrame = _maxFrames - 1;
        }
    }
    else{
        if(_currentFrame <= 0) {
            _frameInc = -_frameInc;
            _currentFrame = 0;
            
            if (_counter == 1)
                TurnOff();
            
            _counter -= 1;
        }
    }
}

void CAnimation::OnALoop()
{
    if (_frameInc<0)
        _frameInc = -_frameInc;

    _currentFrame += _frameInc;
    if(_currentFrame >= _maxFrames) {
        _currentFrame = 0;
    }
}

void CAnimation::OnForWard()
{
    if (_frameInc<0)
        _frameInc = -_frameInc;

    _currentFrame += _frameInc;
    if(_currentFrame >= _maxFrames) {
            _currentFrame = _maxFrames - 1;
    }
}

void CAnimation::OnBackWard()
{
    if (_frameInc>0)
        _frameInc = -_frameInc;

    _currentFrame += _frameInc;
    if(_currentFrame <= 0) {
        _currentFrame = 0;
    }
}

//==============================================================================
void CAnimation::SetFrameRate(int rate) 
{
    _frameRate = rate;
}

//------------------------------------------------------------------------------
void CAnimation::SetCurrentFrame(int frame) 
{
    if(frame < 0 || frame >= _maxFrames) return;

    _currentFrame = frame;
}

//------------------------------------------------------------------------------
int CAnimation::GetCurrentFrame() const
{
    return _currentFrame;
}

//------------------------------------------------------------------------------
bool CAnimation::GetEnable() const
{
    return _enable;
}

//------------------------------------------------------------------------------
void CAnimation::SetFrameInc(int inc) 
{
    _frameInc = inc;
}

//------------------------------------------------------------------------------

void CAnimation::TurnOn(int counter)
{
    if (counter != 0){
        _counter = counter;
        _enable = true;
    }
}

//------------------------------------------------------------------------------

void CAnimation::TurnOff(int frame)
{
    _enable = false;
    SetCurrentFrame(frame);
}

//==============================================================================

void CAnimation::SetMaxFrames(int frame)
{
    _maxFrames = frame < 0 ? 0 : frame;
}

int CAnimation::GetMaxFrames() const
{
    return _maxFrames;
}