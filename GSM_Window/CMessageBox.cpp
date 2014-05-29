/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CMessageBox.h"

using namespace std;

CMessageBox::CMessageBox()
{
    _AnimationControl._MaxFrames = 1;
    _AnimationControl.SetFrameRate(10);
    _AnimationControl.SetCurrentFrame(0);
    _AnimationControl._Type = CAnimation::Oscillate;

    _isPaused = false;
}

CMessageBox* CMessageBox::Create(const char* filename)
{
    CMessageBox* __msgbox = new CMessageBox();
    if (__msgbox->LoadConfigFile(filename)){
        __msgbox->SetLayerOrder(4);
        return __msgbox;
    }
    
    delete __msgbox;
    return NULL;
}

void CMessageBox::SetFont(sf::Font& font)
{
    CTextProcessing::SetFont(font);
    _speakerName.setFont(font);
}

bool CMessageBox::SetProperty(map<string, string>& list)
{
    CTextProcessing::SetRowWidth(atoi(list["MSG_WIDTH"].c_str()));

//=================Init cursor==================================
    if (!_frames.LoadImg(list["CURSOR_PATH"].c_str()))
        return false;

    _frames.SetWidth(atoi(list["CURSOR_WIDTH"].c_str()));
    _frames.SetHeight(atoi(list["CURSOR_HEIGHT"].c_str()));
    _AnimationControl._MaxFrames = atoi(list["CURSOR_MAX_FRAMES"].c_str());
    _AnimationControl.SetFrameRate(atoi(list["CURSOR_FRAME_RATE"].c_str()));

    _speakerNameOffset.x = atof(list["SPEAKER_OFFSET_X"].c_str());
    _speakerNameOffset.y = atof(list["SPEAKER_OFFSET_Y"].c_str());
    _msgOffset.x = atof(list["MSG_OFFSET_X"].c_str());
    _msgOffset.y = atof(list["MSG_OFFSET_Y"].c_str());

    CFont* __fnt = NULL;
    CObject* __obj = list.count("MSG_FONT") < 1 ? 
        CResourceControl::_ResourceManager.GetObject("Font:__main") : 
        CResourceControl::_ResourceManager.GetObject(list["MSG_FONT"]);
   
    if (__obj != NULL){
        __fnt = static_cast<CFont*>(__obj);
        SetFont(__fnt->GetFont());
    }
    else
        return false;

    return CBox::SetProperty(list);
}

bool CMessageBox::CheckList(map<string, string>& list)
{
    bool result = CBox::CheckList(list);

    if (list.count("MSG_OFFSET_X") < 1){
        cout << "can't find value of MSG_OFFSET_X." << endl;
        result = false;
    }

    if (list.count("MSG_OFFSET_Y") < 1){
        cout << "can't find value of MSG_OFFSET_X." << endl;
        result = false;
    }

    if (list.count("MSG_WIDTH") < 1){
        cout << "can't find value of MSG_WIDTH." << endl;
        result = false;
    }

    //if (list.count("MSG_APPEND") < 1){
    //    cout << "can't find value of MSG_APPEND." << endl;
    //    result = false;
    //}

    if (list.count("CURSOR_PATH") < 1){
        cout << "can't find value of CURSOR_PATH." << endl;
        result = false;
    }

    if (list.count("CURSOR_WIDTH") < 1){
        cout << "can't find value of CURSOR_CURSOR_WIDTH." << endl;
        result = false;
    }

    if (list.count("CURSOR_HEIGHT") < 1){
        cout << "can't find value of CURSOR_CURSOR_HEIGHT." << endl;
        result = false;
    }

    if (list.count("CURSOR_FRAME_RATE") < 1){
        cout << "can't find value of CURSOR_FRAME_RATE." << endl;
        result = false;
    }

    if (list.count("CURSOR_MAX_FRAMES") < 1){
        cout << "can't find value of CURSOR_MAX_FRAMES." << endl;
        result = false;
    }

    if (list.count("SPEAKER_OFFSET_X") < 1){
        cout << "can't find value of SPEAKER_OFFSET_X." << endl;
        result = false;
    }

    if (list.count("SPEAKER_OFFSET_Y") < 1){
        cout << "can't find value of SPEAKER_OFFSET_Y." << endl;
        result = false;
    }

    return result;
}

bool CMessageBox::OnLoop()
{
    bool __result = CBox::OnLoop();

    _speakerName.setPosition(CBox::_Coordinate + _speakerNameOffset);

    CTextProcessing::SetPosition(
        CBox::_Coordinate.x + _msgOffset.x, 
        CBox::_Coordinate.y + _msgOffset.y);

    if (IsTextAllShown() && !GetText().empty()){
        _frames.SetCurrentImageFrame(_AnimationControl.GetCurrentFrame());
        _AnimationControl.OnAnimate(CCommon::_Common.GetTicks());

        _frames._Coordinate = 
            CTextProcessing::GetLastCharacterPos()+
            sf::Vector2f(5.0f, 0.0f);

        _frames._Alpha = 255;
    }
    else
        _frames._Alpha = 0;

    _frames.OnLoop();
    CTextProcessing::OnLoop();
    return _isPaused || !IsTextAllShown() || __result;
}

void CMessageBox::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (CBox::_visible){
        CBox::OnRender(Surf_Dest);
        Surf_Dest->draw(_speakerName);
        CTextProcessing::OnRender(Surf_Dest);
        _frames.OnRender(Surf_Dest);
    }
}

void CMessageBox::SetSpeakerName(string name)
{
    CTextFunction::SetString(_speakerName, name.c_str());
}

void CMessageBox::SetText(string msg)
{
    _isPaused = true;
    CTextProcessing::SetText(msg);
}

bool CMessageBox::OnLButtonDown(int x, int y)
{
    if (IsTextAllShown())
        _isPaused = false;
    else
        Skip();

    return true;
}

bool CMessageBox::OnLButtonUp(int x, int y)
{
    return true;
}

bool CMessageBox::OnRButtonDown(int x, int y)
{
    return true;
}

bool CMessageBox::OnRButtonUp(int x, int y)
{
    return true;
}
