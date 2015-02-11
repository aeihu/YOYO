/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCharacterLayer.h"
#include "../Common/CZlib.h"
#include "../Common/Cio.h"
#include "../Common/CResourceControl.h"

CCharacterLayer::CCharacterLayer(float x, float y):CImageBaseClass(x,y)
{
    _isFaceEnable = false;
    _framesOfMouth._Type = CAnimation::Oscillate;
    _framesOfEyes._Type = CAnimation::Oscillate;
    _currcentFace = _currcentVoice = "";
    _timer = 0;
}

CCharacterLayer* CCharacterLayer::Create(const char* filename)
{    
    CCharacterLayer* __chr = new CCharacterLayer();
    if (__chr->LoadConfigFile(filename)){
        __chr->SetClassName("character");
        __chr->SetPath(filename);
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

bool CCharacterLayer::OnSubLoop()
{
    if (_visible){
        if (_isFaceEnable){
            _framesOfMouth.OnLoop();
            _framesOfEyes.OnLoop();

            if (_currcentVoice != "")
                switch (CResourceControl::_ResourceManager._SoundControl.IsVoiceSilence(_currcentVoice)){
                    case CSoundBank::VOICE_STOPPED:
                        _currcentVoice = "";
                        //_framesOfMouth.TurnOff();
                    break;
                    case CSoundBank::VOICE_SILENCE:
                        //_framesOfMouth.TurnOff();
                    break;
                    case CSoundBank::VOICE_PLAYING:
                        _framesOfMouth.TurnOn(1);
                    break;
                }

            if (_timer < CCommon::_Common.GetTicks()){
                if (_timer != 0)
                    _framesOfEyes.TurnOn(1);
                
                _timer = std::rand() % 20000 + CCommon::_Common.GetTicks();
                //cout << _timer << endl;
            }
        }
    }

    return false;
}

bool CCharacterLayer::CheckList(Object json) 
{
    bool result = true;
    if (!json.has<String>("BODY_PATH")){
        cout << "can't find value of BODY_PATH." << endl;
        result = false;
    }

    if (!json.has<Boolean>("FACE_ENABLE")){
        cout << "can't find value of FACE_ENABLE." << endl;
        return false;
    }

    if (json.get<Boolean>("FACE_ENABLE")){
        if (!json.has<Number>("EYE_OFFSET_X")){
            cout << "can't find value of EYE_OFFSET_X." << endl;
            result = false;
        }
        if (!json.has<Number>("EYE_OFFSET_Y")){
            cout << "can't find value of EYE_OFFSET_Y." << endl;
            result = false;
        }
        if (!json.has<Number>("EYE_WIDTH")){
            cout << "can't find value of EYE_WIDTH." << endl;
            result = false;
        }
        if (!json.has<Number>("EYE_HEIGHT")){
            cout << "can't find value of EYE_HEIGHT." << endl;
            result = false;
        }
        if (!json.has<Number>("EYE_FRAME_RATE")){
            cout << "can't find value of EYE_FRAME_RATE." << endl;
            result = false;
        }

        if (!json.has<Number>("MOUTH_OFFSET_X")){
            cout << "can't find value of MOUTH_OFFSET_X." << endl;
            result = false;
        }
        if (!json.has<Number>("MOUTH_OFFSET_Y")){
            cout << "can't find value of MOUTH_OFFSET_Y." << endl;
            result = false;
        }
        if (!json.has<Number>("MOUTH_WIDTH")){
            cout << "can't find value of MOUTH_WIDTH." << endl;
            result = false;
        }
        if (!json.has<Number>("MOUTH_HEIGHT")){
            cout << "can't find value of MOUTH_HEIGHT." << endl;
            result = false;
        }
        if (!json.has<Number>("MOUTH_FRAME_RATE")){
            cout << "can't find value of MOUTH_FRAME_RATE." << endl;
            result = false;
        }
        
        if (!json.has<Object>("FACE")){
            cout << "can't find value of FACE." << endl;
            result = false;
        }
    }

    return result;
}

bool CCharacterLayer::SetProperty(Object json)
{
    if (!LoadImg(json.get<String>("BODY_PATH").c_str()))
        return false;

    _faceList.reset();

    if (json.get<Boolean>("FACE_ENABLE")){
        _framesOfMouth.SetOffset(json.get<Number>("MOUTH_OFFSET_X"), json.get<Number>("MOUTH_OFFSET_Y"));
        _framesOfMouth.SetSize(json.get<Number>("MOUTH_WIDTH"), json.get<Number>("MOUTH_HEIGHT"));
        _framesOfMouth.SetFrameRate(json.get<Number>("MOUTH_FRAME_RATE"));
        _framesOfMouth.SetDestTexture(&_image);

        _framesOfEyes.SetOffset(json.get<Number>("EYE_OFFSET_X"), json.get<Number>("EYE_OFFSET_Y"));
        _framesOfEyes.SetSize(json.get<Number>("EYE_WIDTH"), json.get<Number>("EYE_HEIGHT"));
        _framesOfEyes.SetFrameRate(json.get<Number>("EYE_FRAME_RATE"));
        _framesOfEyes.SetDestTexture(&_image);
        _faceList = json.get<Object>("FACE");
        _isFaceEnable = true;
    }
    else
        _isFaceEnable= false;

    return true;
}

void CCharacterLayer::SetFace(vector<string> args)
{
    if (args.size() > 0)
        SetFace(args[0]);
}

bool CCharacterLayer::SetFace(string name)
{
    if (_currcentFace == name)
        return true;

    if (_faceList.has<Object>(name)){
        if (!_faceList.get<Object>(name).has<Object>("EYE") || 
            !_faceList.get<Object>(name).has<Object>("MOUTH")){
            cout << "CCharacterLayer::SetFace(): can't find EYE or MOUTH in value face \"" << name << "\"." << endl;
            return false;
        }
        
        Object __eye = _faceList.get<Object>(name).get<Object>("EYE");
        Object __mouth = _faceList.get<Object>(name).get<Object>("MOUTH");
        if (_framesOfEyes.LoadImg(__eye.get<String>("PATH").c_str()) &&
            _framesOfMouth.LoadImg(__mouth.get<String>("PATH").c_str())){

            if (__eye.has<Number>("MAX_FRAMES")) 
                _framesOfEyes.SetMaxFrames(__eye.get<Number>("MAX_FRAMES"));
            else{
                cout << "CCharacterLayer::SetFace(): can't find EYE's MAX_FRAMES in value face \"" << name << "\"." << endl;
                return false;
            }

            /////////////////////////////////////////////////////////////

            if (__mouth.has<Number>("MAX_FRAMES")) 
                _framesOfMouth.SetMaxFrames(__mouth.get<Number>("MAX_FRAMES"));
            else{
                cout << "CCharacterLayer::SetFace(): can't find MOUTH's MAX_FRAMES in value face \"" << name << "\"." << endl;
                return false;
            }
            _currcentFace = name;

            return true;
        }
    }
    
    cout << "CCharacterLayer::SetFace(): can't find face \"" << name << "\"." << endl;
    return false;
}

void CCharacterLayer::OnSaveData(Object& json) const
{
    CImageBaseClass::OnSaveData(json);
    json << "face" << _currcentFace;
}
