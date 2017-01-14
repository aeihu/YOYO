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
    switch (_processStatus){
        case CResourceControl::PLAYING:
            if (_DrawableObjectControl.OnLButtonDown(mX, mY))
                return true;

            if (GetMsgboxPauseStatus()){
                OffMsgboxPause();

                CMessageBox* __msgbox = static_cast<CMessageBox*>(_DrawableObjectControl.GetDrawableObject(_CurrentMsg._FromMsgbox));
                if (__msgbox){
                    string ss = _CurrentMsg._Name + ":\n" + __msgbox->GetText();
                    _logbox->AddLog(
                        ss,
                        _SoundControl.GetVoice(_CurrentMsg._VoiceName));
                }

                _LuaControl.ResumeLuaThread();
                return true;
            }
            break;
        case CResourceControl::PLAYING_LOGBOX:
            break;
        case CResourceControl::PLAYING_SAVEBOX:
            break;
        case CResourceControl::PLAYING_LOADBOX:
            break;
        default:
            break;
    }

    return false;
}

bool CResourceControl::OnLButtonUp(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnLButtonUp(mX, mY);

    return false;
}

bool CResourceControl::OnRButtonDown(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnRButtonDown(mX, mY);
        
    return false;
}

bool CResourceControl::OnRButtonUp(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnRButtonUp(mX, mY);

    return false;
}

bool CResourceControl::OnMButtonDown(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnMButtonDown(mX, mY);

    return false;
}

bool CResourceControl::OnMButtonUp(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnMButtonUp(mX, mY);

    return false;
}
//------------------------------------------------------------------------------
bool CResourceControl::OnMouseMove(int mX, int mY)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnMouseMove(mX, mY);

    return false;
}

bool CResourceControl::OnMouseWheel(int delta)
{
    switch (_processStatus){
        case CResourceControl::PLAYING:
            if (delta > 0){
                _logbox->Show();
                _processStatus = CResourceControl::PLAYING_LOGBOX;
                return true;
            }
            break;
        case CResourceControl::PLAYING_LOGBOX:
            return _logbox->OnMouseWheel(delta);
            break;
        case CResourceControl::PLAYING_SAVEBOX:
            break;
        case CResourceControl::PLAYING_LOADBOX:
            break;
        default:
            return _DrawableObjectControl.OnMouseWheel(delta);
            break;
    }

    return false;
}

bool CResourceControl::OnKeyDown(sf::Event::KeyEvent key)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnKeyDown(key);

    return false;
}

bool CResourceControl::OnKeyUp(sf::Event::KeyEvent key)
{
    if (_processStatus == CResourceControl::PLAYING)
        return _DrawableObjectControl.OnKeyUp(key);

    return false;
}

//==============================================================================
