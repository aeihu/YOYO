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

CCharacterLayer::CCharacterLayer()
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

sf::Transform CCharacterLayer::GetTransform()
{
    if (_baseNode)
        return _sprite.getTransform() * _baseNode->GetTransform();

    return _sprite.getTransform();
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

void CCharacterLayer::SetVoice(string name)
{
    _currcentVoice = name;
}

void CCharacterLayer::OnLoop()
{
    CBaiscProperties::OnLoop();
    if (_isBodyChangeing){ 
        if (_simAct.OnLoop()){
            _isBodyChangeing = false;
            _sprite.setTexture(_textureList[_currcentBody]._Texture, true);
        }
        
        _swapSprite.setColor(sf::Color(GetRed(), GetGreen(), GetBlue(), (1.0f - _alphaOfSwap) * GetAlpha()));
    }

    if (_sprite.getColor().a != GetAlpha() ||
        _sprite.getColor().r != GetRed() ||
        _sprite.getColor().g != GetGreen() ||
        _sprite.getColor().b != GetBlue())
        _sprite.setColor(sf::Color(GetRed(), GetGreen(), GetBlue(), GetAlpha() * _alphaOfSwap));

    Loop(&_sprite);
    Loop(&_swapSprite);

    if (IsShowed()){
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
                    _framesOfMouth.TurnOn(false);
                break;
            }

        if (_timer < CCommon::_Common.GetTicks()){
            if (_timer != 0)
                _framesOfEyes.TurnOn(false);
                
            _timer = std::rand() % 20000 + CCommon::_Common.GetTicks();
        }
    }
}
         
void CCharacterLayer::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (IsShowed()){
        if (_baseNode)
            Surf_Dest->draw(_sprite, _baseNode->GetTransform());
        else
            Surf_Dest->draw(_sprite);

        if (_isBodyChangeing)
            if (_baseNode)
                Surf_Dest->draw(_swapSprite, _baseNode->GetTransform());
            else
                Surf_Dest->draw(_swapSprite);
    }
}

//================================
//property:
//* EYE_OFFSET_X,
//* EYE_OFFSET_Y,
//* EYE_WIDTH,
//* EYE_HEIGHT,
//* EYE_FRAME_RATE,
//* MOUTH_OFFSET_X,
//* MOUTH_OFFSET_Y,
//* MOUTH_WIDTH,
//* MOUTH_HEIGHT,
//* MOUTH_FRAME_RATE,
//* BODY,
//* EYE:
//{
//  *PATH,
//  *MAX_FRAMES,
//}
//* MOUTH:
//{
//  *PATH,
//  *MAX_FRAMES,
//}
//ORDER,
//EYE_COMPOSITE,
//MOUTH_COMPOSITE,
//================================

