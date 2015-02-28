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
    //_isFaceEnable = false;
    _framesOfMouth._Type = CAnimation::Oscillate;
    _framesOfEyes._Type = CAnimation::Oscillate;
    _currcentBody = _currcentMouth = _currcentEyes = _currcentVoice = "";
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

void CCharacterLayer::Flip()
{
    _sprite.setTextureRect(
        sf::IntRect(
            _flipX ? _sprite.getLocalBounds().width : 0,
            _flipY ? _sprite.getLocalBounds().height : 0,
            _flipX ? -_sprite.getLocalBounds().width : _sprite.getLocalBounds().width,
            _flipY ? -_sprite.getLocalBounds().height : _sprite.getLocalBounds().height)
    );
}

void CCharacterLayer::FlipX()
{
    _flipX = !_flipX;
    Flip();
}

void CCharacterLayer::FlipY()
{
    _flipY = !_flipY;
    Flip();
}
        
const sf::Vector2f& CCharacterLayer::GetGlobalPosition() const
{
    return _sprite.getPosition();
}

void CCharacterLayer::SetVoice(string name)
{
    _currcentVoice = name;
}

void CCharacterLayer::OnLoop()
{
    _visible = _alpha > 0 ? true : false;

    if (_sprite.getColor().a != _alpha)
        _sprite.setColor(sf::Color(255,255,255,_alpha));

    if (_visible){
        if (_coordinate != _sprite.getPosition())
            _sprite.setPosition(_coordinate);
        
        if (_origin != _sprite.getOrigin())
            _sprite.setOrigin(_origin);
        
        if (_scale != _sprite.getScale())
            _sprite.setScale(_scale);

        if (_rotation != _sprite.getRotation())
            _sprite.setRotation(_rotation);

        //if (_isFaceEnable){
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
        //}
    }
}
         
void CCharacterLayer::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_visible)
        Surf_Dest->draw(_sprite);
}

bool CCharacterLayer::CheckList(Object json) 
{
    bool result = true;
    string __name;
    if (!json.has<Array>("BODY")){
        cout << "can't find value of BODY." << endl;
        result = false;
    }
    else{
        if (json.get<Array>("BODY").size() < 1){
            cout << "value of BODY must be has one." << endl;
            result = false;
        }

        Object __body;
        for (size_t i=0; i<json.get<Array>("BODY").size(); i++){
            __body = json.get<Array>("BODY").get<Object>(i);
            if (!__body.has<String>("BODY_PATH")){
                cout << "can't find value of BODY_PATH." << endl;
                result = false;
            }

            __name = CTextFunction::GetNameInFilename(__body.get<String>("BODY_PATH"));
            if (!__body.has<Number>("EYE_OFFSET_X")){
                cout << "BODY '" << __name << "' can't find value of EYE_OFFSET_X." << endl;
                result = false;
            }
            if (!__body.has<Number>("EYE_OFFSET_Y")){
                cout << "BODY '" << __name << "' can't find value of EYE_OFFSET_Y." << endl;
                result = false;
            }
            if (!__body.has<Number>("EYE_WIDTH")){
                cout << "BODY '" << __name << "' can't find value of EYE_WIDTH." << endl;
                result = false;
            }
            if (!__body.has<Number>("EYE_HEIGHT")){
                cout << "BODY '" << __name << "' can't find value of EYE_HEIGHT." << endl;
                result = false;
            }
            if (!__body.has<Number>("EYE_FRAME_RATE")){
                cout << "BODY '" << __name << "' can't find value of EYE_FRAME_RATE." << endl;
                result = false;
            }

            if (!__body.has<Number>("MOUTH_OFFSET_X")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_OFFSET_X." << endl;
                result = false;
            }
            if (!__body.has<Number>("MOUTH_OFFSET_Y")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_OFFSET_Y." << endl;
                result = false;
            }
            if (!__body.has<Number>("MOUTH_WIDTH")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_WIDTH." << endl;
                result = false;
            }
            if (!__body.has<Number>("MOUTH_HEIGHT")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_HEIGHT." << endl;
                result = false;
            }
            if (!__body.has<Number>("MOUTH_FRAME_RATE")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_FRAME_RATE." << endl;
                result = false;
            }    
        }
    }

    if (!json.has<Array>("EYE")){
        cout << "can't find value of EYE." << endl;
        result = false;
    }
    else{
        for (size_t i=0; i<json.get<Array>("EYE").size(); i++){
            if (!json.get<Array>("EYE").has<Object>(i)){
                result = false;
                continue;
            }

            __name = CTextFunction::GetNameInFilename(json.get<Array>("EYE").get<Object>(i).get<String>("PATH"));

            if (!json.get<Array>("EYE").get<Object>(i).has<String>("PATH")){
                cout << "EYE '" << __name << "' can't find value of PATH." << endl;
                result = false;
            }

            if (!json.get<Array>("EYE").get<Object>(i).has<Number>("MAX_FRAMES")){
                cout << "EYE '" << __name << "' can't find value of MAX_FRAMES." << endl;
                result = false;
            }
        }
    }

    if (!json.has<Array>("MOUTH")){
        cout << "can't find value of MOUTH." << endl;
        result = false;
    }
    else{
        for (size_t i=0; i<json.get<Array>("MOUTH").size(); i++){
            if (!json.get<Array>("MOUTH").has<Object>(i)){
                result = false;
                continue;
            }

            __name = CTextFunction::GetNameInFilename(json.get<Array>("MOUTH").get<Object>(i).get<String>("PATH"));

            if (!json.get<Array>("MOUTH").get<Object>(i).has<String>("PATH")){
                cout << "MOUTH '" << __name << "' can't find value of PATH." << endl;
                result = false;
            }

            if (!json.get<Array>("MOUTH").get<Object>(i).has<Number>("MAX_FRAMES")){
                cout << "MOUTH '" << __name << "' can't find value of MAX_FRAMES." << endl;
                result = false;
            }
        }
    }

    return result;
}

