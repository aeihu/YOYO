/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CRESOURCECONTROL_H_
    #define _CRESOURCECONTROL_H_

#include <string>
#include "CCommon.h"
#include "CObjectControl.h"
#include "CPositionControl.h"
#include "../Graphics/CCamera.h"
#include "../Script/CScript.h"
#include "../Sound/CSoundBank.h"
#include "../Graphics/CDrawableObjectControl.h"

using namespace std;

class CResourceControl : public CScript
{
    private:
        Object                                  _script;

        string GetNameInFilename(string filename);
        bool CheckIn(Object& json, string name, string objTypeName);
    protected:
        friend bool Common_FuncOfShow(string funcName, CResourceControl* controlBase, vector<string> args);
        friend bool Cmd_AddVariable(vector<string> args);
        
        map<string, CCamera*>                   _cameraList;
        //CScript                                 _script;

        inline CResourceControl() {_script.reset();}
    public:
        static CResourceControl                 _ResourceManager;
        CSoundBank                              _SoundControl;
        CPositionControl                        _PositionControl;
        CDrawableObjectControl                  _DrawableObjectControl;
        CObjectControl                          _ObjectControl;

        bool AddVariable(string name, string val);
        bool SetVariable(string name, string val);
        string GetVariable(string name);
        bool DelVariable(string name);

        bool AddCamera(string name);
        bool DelCamera(string name);
        CCamera* GetCamera(string name);
        
        
        bool OnInit(string filename);
        bool LoadScript(string filename);
        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
        void OnSaveData();
        void OnLoadData();
};

#endif