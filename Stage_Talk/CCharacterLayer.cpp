/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCharacterLayer.h"
#include "../Common/CZlib.h"
#include "../Common/Cio.h"

CCharacterLayer::CCharacterLayer(float x, float y):CImageBaseClass(x,y)
{
    _isFaceEnable = false;
    _framesOfMouth._Type = CAnimation::Oscillate;
    _framesOfEyes._Type = CAnimation::Oscillate;
    _currcentVoice = "";
    _timer = 0;
}

CCharacterLayer* CCharacterLayer::Create(const char* filename)
{    
    CCharacterLayer* __chr = new CCharacterLayer();
    if (__chr->LoadConfigFile(filename)){
        __chr->SetLayerOrder(2);
        return __chr;
    }
    
    delete __chr;
    return NULL;
}

void CCharacterLayer::SetVoice(string name)
{
    _currcentVoice = name;
}

bool CCharacterLayer::OnLoop()
{
    bool __result = CImageBaseClass::OnLoop();

    if (_visible){
        if (_isFaceEnable){
            _framesOfMouth.OnLoop();
            _framesOfEyes.OnLoop();

            if (_currcentVoice != "")
                switch (CSoundBank::_SoundControl.IsVoiceSilence(_currcentVoice)){
                    case CSoundBank::VOICE_STOPPED:
                        _currcentVoice = "";
                        _framesOfMouth.TurnOff();
                    break;
                    case CSoundBank::VOICE_SILENCE:
                        _framesOfMouth.TurnOff();
                    break;
                    case CSoundBank::VOICE_PLAYING:
                        _framesOfMouth.TurnOn();
                    break;
                }

            if (_timer < CCommon::_Common.GetTicks()){
                if (_timer != 0)
                    _framesOfEyes.TurnOn(1);
                
                _timer = std::rand() % 20000 + CCommon::_Common.GetTicks();
                cout << _timer << endl;
            }
        }
    }

    return __result;
}

bool CCharacterLayer::CheckList(map<string, string>& list) 
{
    bool result = true;
    if (list.count("BODY_PATH") < 1){
        cout << "can't find value of BODY_PATH." << endl;
        result = false;
    }

    if (list.count("FACE_ENABLE") < 1){
        cout << "can't find value of FACE_ENABLE." << endl;
        return false;
    }

    if (list["FACE_ENABLE"] != "0"){
        if (list.count("MOUTH_OFFSET_X") < 1){
            cout << "can't find value of MOUTH_OFFSET_X." << endl;
            result = false;
        }
        
        if (list.count("MOUTH_OFFSET_Y") < 1){
            cout << "can't find value of MOUTH_OFFSET_Y." << endl;
            result = false;
        }

        if (list.count("MOUTH_WIDTH") < 1){
            cout << "can't find value of MOUTH_WIDTH." << endl;
            result = false;
        }
        
        if (list.count("MOUTH_HEIGHT") < 1){
            cout << "can't find value of MOUTH_HEIGHT." << endl;
            result = false;
        }
        
        if (list.count("MOUTH_MAX_FRAMES") < 1){
            cout << "can't find value of MOUTH_MAX_FRAMES." << endl;
            result = false;
        }
        
        if (list.count("MOUTH_FRAME_RATE") < 1){
            cout << "can't find value of MOUTH_FRAME_RATE." << endl;
            result = false;
        }
        
        if (list.count("EYES_OFFSET_X") < 1){
            cout << "can't find value of EYES_OFFSET_X." << endl;
            result = false;
        }
        
        if (list.count("EYES_OFFSET_Y") < 1){
            cout << "can't find value of EYES_OFFSET_Y." << endl;
            result = false;
        }

        if (list.count("EYES_WIDTH") < 1){
            cout << "can't find value of EYES_WIDTH." << endl;
            result = false;
        }
        
        if (list.count("EYES_HEIGHT") < 1){
            cout << "can't find value of EYES_HEIGHT." << endl;
            result = false;
        }
        
        if (list.count("EYES_MAX_FRAMES") < 1){
            cout << "can't find value of EYES_MAX_FRAMES." << endl;
            result = false;
        }
        
        if (list.count("EYES_FRAME_RATE") < 1){
            cout << "can't find value of EYES_FRAME_RATE." << endl;
            result = false;
        }
    }

    return result;
}

bool CCharacterLayer::SetProperty(map<string, string>& list)
{
    if (!LoadImg(list["BODY_PATH"].c_str()))
        return false;

    _faceList.clear();

    if (list["FACE_ENABLE"] != "0"){
        _isFaceEnable = true;
        _framesOfMouth.SetOffset(atoi(list["MOUTH_OFFSET_X"].c_str()), atoi(list["MOUTH_OFFSET_Y"].c_str()));
        _framesOfMouth.SetMaxFrames(atoi(list["MOUTH_MAX_FRAMES"].c_str()));
        _framesOfMouth.SetFrameRate(atoi(list["MOUTH_FRAME_RATE"].c_str()));

        _framesOfMouth.SetSize(atoi(list["MOUTH_WIDTH"].c_str()), atoi(list["MOUTH_HEIGHT"].c_str()));
        _framesOfMouth.SetDestTexture(&_image);

        _framesOfEyes.SetOffset(atoi(list["EYES_OFFSET_X"].c_str()), atoi(list["EYES_OFFSET_Y"].c_str()));
        _framesOfEyes.SetMaxFrames(atoi(list["EYES_MAX_FRAMES"].c_str()));
        _framesOfEyes.SetFrameRate(atoi(list["EYES_FRAME_RATE"].c_str()));

        _framesOfEyes.SetSize(atoi(list["EYES_WIDTH"].c_str()), atoi(list["EYES_HEIGHT"].c_str()));
        _framesOfEyes.SetDestTexture(&_image);

        list.erase("BODY_PATH");
        list.erase("MOUTH_OFFSET_X");
        list.erase("MOUTH_OFFSET_Y");
        list.erase("MOUTH_MAX_FRAMES");
        list.erase("MOUTH_FRAME_RATE");
        list.erase("MOUTH_WIDTH");
        list.erase("MOUTH_HEIGHT");
        list.erase("FACE_ENABLE");

        list.erase("EYES_OFFSET_X");
        list.erase("EYES_OFFSET_Y");
        list.erase("EYES_MAX_FRAMES");
        list.erase("EYES_FRAME_RATE");
        list.erase("EYES_WIDTH");
        list.erase("EYES_HEIGHT");

        map<string, string>::iterator it;
        for (it = list.begin(); it!=list.end(); it++){
            std::list<string> __list = Cio::SplitString("\""+(*it).second+"\"", "|");

            if (__list.size() == 2){
                _faceList.push_back(
                    make_pair((*it).first, 
                    make_pair(__list.front(), __list.back())));
            }
            else
                cout << "CCharacterLayer::SetProperty(): face \"" << (*it).first << "\" failed to add." << endl;
        }
    }
    else
        _isFaceEnable= false;

    return true;
}

bool CCharacterLayer::SetFace(string name)
{
    list<pair<string, pair<string, string> > >::iterator it;
    for (it = _faceList.begin(); it!=_faceList.end(); it++){
        if ((*it).first == name){
            _framesOfEyes.LoadImg((*it).second.first.c_str());
            _framesOfMouth.LoadImg((*it).second.second.c_str());
            return true;
        }
    }
    
    cout << "CCharacterLayer::SetFace(): can't find face \"" << name << "\"." << endl;
    return false;
}
