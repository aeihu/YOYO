/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCHARACTERLAYER_H_
    #define _CCHARACTERLAYER_H_

#include "../Graphics/CImageBaseClass.h"
#include "../Common/CConfigFile.h"
#include "../Graphics/CSequenceOfFrames.h"
#include "../Sound/CSoundBank.h"
#include <map>
#include <string>

using namespace std;

class CCharacterLayer : public CImageBaseClass, public CConfigFile
{
  private:
        Object                  _faceList;
        bool                    _isFaceEnable;
        CSequenceOfFrames       _framesOfMouth;
        CSequenceOfFrames       _framesOfEyes;
        string                  _currcentFace;
        string                  _currcentVoice;
        unsigned long           _timer;
        
        bool CheckList(Object json);
        bool SetProperty(Object json);
  public:
        CCharacterLayer(float x=0.0f, float y=0.0f);
        
        static CCharacterLayer* Create(const char* filename);
        
        void FlipHorizontally();
        bool SetFace(string name);
        void SetVoice(string name);
        
        bool OnSubLoop();
        virtual void OnSaveData(Object& json) const;
       // void OnRender(sf::RenderTarget* Surf_Dest);
};
#endif
