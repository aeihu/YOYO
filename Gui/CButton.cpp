/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CButton.h"
//#include "CSoundBank.h"

CButton::CButton(float x, float y, int w, int h, int maxframes, int framerate):CSequenceOfFrames(x,y,0,0,w,h)
{
    _AnimationControl._MaxFrames = maxframes;
    _AnimationControl.SetFrameRate(framerate);
    _AnimationControl.SetCurrentFrame(0);
    _AnimationControl._Type = CAnimation::Backward;
    _isMouseDown = false;
    _isMouseOver = false;
    _seNameOfMouseOver = CCommon::common.MOUSEOVER_SE;
    _seNameOfMouseDown = CCommon::common.MOUSEDOWN_SE;
    _Coordinate.x=x;
    _Coordinate.y=y;
}

bool CButton::OnLButtonDown(int x, int y)
{
    if (IsStandby())
        if (_isMouseOver)
        {
            _isMouseDown = true;
            SetCurrentImageFrame(_AnimationControl._MaxFrames);
            _AnimationControl.SetCurrentFrame(_AnimationControl._MaxFrames-1);
            //CSoundBank::_SoundControl.PlaySE(SEName_MouseDown);
            return true;
        }

    return false;
}

bool CButton::OnLButtonUp(int x, int y)
{
    if (IsStandby())
        if(_isMouseOver){
            _isMouseDown = false;
            SetCurrentImageFrame(_AnimationControl._MaxFrames-1);
            CParser::parser.InsertCmdList(_CmdList);
            return true;
        }
        else{
            SetCurrentImageFrame(_AnimationControl.GetCurrentFrame());
        }

    return false;
}
//
bool CButton::Subclass_Loop()
{
    if (!_isMouseDown){
        SetCurrentImageFrame(_AnimationControl.GetCurrentFrame());
        _AnimationControl.OnAnimate(CCommon::common.GetTicks());
    }

    return false;
}

void CButton::OnMouseMove(int x, int y)
{
    if (IsStandby())
        if(( x > GetPosition().x ) && ( x < GetPosition().x + GetWidth()) && 
            ( y > GetPosition().y ) && ( y < GetPosition().y + GetHeight())){
            if (!_isMouseOver)
            _isMouseOver = true;
            _AnimationControl._Type = CAnimation::Forward;
        }
        else{
            _isMouseOver = false;
            _isMouseDown = false;
            _AnimationControl._Type = CAnimation::Backward;
        }
}

bool CButton::LoadButton(const char* FileName)
{
    list<string> __expressions = Cio::LoadTxtFile(FileName, "\r\n");
    map<string, string> __valueList;

    for (list<string>::iterator it=__expressions.begin();
        it!=__expressions.end(); it++){
        string __paraName = "";
        string __paraValue = "";
        if(Cio::AnalyticExpression((*it), __paraName, __paraValue))
            __valueList[__paraName] = __paraValue;
    }

    if (!CheckList(__valueList))
        return false;

    if (!SetProperty(__valueList))
        return false;

    return true;
}

bool CButton::CheckList(map<string, string> list) 
{
    bool result = true;
    if (list.count("TILESET_PATH") < 1){
        cout << "can't find value of TILESET_PATH." << endl;
        result = false;
    }

    if (list.count("SCRIPT_PATH") < 1){
        cout << "can't find value of SCRIPT_PATH." << endl;
        result = false;
    }
    
    if (list.count("SCRIPT_SECTION") < 1){
        cout << "can't find value of SCRIPT_SECTION." << endl;
        result = false;
    }

    if (list.count("WIDTH") < 1){
        cout << "can't find value of WIDTH." << endl;
        result = false;
    }

    if (list.count("HEIGHT") < 1){
        cout << "can't find value of HEIGHT." << endl;
        result = false;
    }

    if (list.count("MAX_FRAMES") < 1){
        cout << "can't find value of MAX_FRAMES." << endl;
        result = false;
    }

    if (list.count("FRAME_RATE") < 1){
        cout << "can't find value of FRAME_RATE." << endl;
        result = false;
    }
    return result;
}

bool CButton::SetProperty(map<string, string> list)
{    

    SetWidth(atoi(list["WIDTH"].c_str()));
    SetHeight(atoi(list["HEIGHT"].c_str()));
    if (!LoadImg(list["TILESET_PATH"].c_str()))
        return false;

    if (!CParser::parser.LoadScript(list["SCRIPT_PATH"].c_str(), 
        list["SCRIPT_SECTION"].c_str(), _CmdList))
        return false;

    _AnimationControl._MaxFrames = atoi(list["MAX_FRAMES"].c_str());
    _AnimationControl.SetFrameRate(atoi(list["FRAME_RATE"].c_str()));
    if (list.count("X") > 0){
        _Coordinate.x=atof(list["X"].c_str());
    }

    if (list.count("Y") > 0){
        _Coordinate.y=atof(list["Y"].c_str());
    }

    return true;
}
