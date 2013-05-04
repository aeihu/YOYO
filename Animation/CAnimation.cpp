/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
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
    _currentFrame    = 0;
    _MaxFrames       = 0;
    _frameInc        = 1;
    _frameRate       = 100; //Milliseconds
    _oldTime         = 0;
}

//------------------------------------------------------------------------------
void CAnimation::OnAnimate(unsigned long time) 
{
    if(_oldTime+_frameRate>time) 
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
      if(_currentFrame >= _MaxFrames) {
        _frameInc = -_frameInc;
                _currentFrame = _MaxFrames - 1;
      }
  }
    else{
    if(_currentFrame <= 0) {
      _frameInc = -_frameInc;
            _currentFrame = 0;
    }
  }
}

void CAnimation::OnALoop()
{
    if (_frameInc<0)
        _frameInc = -_frameInc;

    _currentFrame += _frameInc;
    if(_currentFrame >= _MaxFrames) {
        _currentFrame = 0;
    }
}

void CAnimation::OnForWard()
{
    if (_frameInc<0)
        _frameInc = -_frameInc;

    _currentFrame += _frameInc;
    if(_currentFrame >= _MaxFrames) {
            _currentFrame = _MaxFrames - 1;
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
    if(frame < 0 || frame >= _MaxFrames) return;

    _currentFrame = frame;
}

//------------------------------------------------------------------------------
int CAnimation::GetCurrentFrame() 
{
    return _currentFrame;
}

//------------------------------------------------------------------------------
void CAnimation::SetFrameInc(int inc) 
{
    _frameInc = inc;
}

//==============================================================================