bool CCharacterLayer::CheckList(const Object& json)
{
    bool __result = true;
    string __name;
    
    if (!json.has<Number>("EYE_OFFSET_X")){
        cout << "' can't find value of EYE_OFFSET_X." << endl;
        __result = false;
    }
    if (!json.has<Number>("EYE_OFFSET_Y")){
        cout << "' can't find value of EYE_OFFSET_Y." << endl;
        __result = false;
    }
    if (!json.has<Number>("EYE_WIDTH")){
        cout << "' can't find value of EYE_WIDTH." << endl;
        __result = false;
    }
    if (!json.has<Number>("EYE_HEIGHT")){
        cout << "' can't find value of EYE_HEIGHT." << endl;
        __result = false;
    }
    if (!json.has<Number>("EYE_FRAME_RATE")){
        cout << "' can't find value of EYE_FRAME_RATE." << endl;
        __result = false;
    }

    if (!json.has<Number>("MOUTH_OFFSET_X")){
        cout << "' can't find value of MOUTH_OFFSET_X." << endl;
        __result = false;
    }
    if (!json.has<Number>("MOUTH_OFFSET_Y")){
        cout << "' can't find value of MOUTH_OFFSET_Y." << endl;
        __result = false;
    }
    if (!json.has<Number>("MOUTH_WIDTH")){
        cout << "' can't find value of MOUTH_WIDTH." << endl;
        __result = false;
    }
    if (!json.has<Number>("MOUTH_HEIGHT")){
        cout << "' can't find value of MOUTH_HEIGHT." << endl;
        __result = false;
    }
    if (!json.has<Number>("MOUTH_FRAME_RATE")){
        cout << "' can't find value of MOUTH_FRAME_RATE." << endl;
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

bool CCharacterLayer::SetProperty(const Object& json, bool isLoad)
{
    Array __bodies = json.get<Array>("BODY");
    sf::IntRect _rectForEye(
        json.get<Number>("EYE_OFFSET_X"),
        json.get<Number>("EYE_OFFSET_Y"),
        json.get<Number>("EYE_WIDTH"),
        json.get<Number>("EYE_HEIGHT"));

    sf::IntRect _rectForMouth(
        json.get<Number>("MOUTH_OFFSET_X"),
        json.get<Number>("MOUTH_OFFSET_Y"),
        json.get<Number>("MOUTH_WIDTH"),
        json.get<Number>("MOUTH_HEIGHT"));

    bool _isEyeComposite = json.has<Boolean>("EYE_COMPOSITE") ? json.get<Boolean>("EYE_COMPOSITE") : false;
    bool _isMouthComposite = json.has<Boolean>("MOUTH_COMPOSITE") ? json.get<Boolean>("MOUTH_COMPOSITE") : false;

    if (isLoad){
        string __name;
    
        for (size_t i = 0; i<__bodies.size(); i++){
            if (!__bodies.has<String>(i))
                return false;

            __name = CTextFunction::GetNameInFilename(__bodies.get<String>(i));

            if (_textureList.count(__name) > 0){
                cout << "CCharacterLayer::SetProperty(): body texture " 
                    " \""<< __name << "\" has existed." <<endl;
                
                return false;
            }
            else{
                _textureList[__name] = SDataAboutTexture();
                sf::Image __image;

                _textureList[__name]._ImageForEye.create(_rectForEye.width, _rectForEye.height);
                _textureList[__name]._ImageForMouth.create(_rectForMouth.width, _rectForMouth.height);

                if (!CSurface::OnLoad(__bodies.get<String>(i).c_str(), __image))
                    return false;

                _textureList[__name]._ImageForEye.copy(__image, 0, 0, _rectForEye, true);
                _textureList[__name]._ImageForMouth.copy(__image, 0, 0, _rectForMouth, true);
                _textureList[__name]._Texture.loadFromImage(__image);
                _textureList[__name]._Texture.setSmooth(true);

                if (i == 0)
                    _currcentBody = __name;
            }
        }
    
        Array __eyes = json.get<Array>("EYE");
        for (size_t i = 0; i<__eyes.size(); i++){
            __name = CTextFunction::GetNameInFilename(__eyes.get<Object>(i).get<String>("PATH"));

            if (_eyeList.count(__name) > 0){
                cout << "CCharacterLayer::SetProperty(): eye texture " 
                    " \""<< __name << "\" has existed." <<endl;
                
                return false;
            }
            else{
                _eyeList[__name] = make_pair(sf::Image(), __eyes.get<Object>(i).get<Number>("MAX_FRAMES"));
            
                if (isLoad)
                    if (!CSurface::OnLoad(__eyes.get<Object>(i).get<String>("PATH").c_str(), _eyeList[__name].first))
                        return false;
            }
        }

        Array __mouths = json.get<Array>("MOUTH");
        for (size_t i = 0; i<__mouths.size(); i++){
            __name = CTextFunction::GetNameInFilename(__mouths.get<Object>(i).get<String>("PATH"));

            if (_mouthList.count(__name) > 0){
                cout << "CCharacterLayer::SetProperty(): mouth texture " 
                    " \""<< __name << "\" has existed." <<endl;
                
                return false;
            }
            else{
                _mouthList[__name] = make_pair(sf::Image(), __mouths.get<Object>(i).get<Number>("MAX_FRAMES"));
                if (!CSurface::OnLoad(__mouths.get<Object>(i).get<String>("PATH").c_str(), _mouthList[__name].first))
                    return false;
            }
        }
    }
    
    if (_flipX)
        FlipX();

    if (_flipY)
        FlipY();

    _sprite.setTexture(_textureList[_currcentBody]._Texture, true);

    _framesOfMouth.SetFrameRate(json.get<Number>("MOUTH_FRAME_RATE"));
    if (_isMouthComposite)
        _framesOfMouth.SetDestTexture(&_textureList[_currcentBody]._Texture, _rectForMouth, &_textureList[_currcentBody]._ImageForMouth);
    else
        _framesOfMouth.SetDestTexture(&_textureList[_currcentBody]._Texture, _rectForMouth);

    _framesOfEyes.SetFrameRate(json.get<Number>("EYE_FRAME_RATE"));
    if (_isEyeComposite)
        _framesOfEyes.SetDestTexture(&_textureList[_currcentBody]._Texture, _rectForEye, &_textureList[_currcentBody]._ImageForEye);
    else
        _framesOfEyes.SetDestTexture(&_textureList[_currcentBody]._Texture, _rectForEye);

    if (json.has<Number>("ORDER"))
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
        
        if (IsShowed() && isEffect){
            _swapSprite.setTexture(_textureList[body]._Texture, true);
            _alphaOfSwap = 1.0f;
            _simAct.OnCleanup();
            _simAct.AddAction(new CActionTo(&_alphaOfSwap, 400, 0, true));
            _isBodyChangeing = true;
            _timer += 1000;
        }
        else{
            _alphaOfSwap = 1.0f;
            _simAct.OnCleanup();
            _sprite.setTexture(_textureList[body]._Texture, true);
        }

        _framesOfEyes.SetDestTexture(&_textureList[body]._Texture, &_textureList[body]._ImageForEye);
        _framesOfMouth.SetDestTexture(&_textureList[body]._Texture, &_textureList[body]._ImageForMouth);
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
