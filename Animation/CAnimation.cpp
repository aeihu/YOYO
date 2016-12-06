/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
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
    _Type = Forward;
    _isLoop =
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
            
            if (!_isLoop){
                _currentFrame = 0;
                TurnOff();
            }
            else
                _currentFrame = 0;
        }
    }
}

void CAnimation::OnForWard()
{
    if (_frameInc<0)
        _frameInc = -_frameInc;

    _currentFrame += _frameInc;
    if(_currentFrame >= _maxFrames) {
        if (!_isLoop){
            _currentFrame = _maxFrames - 1;
            TurnOff();
        }
        else
            _currentFrame = 0;
    }
}

void CAnimation::OnBackWard()
{
    if (_frameInc>0)
        _frameInc = -_frameInc;

    _currentFrame += _frameInc;
    if(_currentFrame <= 0) {
        if (!_isLoop){
            _currentFrame = 0;
            TurnOff();
        }
        else
            _currentFrame = _maxFrames - 1;
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

void CAnimation::TurnOn(bool loop)
{
    _isLoop = loop;
    _enable = true;
}

//------------------------------------------------------------------------------

void CAnimation::TurnOff()
{
    _enable = false;
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