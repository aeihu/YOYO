/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCHARACTERLAYER_H_
    #define _CCHARACTERLAYER_H_

#include "../Graphics/CImageBaseClass.h"
#include "../Common/CCommon.h"
#include "../Common/Define.h"
#include <map>
#include <string>

using namespace std;

class CCharacterLayer : public CImageBaseClass
{
  private:
        CCoordinate2f           _offset;
        CImage                  _imageFace;
        CSprite                 _spriteFace;
        map<string, string>     _faceList;
        bool                    _isFaceEnable;

        bool CheckList(map<string, string> list);
        bool SetProperty(map<string, string> list);
        bool LoadImage(const char* FileName, CImage &image, CSprite &sprite);
  public:
        CCharacterLayer(float x=0.0f, float y=0.0f);

        bool LoadChara(const char* FileName);
        bool SetFace(string name);

        bool Subclass_Loop();
        void Subclass_Render(CWindow* Surf_Dest);
};
#endif
