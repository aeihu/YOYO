/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CDrawableObjectControl_H_
    #define _CDrawableObjectControl_H_

#include <string>
#include "CCommon.h"
#include "../Graphics/CImageBaseClass.h"
#include "../Common/CObjectControl.h"

using namespace std;

class CDrawableObjectControl : public CObjectControl
{
    protected:
        friend bool Common_FuncOfShow(string funcName, CDrawableObjectControl* controlBase, vector<string> args);

        unsigned int                            _interval;
        vector<pair<string, CImageBaseClass*>>  _drawableObjectList;
        //map<string, CImageBaseClass*>           _drawableObjectList;

        inline CDrawableObjectControl() {_interval = 10;}
    public:
        static CDrawableObjectControl         _ResourceManager;

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