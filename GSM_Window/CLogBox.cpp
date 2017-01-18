/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CLogBox.h"
#include "../Common/CResourceControl.h"

CLogBox::CTextLog::CTextLog()
{
}

void CLogBox::CTextLog::SetTextLog(string text, sf::SoundBuffer* voice)
{
    SetString(text);
    if (voice){
        _btnVoice._voice = voice;
        AddChildNode(&_btnVoice);
    }
    else{
        _btnVoice._voice = NULL;
        RemoveChildNode(&_btnVoice);
    }
}

bool CLogBox::CTextLog::SetVoiceButton(const Object& json)
{
    return _btnVoice.SetProperty(json);
}

void CLogBox::CTextLog::Clean()
{
    SetString("");
    _btnVoice._voice = NULL;
}

void CLogBox::CTextLog::OnCleanup()
{
    Clean();
    CImageBaseClass::OnCleanup();
}

bool CLogBox::CTextLog::OnLButtonDown(int x, int y)
{
    return _btnVoice.OnLButtonDown(x, y);
}
bool CLogBox::CTextLog::OnMouseMove(int x, int y)
{
    return _btnVoice.OnMouseMove(x, y);
}

bool CLogBox::CTextLog::OnLButtonUp(int x, int y)
{
    return _btnVoice.OnLButtonUp(x, y);
}

//==========================================

CLogBox::CVoiceButton::CVoiceButton()
{
    _voice = NULL;
}

void CLogBox::CVoiceButton::Exec(void* data)
{
    if (_voice)
        CResourceControl::_ResourceManager._SoundControl.PlayVoice(_voice);
}

//==========================================

CLogBox::CLogBox()
{
    _logMax = _visNum = 0;
    AddChildNode(&_scrollbar);
    _scrollbar.SetObjectForCallback(this);
}

CLogBox* CLogBox::Create(const char* filename)
{
    CLogBox* __logBox = new CLogBox();
    if (__logBox->LoadConfigFile(filename)){
        __logBox->SetClassName("LogBox");
        __logBox->SetPath(filename);
        __logBox->SetLayerOrder(165);
        return __logBox;
    }
    
    delete __logBox;
    return NULL;
}

void CLogBox::SetValue(int val)
{
    if (val >= 0){
        float __offset = 0;
        for (size_t i = 0; i < _textLogs.size(); i++){
            if (_logList.size() > i + _scrollbar.GetValue())
                _textLogs[i]->SetTextLog(
                    _logList[i + _scrollbar.GetValue()].first, 
                    _logList[i + _scrollbar.GetValue()].second);
            else
                _textLogs[i]->SetTextLog("", NULL);

            _textLogs[i]->SetPosition(_logOffset.x, _logOffset.y + __offset);
            __offset += _textLogs[i]->GetHeight() + (float)_textLogs[i]->GetCharacterSize() * 0.8f;
        }
    }
}

void CLogBox::Show()
{
    if (!IsShowed()){
        int __index = (int)(_logList.size() - _visNum) < 0 ? 0 : (int)(_logList.size() - _visNum);
        CreateActionOfAlphaToForSelf(100, 255.f, false);
        _scrollbar.SetMaxValue(__index);
        _scrollbar.SetValue(__index);
    }
}

void CLogBox::Hide()
{
    CSequenceOfAction* __seq = new CSequenceOfAction();
    __seq->AddAction(CreateActionOfAlphaTo(100, 0.f, false));
    __seq->AddAction(
        new CClassFuncOfAction<CResourceControl, void>
        (&CResourceControl::_ResourceManager, 
        &CResourceControl::ReturnProcessStatusToPlaying));

    _actionList.AddAction(__seq);
}

void CLogBox::OnCleanup()
{
    CleanLogList();
    CBox::OnCleanup();

    for (vector<CTextLog*>::iterator it = _textLogs.begin(); it != _textLogs.end(); it++){
        delete (*it);
        (*it) = NULL;
    }
    
    _textLogs.clear();
}

