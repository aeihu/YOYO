/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CResourceControl.h"

//------------------------------------------------------------------------------
void CResourceControl::OnLButtonDown(int mX, int mY)
{
    if (_loadingProcessStatus == CResourceControl::PLAYING){
        if (GetMsgboxPauseStatus()){
            OffMsgboxPause();
            _LuaControl.ResumeLuaThread();
        }
        else if (CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonDown(mX, mY))
            return;
    }
}

void CResourceControl::OnRButtonDown(int mX, int mY)
{
    if (_loadingProcessStatus == CResourceControl::PLAYING)
        if (CResourceControl::_ResourceManager._DrawableObjectControl.OnRButtonDown(mX, mY))
            return;
}

void CResourceControl::OnRButtonUp(int mX, int mY)
{
    if (_loadingProcessStatus == CResourceControl::PLAYING)
        if (CResourceControl::_ResourceManager._DrawableObjectControl.OnRButtonUp(mX, mY))
            return;
}
//------------------------------------------------------------------------------
void CResourceControl::OnLButtonUp(int mX, int mY)
{
    if (_loadingProcessStatus == CResourceControl::PLAYING)
        if (CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonUp(mX, mY))
            return;
}


//------------------------------------------------------------------------------
void CResourceControl::OnMouseMove(int mX, int mY)
{
    if (_loadingProcessStatus == CResourceControl::PLAYING)
        if (CResourceControl::_ResourceManager._DrawableObjectControl.OnMouseMove(mX, mY))
            return;
}

//==============================================================================
