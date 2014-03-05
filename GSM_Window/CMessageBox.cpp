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

bool CMessageBox::Sub_OnLoad()
{
    if (!CTextProcessing::OnInit(
        CBox::_sprite.getGlobalBounds().width - atof(_parameterList["MSG_OFFSET_X"].c_str()) * 2))
        return false;

//=================Init cursor==================================
    if (!CSequenceOfFrames::LoadImg(_parameterList["CURSOR_PATH"].c_str()))
        return false;

    SetWidth(atoi(_parameterList["CURSOR_WIDTH"].c_str()));
    SetHeight(atoi(_parameterList["CURSOR_HEIGHT"].c_str()));
    _AnimationControl._MaxFrames = atoi(_parameterList["CURSOR_MAX_FRAMES"].c_str());
    _AnimationControl.SetFrameRate(atoi(_parameterList["CURSOR_FRAME_RATE"].c_str()));
    return true;
}

bool CMessageBox::Sub_CheckList(map<string, string> list)
{
    bool result = true;

    if (list.count("MSG_OFFSET_X") < 1){
        cout << "can't find value of MSG_OFFSET_X." << endl;
        result = false;
    }

    if (list.count("MSG_OFFSET_Y") < 1){
        cout << "can't find value of MSG_OFFSET_X." << endl;
        result = false;
    }

    if (list.count("MSG_APPEND") < 1){
        cout << "can't find value of MSG_APPEND." << endl;
        result = false;
    }

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

    return result;
}

bool CMessageBox::OnLoop()
{
    bool __result = CBox::OnLoop();
//    _speakerName.setPosition(CCommon::common.MSGBOX_SPEAKER_OFFSET_X, CCommon::common.MSGBOX_SPEAKER_OFFSET_Y);
    CTextProcessing::SetPosition(
        CBox::_Coordinate.x + atof(_parameterList["MSG_OFFSET_X"].c_str()), 
        CBox::_Coordinate.y + atof(_parameterList["MSG_OFFSET_Y"].c_str()));

    if (IsTextAllShown() && !GetText().empty()){
        SetCurrentImageFrame(_AnimationControl.GetCurrentFrame());
        _AnimationControl.OnAnimate(CCommon::common.GetTicks());

        CSequenceOfFrames::_Coordinate = 
            CTextProcessing::GetPosition()+
            CTextProcessing::GetCharacterPos(GetText().length()-1)+
            sf::Vector2f(2.0f, 5.0f);
        //CSequenceOfFrames::_Coordinate.x = CTextProcessing::GetPosition()
        //CSequenceOfFrames::_Coordinate.y = 
        CSequenceOfFrames::_Alpha = 255;
    }
    else
        CSequenceOfFrames::_Alpha = 0;

    CSequenceOfFrames::OnLoop();
    CTextProcessing::OnLoop();
    return _isPaused || !IsTextAllShown() || __result;
}

void CMessageBox::OnRender(sf::RenderWindow* Surf_Dest)
{
    CBox::OnRender(Surf_Dest);
    Surf_Dest->draw(_speakerName);
    CTextProcessing::OnRender(Surf_Dest);
    CSequenceOfFrames::OnRender(Surf_Dest);
}

void CMessageBox::SetSpeakerName(string name)
{
    _speakerName.setString(name.c_str());
}

void CMessageBox::SetText(string msg)
{
    _isPaused = true;
    CTextProcessing::SetText(msg, atoi(_parameterList["MSG_APPEND"].c_str()));
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
