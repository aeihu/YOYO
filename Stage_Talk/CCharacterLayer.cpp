/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CCharacterLayer.h"
#include "../Common/CZlib.h"
#include "../Common/Cio.h"
#include "../Common/CResourceControl.h"

CCharacterLayer::CCharacterLayer(float x, float y):CImageBaseClass(x,y)
{
    _isBodyChangeing = false;
    _framesOfMouth._Type = CAnimation::Oscillate;
    _framesOfEyes._Type = CAnimation::Oscillate;
    _currcentBody = _currcentMouth = _currcentEyes = _currcentVoice = "";
    _timer = 0;
    _alphaOfSwap = 1.0f;
}

CCharacterLayer* CCharacterLayer::Create(const char* filename)
{    
    CCharacterLayer* __chr = new CCharacterLayer();
    if (__chr->LoadConfigFile(filename)){
        __chr->SetClassName("CharacterLayer");
        __chr->SetPath(filename);
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
        
void CCharacterLayer::SetVoice(vector<string> args)
{
    if (args.size() > 0)
        SetVoice(args[0]);
}

void CCharacterLayer::OnLoop()
{
    if (_isBodyChangeing){ 
        if (_simAct.OnLoop()){
            _isBodyChangeing = false;
            _sprite.setTexture(_textureList[_currcentBody],true);
        }
        
        _swapSprite.setColor(sf::Color(_red, _green, _blue, (1.0f-_alphaOfSwap)*_alpha));
    }

    _isShowed = _alpha > 0 ? true : false;

    if (_sprite.getColor().a != _alpha ||
        _sprite.getColor().r != _red ||
        _sprite.getColor().g != _green ||
        _sprite.getColor().b != _blue)
        _sprite.setColor(sf::Color(_red, _green, _blue, _alpha*_alphaOfSwap));

    if (_isShowed){
        if (_coordinate != _sprite.getPosition()){
            _sprite.setPosition(_coordinate);
            _swapSprite.setPosition(_coordinate);
        }
        
        if ((_origin.x * _sprite.getLocalBounds().width != _sprite.getOrigin().x) ||
            (_origin.y * _sprite.getLocalBounds().height != _sprite.getOrigin().y)){
            _sprite.setOrigin(_origin.x * _sprite.getLocalBounds().width,
                _origin.y * _sprite.getLocalBounds().height);

            _swapSprite.setOrigin(_sprite.getOrigin());
        }
        
        if (_scale != _sprite.getScale()){
            _sprite.setScale(_scale);
            _swapSprite.setScale(_scale);
        }

        if (_rotation != _sprite.getRotation()){
            _sprite.setRotation(_rotation);
            _swapSprite.setRotation(_rotation);
        }

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
         
void CCharacterLayer::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_isShowed)
        Surf_Dest->draw(_sprite);

    if (_isBodyChangeing)
        Surf_Dest->draw(_swapSprite);
}

bool CCharacterLayer::CheckList(Object json) 
{
    bool __result = true;
    string __name;
    if (!json.has<Number>("ORDER")){
        cout << "can't find value of ORDER." << endl;
        __result = false;
    }
    
    if (!json.has<Array>("BODY")){
        cout << "can't find value of BODY." << endl;
        __result = false;
    }
    else{
        if (json.get<Array>("BODY").size() < 1){
            cout << "value of BODY must be has one." << endl;
            __result = false;
        }

        Object __body;
        for (size_t i=0; i<json.get<Array>("BODY").size(); i++){
            __body = json.get<Array>("BODY").get<Object>(i);
            if (!__body.has<String>("BODY_PATH")){
                cout << "can't find value of BODY_PATH." << endl;
                __result = false;
            }

            __name = CTextFunction::GetNameInFilename(__body.get<String>("BODY_PATH"));
            if (!__body.has<Number>("EYE_OFFSET_X")){
                cout << "BODY '" << __name << "' can't find value of EYE_OFFSET_X." << endl;
                __result = false;
            }
            if (!__body.has<Number>("EYE_OFFSET_Y")){
                cout << "BODY '" << __name << "' can't find value of EYE_OFFSET_Y." << endl;
                __result = false;
            }
            if (!__body.has<Number>("EYE_WIDTH")){
                cout << "BODY '" << __name << "' can't find value of EYE_WIDTH." << endl;
                __result = false;
            }
            if (!__body.has<Number>("EYE_HEIGHT")){
                cout << "BODY '" << __name << "' can't find value of EYE_HEIGHT." << endl;
                __result = false;
            }
            if (!__body.has<Number>("EYE_FRAME_RATE")){
                cout << "BODY '" << __name << "' can't find value of EYE_FRAME_RATE." << endl;
                __result = false;
            }

            if (!__body.has<Number>("MOUTH_OFFSET_X")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_OFFSET_X." << endl;
                __result = false;
            }
            if (!__body.has<Number>("MOUTH_OFFSET_Y")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_OFFSET_Y." << endl;
                __result = false;
            }
            if (!__body.has<Number>("MOUTH_WIDTH")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_WIDTH." << endl;
                __result = false;
            }
            if (!__body.has<Number>("MOUTH_HEIGHT")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_HEIGHT." << endl;
                __result = false;
            }
            if (!__body.has<Number>("MOUTH_FRAME_RATE")){
                cout << "BODY '" << __name << "' can't find value of MOUTH_FRAME_RATE." << endl;
                __result = false;
            }    
        }
    }

    if (!json.has<Array>("EYE")){
        cout << "can't find value of EYE." << endl;
        __result = false;
    }
    else{
        for (size_t i=0; i<json.get<Array>("EYE").size(); i++){
            if (!json.get<Array>("EYE").has<Object>(i)){
                __result = false;
                continue;
            }

            __name = CTextFunction::GetNameInFilename(json.get<Array>("EYE").get<Object>(i).get<String>("PATH"));

            if (!json.get<Array>("EYE").get<Object>(i).has<String>("PATH")){
                cout << "EYE '" << __name << "' can't find value of PATH." << endl;
                __result = false;
            }

            if (!json.get<Array>("EYE").get<Object>(i).has<Number>("MAX_FRAMES")){
                cout << "EYE '" << __name << "' can't find value of MAX_FRAMES." << endl;
                __result = false;
            }
        }
    }

    if (!json.has<Array>("MOUTH")){
        cout << "can't find value of MOUTH." << endl;
        __result = false;
    }
    else{
        for (size_t i=0; i<json.get<Array>("MOUTH").size(); i++){
            if (!json.get<Array>("MOUTH").has<Object>(i)){
                __result = false;
                continue;
            }

            __name = CTextFunction::GetNameInFilename(json.get<Array>("MOUTH").get<Object>(i).get<String>("PATH"));

            if (!json.get<Array>("MOUTH").get<Object>(i).has<String>("PATH")){
                cout << "MOUTH '" << __name << "' can't find value of PATH." << endl;
                __result = false;
            }

            if (!json.get<Array>("MOUTH").get<Object>(i).has<Number>("MAX_FRAMES")){
                cout << "MOUTH '" << __name << "' can't find value of MAX_FRAMES." << endl;
                __result = false;
            }
        }
    }

    return __result;
}

bool CCharacterLayer::SetProperty(Object json, bool isLoad)
{
    Array __bodyList = json.get<Array>("BODY");

    if (isLoad){
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
            
                _textureList[__name].setSmooth(true);

                if (i == 0){
                    _currcentBody = __name;
                    _sprite.setTexture(_textureList[__name],true);
                
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
            
                if (isLoad)
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
    }
    
    if (_flipX)
        FlipX();

    if (_flipY)
        FlipY();

    SetLayerOrder(json.get<Number>("ORDER"));
    return true;
}

void CCharacterLayer::SetPose(vector<string> args)
{
    if (args.size() >= 3)
        SetPose(args[0], args[1], args[2], args.size()==3);
}

bool CCharacterLayer::SetPose(string body, string eye, string mouth, bool isEffect)
{
    bool __isBodyChanged = _currcentBody != body;
    if (__isBodyChanged && !body.empty() && _textureList.count(body) > 0){
        _currcentBody = body;
        
        if (_isShowed && isEffect){
            _swapSprite.setTexture(_textureList[body],true);
            _alphaOfSwap = 1.0f;
            _simAct.OnCleanup();
            _simAct.AddAction(new CActionTo(&_alphaOfSwap, 400, 0, true));
            _isBodyChangeing = true;
            _timer += 1000;
        }
        else{
            _alphaOfSwap = 1.0f;
            _simAct.OnCleanup();
            _sprite.setTexture(_textureList[body],true);
        }

        _framesOfEyes.SetDestTexture(&_textureList[body]);
        _framesOfMouth.SetDestTexture(&_textureList[body]);
    }
    else if(_textureList.count(body) < 1 && !body.empty()){
        cout << "CCharacterLayer::SetPose(): can't find BODY \"" << body << "\"." << endl;
        return false;
    }

    if ((__isBodyChanged || _currcentEyes != eye) && 
        !eye.empty() && 
        _eyeList.count(eye) > 0){

        _framesOfEyes.SetTexture(_eyeList[eye].first);
        _framesOfEyes.SetMaxFrames(_eyeList[eye].second);
        _currcentEyes = eye;
    }
    else if(_eyeList.count(eye) < 1 && !eye.empty()){
        cout << "CCharacterLayer::SetPose(): can't find EYE \"" << eye << "\"." << endl;
        return false;
    }

    if ((__isBodyChanged || _currcentMouth != mouth) && 
        !mouth.empty() && 
        _mouthList.count(mouth) > 0){

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

    if (!_currcentBody.empty()) json << "body" << _currcentBody;
    if (!_currcentEyes.empty()) json << "eye" << _currcentEyes;
    if (!_currcentMouth.empty()) json << "mouth" << _currcentMouth;
    if (!_currcentVoice.empty()) json << "voice" << _currcentVoice;
}
        
void CCharacterLayer::OnLoadData(Object json)
{
    CImageBaseClass::OnLoadData(json);
    SetPose(
        json.has<String>("body") ? json.get<String>("body") : "", 
        json.has<String>("eye") ? json.get<String>("eye") : "", 
        json.has<String>("mouth") ? json.get<String>("mouth") : "", 
        false);

    SetVoice(json.has<String>("voice") ? json.get<String>("voice") : "");
}
