/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIMGLAYERCONTROL_H_
    #define _CIMGLAYERCONTROL_H_

#include "CImgLayer.h"
#include "../Common/CControlOfImageBaseClass.h"
#include "../Common/CAdder.h"
#include <map>
#include <string>

class CImgLayerControl : public CControlOfImageBaseClass
{
    private:
        friend class CResourceManager;
        
        CObject* GetObject(std::string name);
        std::map<std::string, CImgLayer>    _imgLayerList;
    public:
        bool AddImage(std::string name, const char* filename, float x=0.0f, float y=0.0f);
        bool DelImage(std::string name);

        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
};

#endif
