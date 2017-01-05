/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CResourceControl.h"

//------------------------------------------------------------------------------
bool CResourceControl::OnLButtonDown(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING){
        if (CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonDown(mX, mY))
            return true;

        if (GetMsgboxPauseStatus()){
            OffMsgboxPause();
            _LuaControl.ResumeLuaThread();
            return true;
        }
    }
    return false;
}

bool CResourceControl::OnLButtonUp(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonUp(mX, mY);

    return false;
}

bool CResourceControl::OnRButtonDown(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnRButtonDown(mX, mY);
        
    return false;
}

bool CResourceControl::OnRButtonUp(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnRButtonUp(mX, mY);

    return false;
}

bool CResourceControl::OnMButtonDown(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnMButtonDown(mX, mY);

    return false;
}

bool CResourceControl::OnMButtonUp(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnMButtonUp(mX, mY);

    return false;
}
//------------------------------------------------------------------------------
bool CResourceControl::OnMouseMove(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnMouseMove(mX, mY);

    return false;
}

bool CResourceControl::OnMouseWheel(int delta)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnMouseWheel(delta);

    return false;
}

bool CResourceControl::OnKeyDown(sf::Event::KeyEvent key)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnKeyDown(key);

    return false;
}

bool CResourceControl::OnKeyUp(sf::Event::KeyEvent key)
{
    if (_processStatus == CResourceControl::PLAYING)
        return CResourceControl::_ResourceManager._DrawableObjectControl.OnKeyUp(key);

    return false;
}

//==============================================================================
