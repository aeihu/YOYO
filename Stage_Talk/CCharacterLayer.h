/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CCHARACTERLAYER_H_
    #define _CCHARACTERLAYER_H_

#include "CImgLayer.h"
#include "../Common/CConfigFile.h"
#include "../Graphics/CSequenceOfFrames.h"
#include "../Sound/CSoundBank.h"
#include "../Text/CTextFunction.h"
#include <map>
#include <string>

using namespace std;

class CCharacterLayer : public CImageBaseClass, public CConfigFile
{
    private:
        struct SDataAboutTexture
        {
            sf::Texture _Texture;
            sf::Image _ImageForEye;
            sf::Image _ImageForMouth;
        };

        CSequenceOfFrames                       _framesOfEyes;
        CSequenceOfFrames                       _framesOfMouth;
        string                                  _currcentBody;
        string                                  _currcentEyes;
        string                                  _currcentMouth;
        string                                  _currcentVoice;
        unsigned long                           _timer;
        map<string, pair<sf::Image, int> >      _mouthList;
        map<string, pair<sf::Image, int> >      _eyeList;
        map<string, SDataAboutTexture>          _textureList;

        float                                   _alphaOfSwap;
        sf::Sprite                              _swapSprite;
        sf::Sprite                              _sprite;
        CSimultaneousOfAction                   _simAct;
        bool                                    _isBodyChangeing;
        
        bool CheckList(Object json);
        bool SetProperty(Object json, bool isLoad=true);
        void Flip();
    public:
        CCharacterLayer(float x=0.0f, float y=0.0f);

        virtual void FlipX();
        virtual void FlipY();
        const sf::Vector2f& GetGlobalPosition() const;
        
        static CCharacterLayer* Create(const char* filename);
        
        bool SetPose(string body, string eye, string mouth, bool isEffect);
        void SetPose(vector<string> args);

        void SetVoice(string name);
        
        void OnLoop();
        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
};
#endif
