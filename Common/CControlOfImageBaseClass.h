/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCONTROLOFIMAGEBASECLASS_H_
    #define _CCONTROLOFIMAGEBASECLASS_H_

#include <string>
#include "CCommon.h"
#include "../Graphics/CImageBaseClass.h"
#include "../Common/CControlBaseClass.h"

using namespace std;

class CControlOfImageBaseClass : public CControlBaseClass
{
    protected:
        friend bool Common_FuncOfShow(string funcName, CControlOfImageBaseClass* controlBase, vector<string> args);

        unsigned int                            _interval;
        map<string, CImageBaseClass*>           _drawableObjectList;

        inline CControlOfImageBaseClass() {_interval = 10;}
    public:
        static CControlOfImageBaseClass         _ResourceManager;

        inline void SetInterval(unsigned int interval) {_interval = interval;}
        bool SetImageVisibility(string name, int alpha, float incr, bool pause);

        bool AddDrawableObject(string name, CImageBaseClass* obj);
        bool DelDrawableObject(string name);
        CImageBaseClass* GetDrawableObject(string name);
        
        bool IsExists(string name);
        bool Move(string name, float x, float y, unsigned int elapsed, bool pause);
        char Show(string name, float x, float y, char type, unsigned int elapsed, bool pause, int alpha=255);
        char Hide(string name, char type, unsigned int elapsed, bool pause);
        
        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
};

#endif