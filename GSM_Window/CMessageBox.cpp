/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CMessageBox.h"
#include "../Graphics/CCamera.h"

using namespace std;

CMessageBox::CMessageBox()
{
    _frames.SetMaxFrames(1);
    _frames.SetFrameRate(10);
    _frames.SetCurrentFrame(0);
    _frames._Type = CAnimation::Oscillate;
    AddChildNode(&_frames);
    AddChildNode(&_textProcessor);
    AddChildNode(&_speakerName);
    _frames.SetFlag(FLAG_NONE);
    _isFramesChanged =
    _isUserWantToHideMsg = false;
}

void CMessageBox::ClearText()
{
    _speakerName.SetString("");
    _textProcessor.Clear();
}

CMessageBox* CMessageBox::Create(const char* filename)
{
    CMessageBox* __msgbox = new CMessageBox();
    if (__msgbox->LoadConfigFile(filename)){
        __msgbox->SetClassName("MessageBox");
        __msgbox->SetPath(filename);
        __msgbox->SetLayerOrder(160);
        return __msgbox;
    }
    
    delete __msgbox;
    return NULL;
}

void CMessageBox::SetFont(string font)
{
    _textProcessor.SetFont(font);
    _speakerName.SetFont(font);
}

bool CMessageBox::SetProperty(const Object& json, bool isLoad)
{
    _textProcessor.SetRowWidth(json.get<Number>("MSG_WIDTH"));

//=================Init cursor==================================
    if (isLoad){
        if (!_frames.LoadImgForSetProperty(json, "CURSOR_PATH"))
            return false;

        _frames.SetWidth(json.get<Number>("CURSOR_WIDTH"));
        _frames.SetHeight(json.get<Number>("CURSOR_HEIGHT"));
        _frames.SetMaxFrames(json.get<Number>("CURSOR_MAX_FRAMES"));
        _frames.SetFrameRate(json.get<Number>("CURSOR_FRAME_RATE"));
    }

    _speakerName.SetPosition(json.get<Number>("SPEAKER_OFFSET_X"), json.get<Number>("SPEAKER_OFFSET_Y"));
    _textProcessor.SetPosition(json.get<Number>("MSG_OFFSET_X"), json.get<Number>("MSG_OFFSET_Y"));
    SetFont(json.get<String>("MSG_FONT"));
    
    _textProcessor.SetColor(
        json.get<Number>("CHAR_COLOR_RED"), 
        json.get<Number>("CHAR_COLOR_GREEN"), 
        json.get<Number>("CHAR_COLOR_BLUE"));

    _textProcessor.SetShadowColor(
        json.get<Number>("CHAR_SHADOW_COLOR_RED"), 
        json.get<Number>("CHAR_SHADOW_COLOR_GREEN"), 
        json.get<Number>("CHAR_SHADOW_COLOR_BLUE"));

    _textProcessor.SetShadowPercent(json.get<Number>("CHAR_SHADOW_PERCENT"));

    //_textProcessor.SetPointAlpha(&_alpha);
    return CBox::SetProperty(json);
}

