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
#include "../Common/CCommon.h"
#include "../Animation/CAnimation.h"
#include "../Graphics/CSequenceOfFrames.h"
#include <map>
#include <string>

using namespace std;

class CCharacterLayer : public CImageBaseClass
{
  private:
        sf::Vector2f                _offset;
        sf::Texture                 _imageFace;
        map<string, string>         _faceList;
        bool                        _isFaceEnable;
        CSequenceOfFrames           _framesOfMouth;

        bool CheckList(map<string, string>& list);
        bool SetProperty(map<string, string>& list);
        bool LoadImage(const char* FileName, sf::Texture &image, sf::Sprite &sprite);
  public:
        CAnimation                  _AnimationControl;

        CCharacterLayer(float x=0.0f, float y=0.0f);

        bool LoadChara(const char* FileName);
        bool SetFace(string name);

        bool Subclass_Loop();
        void Subclass_Render(sf::RenderWindow* Surf_Dest);
};
#endif
