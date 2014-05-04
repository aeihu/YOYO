/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CPARTICLESYSTEMCONTROL_H_
    #define _CPARTICLESYSTEMCONTROL_H_

#include "../Common/CControlBaseClass.h"
#include "CParticleSystem.h"
#include <map>

class CParticleSystemControl : public CControlBaseClass
{
    private:
        friend class CResourceManager;

        map<string, CParticleSystem>    _particleSystemList;
        CObject* GetObject(std::string name);
    public:
        char AddParticleSystem(string name, const char* filename);
        bool DelParticleSystem(string name);
        char ShowParticleSystem(string name);
        char HideParticleSystem(string name);

        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
};

#endif