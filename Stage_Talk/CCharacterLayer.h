/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
        list<pair<string, pair<string, string> > >      _faceList;
        bool                                            _isFaceEnable;
        CSequenceOfFrames                               _framesOfMouth;
        CSequenceOfFrames                               _framesOfEyes;
        string                                          _currcentVoice;
        unsigned long                                   _timer;
        
        bool CheckList(map<string, string>& list);
        bool SetProperty(map<string, string>& list);
  public:
        CCharacterLayer(float x=0.0f, float y=0.0f);
        
        static CCharacterLayer* Create(const char* filename);
        bool SetFace(string name);
        void SetVoice(string name);

        bool OnLoop();
       // void OnRender(sf::RenderWindow* Surf_Dest);
};
#endif
