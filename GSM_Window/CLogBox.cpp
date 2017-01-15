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
        _childrenList.clear();
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
    _logRowHeight = _logMax = _visNum = 0;
    //AddChildNode(&_scrollbar);
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

bool CLogBox::Down()
{
    if (_logList.size() > _visNum){
        if ((int)(_logList.size() - _visNum) > _index){
            _index++;
            RefTextLogs();
            return true;
        }
    }
    return false;
}

bool CLogBox::Up()
{
    if (_logList.size() > _visNum){
        if (_index > 0){
            _index--;
            RefTextLogs();
            return true;
        }
    }
    return false;
}

void CLogBox::Show()
{
    if (!IsShowed()){
        _index = (int)(_logList.size() - _visNum) < 0 ? 0 : (int)(_logList.size() - _visNum);
        RefTextLogs();
        CreateActionOfAlphaToForSelf(300, 255.f, false);
    }
}

void CLogBox::Hide()
{
    CSequenceOfAction* __seq = new CSequenceOfAction();
    __seq->AddAction(CreateActionOfAlphaTo(300, 0.f, false));
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

void CLogBox::RefTextLogs()
{
    for (size_t i = 0; i < _textLogs.size(); i++){
        if (_logList.size() > i + _index)
            _textLogs[i]->SetTextLog(_logList[i + _index].first, _logList[i + _index].second);
        else
            _textLogs[i]->SetTextLog("", NULL);
    }
}

//================================
//property:
//* PATH,
//* SCROLLBAR_OFFSET_X
//* SCROLLBAR_OFFSET_Y
//* LOG
//{
//* FONT,
//* OFFSET_X,
//* OFFSET_Y,
//* MAXNUM,
//* ROW_HEIGHT,
//* VISIBLE_NUM,
//  SIZE
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
//* PLAY_BUTTON
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

    //if (!_scrollbar.CheckList(json))
    //    __result = false;

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

        if (!__obj.has<Number>("ROW_HEIGHT")){
            cout << "can't find value of ROW_HEIGHT." << endl;
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

    if (!json.has<Number>("SCROLLBAR_OFFSET_X")){
        cout << "can't find value of SCROLLBAR_OFFSET_X." << endl;
        __result = false;
    }

    if (!json.has<Number>("SCROLLBAR_OFFSET_Y")){
        cout << "can't find value of SCROLLBAR_OFFSET_Y." << endl;
        __result = false;
    }

    return __result;
}

bool CLogBox::SetProperty(const Object& json, bool isLoad)
{
    if (isLoad){
        const Object& __obj = json.get<Object>("LOG");
        _logMax = __obj.get<Number>("MAXNUM");
        _visNum = __obj.get<Number>("VISIBLE_NUM");
        _logRowHeight = __obj.get<Number>("ROW_HEIGHT");
        _logOffset.x = __obj.get<Number>("OFFSET_X");
        _logOffset.y = __obj.get<Number>("OFFSET_Y");

        for (size_t i = 0; i < _visNum; i++){
            _textLogs.push_back(new CTextLog());
            _textLogs.back()->SetFont(__obj.get<String>("FONT"));
            _textLogs.back()->SetPosition(_logOffset.x, _logOffset.y + _logRowHeight * i);
            _textLogs.back()->SetVoiceButton(json.get<Object>("PLAY_BUTTON"));

            if (__obj.has<Number>("SIZE"))
                _textLogs.back()->SetCharacterSize(__obj.get<Number>("SIZE"));

            AddChildNode(_textLogs.back());
            _childrenList.size();
        }
    }
    else
        CleanLogList();

    //_scrollbar.SetOffset(json.get<Number>("SCROLLBAR_OFFSET_X"), json.get<Number>("SCROLLBAR_OFFSET_Y"));

    //if (!_scrollbar.SetProperty(json))
    //    return false;

    return CBox::SetProperty(json);
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

bool CLogBox::OnMouseMove(int x, int y)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (vector<CTextLog*>::iterator it = _textLogs.begin(); it != _textLogs.end(); it++)
                if ((*it)->OnMouseMove(x, y))
                    return true;
        }
    }
    
    return false;
}

bool CLogBox::OnMouseWheel(int delta)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            if (delta > 0){
                Up();
            }
            else{
                if (!Down()){
                    Hide();
                }
            }
            return true;
        }
    }

    return false;
}

bool CLogBox::OnLButtonDown(int x, int y)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (vector<CTextLog*>::iterator it = _textLogs.begin(); it != _textLogs.end(); it++)
                if ((*it)->OnLButtonDown(x, y))
                    return true;
        }
    }

    return false;
}

bool CLogBox::OnLButtonUp(int x, int y)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (vector<CTextLog*>::iterator it = _textLogs.begin(); it != _textLogs.end(); it++)
                if ((*it)->OnLButtonUp(x, y))
                    return true;
        }
    }

    return false;
}
