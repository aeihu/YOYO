/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CPOSITIONS_H_
    #define _CPOSITIONS_H_

#include "CCharacterLayer.h"
#include "../Common/CControlBaseClass.h"
#include "../Common/Define.h"
#include <map>
#include <string>

class CCharacterLayerControl : public CControlBaseClass
{
    private:
        map<string, CCoordinate2f>          _positions;
    public:
        map<string, CCharacterLayer>        _CharacterList;

        CCharacterLayerControl();
        
        bool IsAlreadyExists(string name);
        char AddCharacter(string name, const char* filename, float x, float y);
        bool Move(string name, string position, float increment, bool pause);
        bool Move(string name, float x, float y, float increment, bool pause);
        bool Show(string name, string position, char type, float buf, float increment, bool pause);
        bool Show(string name, float x, float y, char type, float buf, float increment, bool pause);
        bool Hide(string name, char type, float buf, float increment, bool pause);

        bool SetVisibility(string name, int alpha, int increment, bool pause);
        void AddPosition(string name, float x, float y);
        void DelPosition(string name);
        bool GetPosition(string name, float* x, float* y);

        void OnLoop(bool &pause);
        void OnRender(CWindow* Surf_Dest);
};

#endif
