/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CPOSITIONS_H_
    #define _CPOSITIONS_H_

#include "CCharacterLayer.h"
#include "../Common/CControlBaseClass.h"
#include "../Sound/CSoundBank.h"
#include <map>
#include <string>

class CCharacterLayerControl : public CControlBaseClass
{
    public:
        map<string, CCharacterLayer>     _CharacterList;

        CCharacterLayerControl();
        
        bool IsAlreadyExists(string name);
        char AddCharacter(string name, const char* filename);
        bool DelCharacter(string name);
        bool Move(string name, float x, float y, float increment, bool pause);
        char Show(string name, float x, float y, char type, float increment, bool pause, int alpha=255);
        bool Hide(string name, char type, float increment, bool pause);

        bool SetVisibility(string name, int alpha, int increment, bool pause);

        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
};

#endif