bool CCharacterLayer::SetProperty(Object json)
{
    Array __bodyList = json.get<Array>("BODY");
    Object __body;
    string __name;

    for (size_t i=0; i<__bodyList.size(); i++){
        if (!__bodyList.has<Object>(i))
            return false;

        __body = __bodyList.get<Object>(i);
        __name = CTextFunction::GetNameInFilename(__body.get<String>("BODY_PATH"));

        if (_textureList.count(__name) > 0){
            cout << "CCharacterLayer::SetProperty(): body texture " 
                " \""<< __name << "\" has existed." <<endl;
                
            return false;
        }
        else{
            _textureList[__name] = sf::Texture();

            if (!CSurface::OnLoad(__body.get<String>("BODY_PATH").c_str(), _textureList[__name]))
                return false;

            if (i == 0){
                _currcentBody = __name;
                _sprite.setTexture(_textureList[__name]);
                
                _framesOfMouth.SetOffset(__body.get<Number>("MOUTH_OFFSET_X"), __body.get<Number>("MOUTH_OFFSET_Y"));
                _framesOfMouth.SetSize(__body.get<Number>("MOUTH_WIDTH"), __body.get<Number>("MOUTH_HEIGHT"));
                _framesOfMouth.SetFrameRate(__body.get<Number>("MOUTH_FRAME_RATE"));
                _framesOfMouth.SetDestTexture(&_textureList[__name]);

                _framesOfEyes.SetOffset(__body.get<Number>("EYE_OFFSET_X"), __body.get<Number>("EYE_OFFSET_Y"));
                _framesOfEyes.SetSize(__body.get<Number>("EYE_WIDTH"), __body.get<Number>("EYE_HEIGHT"));
                _framesOfEyes.SetFrameRate(__body.get<Number>("EYE_FRAME_RATE"));
                _framesOfEyes.SetDestTexture(&_textureList[__name]);
            }
        }
    }
    
    Array __eye = json.get<Array>("EYE");
    for (size_t i=0; i<__eye.size(); i++){
        __name = CTextFunction::GetNameInFilename(__eye.get<Object>(i).get<String>("PATH"));

        if (_eyeList.count(__name) > 0){
            cout << "CCharacterLayer::SetProperty(): eye texture " 
                " \""<< __name << "\" has existed." <<endl;
                
            return false;
        }
        else{
            _eyeList[__name] = make_pair(sf::Image(), __eye.get<Object>(i).get<Number>("MAX_FRAMES"));
            if (!CSurface::OnLoad(__eye.get<Object>(i).get<String>("PATH").c_str(), _eyeList[__name].first))
                return false;
        }
    }

    Array __mouth = json.get<Array>("MOUTH");
    for (size_t i=0; i<__mouth.size(); i++){
        __name = CTextFunction::GetNameInFilename(__mouth.get<Object>(i).get<String>("PATH"));

        if (_mouthList.count(__name) > 0){
            cout << "CCharacterLayer::SetProperty(): mouth texture " 
                " \""<< __name << "\" has existed." <<endl;
                
            return false;
        }
        else{
            _mouthList[__name] = make_pair(sf::Image(), __mouth.get<Object>(i).get<Number>("MAX_FRAMES"));
            if (!CSurface::OnLoad(__mouth.get<Object>(i).get<String>("PATH").c_str(), _mouthList[__name].first))
                return false;
        }
    }

    return true;
}

void CCharacterLayer::SetPose(vector<string> args)
{
    if (args.size() > 1)
        SetPose(args[0], args[1], args[2]);
}

bool CCharacterLayer::SetPose(string body, string eye, string mouth)
{
    if (_currcentBody != body && !body.empty() && _textureList.count(body) > 0){
        _sprite.setTexture(_textureList[body]);
        _currcentBody = body;
        _framesOfEyes.SetDestTexture(&_textureList[body]);
        _framesOfMouth.SetDestTexture(&_textureList[body]);
    }
    else if(_textureList.count(body) < 1 && !body.empty()){
        cout << "CCharacterLayer::SetPose(): can't find BODY \"" << body << "\"." << endl;
        return false;
    }

    if (_currcentEyes != eye && !eye.empty() && _eyeList.count(eye) > 0){
        _framesOfEyes.SetTexture(_eyeList[eye].first);
        _framesOfEyes.SetMaxFrames(_eyeList[eye].second);
        _currcentEyes = eye;
    }
    else if(_eyeList.count(eye) < 1 && !eye.empty()){
        cout << "CCharacterLayer::SetPose(): can't find EYE \"" << eye << "\"." << endl;
        return false;
    }

    if (_currcentMouth != mouth && !mouth.empty() && _mouthList.count(mouth) > 0){
        _framesOfMouth.SetTexture(_mouthList[mouth].first);
        _framesOfMouth.SetMaxFrames(_mouthList[mouth].second);
        _currcentMouth = mouth;
    }
    else if(_mouthList.count(mouth) < 1 && !mouth.empty()){
        cout << "CCharacterLayer::SetPose(): can't find MOUTH \"" << mouth << "\"." << endl;
        return false;
    }
            
    return true;
}

void CCharacterLayer::OnSaveData(Object& json) const
{
    CImageBaseClass::OnSaveData(json);
    json << "eye" << _currcentEyes;
    json << "mouth" << _currcentMouth;
}
