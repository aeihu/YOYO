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

class CResourceControl : public CObjectControl
{
    protected:
        friend bool Common_FuncOfShow(string funcName, CResourceControl* controlBase, vector<string> args);
        friend bool Cmd_AddVariable(vector<string> args);

        unsigned int                            _interval;
        bool                                    _isNeedSort;
        vector<pair<string, CImageBaseClass*> > _drawableObjectList;
        //map<string, CImageBaseClass*>           _drawableObjectList;
        map<string, string>                     _userVariableList;
        map<string, string>                     _systemVariableList;

        inline CResourceControl() {_interval = 10; _isNeedSort = false;}
    public:
        static CResourceControl                 _ResourceManager;

        inline void SetInterval(unsigned int interval) {_interval = interval;}
        bool SetImageVisibility(string name, int alpha, float incr, bool pause);
        bool SetImageVisibility(string name, int alpha, unsigned int elapsed, bool pause);
        bool SetLayerOrder(string name, char order);

        bool AddVariable(string name, string val);
        bool SetVariable(string name, string val);
        string GetVariable(string name);
        bool DelVariable(string name);

        bool AddDrawableObject(string name, CImageBaseClass* obj);
        bool DelDrawableObject(string name);
        CImageBaseClass* GetDrawableObject(string name);
        void SetDrawableObjectLayerOrder(string name, char layer);
        
        bool IsExists(string name);
        bool Move(string name, float x, float y, unsigned int elapsed, bool pause);
        char Show(string name, float x, float y, char type, unsigned int elapsed, bool pause, int alpha=255);
        char Hide(string name, char type, unsigned int elapsed, bool pause);
        
        bool OnLButtonUp(int mX, int mY);
        bool OnLButtonDown(int mX, int mY);
        bool OnMouseMove(int mX, int mY);
        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
        void OnSaveData();
        void OnLoadData();
};

#endif