//================================
//property:
//* PATH,
//* MSG_OFFSET_X,
//* MSG_OFFSET_Y,
//* MSG_WIDTH,
//* MSG_FONT,
//* CURSOR_PATH,
//* CURSOR_WIDTH,
//* CURSOR_HEIGHT,
//* CURSOR_FRAME_RATE,
//* CURSOR_MAX_FRAMES,
//* SPEAKER_OFFSET_X,
//* SPEAKER_OFFSET_Y,
//* CHAR_COLOR_RED,
//* CHAR_COLOR_GREEN,
//* CHAR_COLOR_BLUE,
//* CHAR_SHADOW_COLOR_RED,
//* CHAR_SHADOW_COLOR_GREEN,
//* CHAR_SHADOW_COLOR_BLUE,
//* CHAR_SHADOW_PERCENT,
//JIUGONG
//{
//* LEFT_WIDTH,
//* RIGHT_WIDTH,
//* TOP_HEIGHT,
//* BOTTOM_HEIGHT,
//}
//ORDER,
//SCALE,
//SCALE_X,
//SCALE_Y,
//ROTATION,
//ORIGIN_X,
//ORIGIN_Y,
//X,
//Y,
//RED,
//GREEN,
//BLUE,
//ALPHA,
//================================
bool CMessageBox::CheckList(const Object& json)
{
    bool result = CBox::CheckList(json);

    if (!json.has<Number>("MSG_OFFSET_X")){
        cout << "can't find value of MSG_OFFSET_X." << endl;
        result = false;
    }

    if (!json.has<Number>("MSG_OFFSET_Y")){
        cout << "can't find value of MSG_OFFSET_X." << endl;
        result = false;
    }

    if (!json.has<Number>("MSG_WIDTH")){
        cout << "can't find value of MSG_WIDTH." << endl;
        result = false;
    }

    if (!json.has<String>("MSG_FONT")){
        cout << "can't find value of MSG_FONT." << endl;
        result = false;
    }

    if (!json.has<String>("CURSOR_PATH")){
        cout << "can't find value of CURSOR_PATH." << endl;
        result = false;
    }

    if (!json.has<Number>("CURSOR_WIDTH")){
        cout << "can't find value of CURSOR_CURSOR_WIDTH." << endl;
        result = false;
    }

    if (!json.has<Number>("CURSOR_HEIGHT")){
        cout << "can't find value of CURSOR_CURSOR_HEIGHT." << endl;
        result = false;
    }

    if (!json.has<Number>("CURSOR_FRAME_RATE")){
        cout << "can't find value of CURSOR_FRAME_RATE." << endl;
        result = false;
    }

    if (!json.has<Number>("CURSOR_MAX_FRAMES")){
        cout << "can't find value of CURSOR_MAX_FRAMES." << endl;
        result = false;
    }

    if (!json.has<Number>("SPEAKER_OFFSET_X")){
        cout << "can't find value of SPEAKER_OFFSET_X." << endl;
        result = false;
    }

    if (!json.has<Number>("SPEAKER_OFFSET_Y")){
        cout << "can't find value of SPEAKER_OFFSET_Y." << endl;
        result = false;
    }

    if (!json.has<Number>("CHAR_COLOR_RED")){
        cout << "can't find value of CHAR_COLOR_RED." << endl;
        result = false;
    }

    if (!json.has<Number>("CHAR_COLOR_GREEN")){
        cout << "can't find value of CHAR_COLOR_GREEN." << endl;
        result = false;
    }

    if (!json.has<Number>("CHAR_COLOR_BLUE")){
        cout << "can't find value of CHAR_COLOR_BLUE." << endl;
        result = false;
    }

    if (!json.has<Number>("CHAR_SHADOW_COLOR_RED")){
        cout << "can't find value of CHAR_SHADOW_COLOR_RED." << endl;
        result = false;
    }

    if (!json.has<Number>("CHAR_SHADOW_COLOR_GREEN")){
        cout << "can't find value of CHAR_SHADOW_COLOR_GREEN." << endl;
        result = false;
    }

    if (!json.has<Number>("CHAR_SHADOW_COLOR_BLUE")){
        cout << "can't find value of CHAR_SHADOW_COLOR_BLUE." << endl;
        result = false;
    }

    if (!json.has<Number>("CHAR_SHADOW_PERCENT")){
        cout << "can't find value of CHAR_SHADOW_PERCENT." << endl;
        result = false;
    }

    return result;
}

void CMessageBox::OnLoop()
{
    CBox::OnLoop();

    if (_textProcessor.GetStatus() == CTextProcessing::FINISH
        && !_textProcessor.GetText().empty()){
        if (!_isFramesChanged){
            _frames.SetPosition(_textProcessor.GetLastCharacterPos().x,
                _textProcessor.GetLastCharacterPos().y);

            _frames.SetAlpha(255);
            _frames.TurnOn(true);
            _isFramesChanged = true;
        }
    }
    else{
        _frames.SetAlpha(0);
        _frames.TurnOff();
        _isFramesChanged = false;
    }
}

void CMessageBox::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (!_isUserWantToHideMsg)
        CBox::OnRender(Surf_Dest);
}

void CMessageBox::SetSpeakerName(string name)
{
    _speakerName.SetString(name);
}

void CMessageBox::SetText(string msg)
{
    _textProcessor.SetString(msg);
}
string CMessageBox::GetText()
{
    return _textProcessor.GetText();
}

string CMessageBox::GetSpeakerName()
{
    return _speakerName.GetString();
}

void CMessageBox::SwitchForShowAndHide()
{
    _isUserWantToHideMsg = !_isUserWantToHideMsg;
}

bool CMessageBox::ConfirmForText()
{
    switch (_textProcessor.GetStatus()){
        case CTextProcessing::RUNNING:
            _textProcessor.Skip();
            return true;
        case CTextProcessing::FINISH:
            _textProcessor.Confirm();
            return false; // ***临时处理 后面需要添加事件响应的状态机
        default:
            return false;
    }
}

bool CMessageBox::OnLButtonDown(int x, int y)
{
    if (_isUserWantToHideMsg){
        _isUserWantToHideMsg = false;
        return true;
    }

    return ConfirmForText();
}

bool CMessageBox::OnRButtonUp(int x, int y)
{
    SwitchForShowAndHide();
    return false;
}

CTextProcessing::EStatus CMessageBox::GetStatus() const
{
    return _textProcessor.GetStatus();
}