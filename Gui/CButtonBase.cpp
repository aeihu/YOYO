/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CButtonBase.h"
#include "../Sound/CSoundBank.h"
#include "../Common/CResourceControl.h"

CButtonBase::CButtonBase(float x, float y, int w, int h, int maxframes, int framerate):CSequenceOfSprite(x,y,0,0,w,h)
{
    SetMaxFrames(maxframes);
    SetFrameRate(framerate);
    SetCurrentFrame(0);
    _Type = CAnimation::Backward;
    _isMouseDown = false;
    _isMouseOver = false;
    _seNameOfMouseOver = CCommon::_Common.MOUSEOVER_SE;
    _seNameOfMouseDown = CCommon::_Common.MOUSEDOWN_SE;
    SetPosition(x, y);
}

bool CButtonBase::OnLButtonDown(int x, int y)
{
    if (IsShowed())
        if (_isMouseOver){
            _isMouseDown = true;
            SetCurrentImageFrame(GetMaxFrames());
            SetCurrentFrame(GetMaxFrames()-1);

            if (_seNameOfMouseDown != "")
                CResourceControl::_ResourceManager._SoundControl.PlaySE(
                    _seNameOfMouseDown, 1.0f, false);
            return true;
        }

    return false;
}

bool CButtonBase::OnLButtonUp(int x, int y)
{
    if (IsShowed()){
        _isMouseDown = false;
        if (_isMouseOver){
            SetCurrentImageFrame(GetMaxFrames()-1);
            Exec();
            return true;
        }
        else{
            SetCurrentImageFrame(GetCurrentFrame());
        }
    }

    return false;
}

void CButtonBase::OnLoop()
{
    if (_isMouseDown){
        CImgLayer::OnLoop();
    }
    else{
        CSequenceOfSprite::OnLoop();
    }
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
    if (IsShowed()){
        sf::FloatRect __rect = _sprite.getGlobalBounds();
        __rect.left = __rect.top = 0.f;
        __rect = GetTransform().transformRect(__rect);
        if (__rect.contains(sf::Vector2f(x, y))){
            if (!_isMouseOver)
            {
                _isMouseOver = true;
                TurnOn(false);

                if (_seNameOfMouseOver != "")
                    CResourceControl::_ResourceManager._SoundControl.PlaySE(
                    _seNameOfMouseOver, 1.0f, false);
            }

            _Type = CAnimation::Forward;
            return true;
        }
        else{
            _isMouseOver = false;
            _Type = CAnimation::Backward;
            TurnOn(false);
        }
    }
    return false;
}