//================================
//property:
//* PATH,
//* LOG
//{
//* FONT,
//* OFFSET_X,
//* OFFSET_Y,
//* MAXNUM,
//* VISIBLE_NUM,
//  SIZE
//}
//* PLAY_BUTTON
//{
//* PATH,
//* WIDTH,
//* HEIGHT,
//* MAX_FRAMES,
//* FRAME_RATE,
//}
//JIUGONG
//{
//* WIDTH,
//* HEIGHT,
//* LEFT_WIDTH,
//* RIGHT_WIDTH,
//* TOP_HEIGHT,
//* BOTTOM_HEIGHT,
//}
//SCROLLBAR
//{
//* PATH,
    //JIUGONG
    //{
    //* WIDTH,
    //* HEIGHT,
    //* LEFT_WIDTH,
    //* RIGHT_WIDTH,
    //* TOP_HEIGHT,
    //* BOTTOM_HEIGHT,
    //}
    //* UP_BUTTON
    //{
    //* PATH,
    //* WIDTH,
    //* HEIGHT,
    //* MAX_FRAMES,
    //* FRAME_RATE,
    //}
    //* DOWN_BUTTON
    //{
    //* PATH,
    //* WIDTH,
    //* HEIGHT,
    //* MAX_FRAMES,
    //* FRAME_RATE,
    //}
    //* BAR
    //{
    //* PATH,
    //* WIDTH,
    //* HEIGHT,
    //* MAX_FRAMES,
    //* FRAME_RATE,
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
bool CLogBox::CheckList(const Object& json)
{
    bool __result = CBox::CheckList(json);

    if (json.has<Object>("SCROLLBAR"))
        __result = _scrollbar.CheckList(json.get<Object>("SCROLLBAR")) ? __result : false;

    if (!json.has<Object>("LOG")){
        cout << "can't find value of LOG." << endl;
        __result = false;
    }
    else{
        const Object& __obj = json.get<Object>("LOG");

        if (!__obj.has<String>("FONT")){
            cout << "can't find value of FONT." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("OFFSET_X")){
            cout << "can't find value of OFFSET_X." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("OFFSET_Y")){
            cout << "can't find value of OFFSET_Y." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("MAXNUM")){
            cout << "can't find value of MAXNUM." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("VISIBLE_NUM")){
            cout << "can't find value of VISIBLE_NUM." << endl;
            __result = false;
        }
    }

    if (!json.has<Object>("PLAY_BUTTON")){
        cout << "can't find value of PLAY_BUTTON." << endl;
        __result = false;
    }
    else{
        const Object& __obj = json.get<Object>("PLAY_BUTTON");

        if (!__obj.has<String>("PATH")){
            cout << "can't find value of PATH." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("WIDTH")){
            cout << "can't find value of WIDTH." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("HEIGHT")){
            cout << "can't find value of HEIGHT." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("MAX_FRAMES")){
            cout << "can't find value of MAX_FRAMES." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("FRAME_RATE")){
            cout << "can't find value of FRAME_RATE." << endl;
            __result = false;
        }
    }

    return __result;
}

bool CLogBox::SetProperty(const Object& json, bool isLoad)
{
    if (isLoad){
        const Object& __obj = json.get<Object>("LOG");
        _logMax = __obj.get<Number>("MAXNUM");
        _visNum = __obj.get<Number>("VISIBLE_NUM");
        _logOffset.x = __obj.get<Number>("OFFSET_X");
        _logOffset.y = __obj.get<Number>("OFFSET_Y");

        for (size_t i = 0; i < _visNum; i++){
            _textLogs.push_back(new CTextLog());
            _textLogs.back()->SetFont(__obj.get<String>("FONT"));

            if (!_textLogs.back()->SetVoiceButton(json.get<Object>("PLAY_BUTTON")))
                return false;

            if (__obj.has<Number>("SIZE"))
                _textLogs.back()->SetCharacterSize(__obj.get<Number>("SIZE"));

            AddChildNode(_textLogs.back());
        }

        if (!_scrollbar.SetProperty(json.get<Object>("SCROLLBAR")))
            return false;
    }
    else
        CleanLogList();


    return CBox::SetProperty(json, isLoad);
}

void CLogBox::CleanLogList()
{
    for (size_t i = 0; i < _logList.size(); i++)
        if (_logList[i].second){
            delete _logList[i].second;
            _logList[i].second = NULL;
        }

    _logList.clear();
    
    for (size_t i = 0; i < _textLogs.size(); i++)
        _textLogs[i]->SetTextLog("", NULL);
}

void CLogBox::PositiveOverflow()
{}

void CLogBox::NegativeOverflow()
{
    Hide();
}

void CLogBox::AddLog(string text, const sf::SoundBuffer* voice)
{
    _logList.push_back(pair<string, sf::SoundBuffer*>(text, voice == NULL ? NULL : new sf::SoundBuffer(*voice)));
    if (_logList.size() >= _logMax){
        if (_logList.front().second){
            delete _logList.front().second;
            _logList.front().second = NULL;
        }

        _logList.pop_front();
    }
}

bool CLogBox::OnRButtonDown(int x, int y)
{
    if (IsShowed())
        if (_actionList.GetSize() < 1){
            Hide();
            return true;
        }

    return false;
}