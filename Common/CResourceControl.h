/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
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
#include "../Graphics/CCamera.h"
#include "../Script/CScript.h"
#include "../Sound/CSoundBank.h"
#include "../Graphics/CDrawableObjectControl.h"
#include "../Graphics/CCameraControl.h"
#include "../Action/CClassFuncOfAction.h"

using namespace std;

class CResourceControl : public CScript
{
    private:
        string                          _fileNameOfScript;

        Object                          _script;
        Object                          _gameBaiscAsset;
        sf::Thread                      _threadOfLoading;
        bool                            _drawableObjCtrlEnable;
        bool                            _effectObjCtrlEnable;
        bool                            _pause;
        map<string, string>             _userVariableList;
        map<string, string>             _systemVariableList;

        void BeginLoadProcess();
        void EndLoadProcess();
        void LoadAsset();
        void Compare(Object& src, Object& des, string colName);

        bool JsonProcess(Object& src, Object& des, string colName);
        bool LoadJson(Object& obj, string filename);

        char CheckIn(Object& json, string colName, string objTypeName);
        bool CheckOut(Object& json, string colName, string objTypeName);
        bool OnInit(string filename);
    protected:

        CResourceControl();
    public:
        static CResourceControl                 _ResourceManager;
        CSoundBank                              _SoundControl;
        CDrawableObjectControl                  _DrawableObjectControl;
        CDrawableObjectControl                  _EffectObjectControl;
        CObjectControl                          _ObjectControl;
        CCameraControl                          _CameraControl;
        CSimultaneousOfAction                   _ActionControl;
        
        bool AddVariable(string name, string val);
        bool SetVariable(string name, string val);
        string GetVariable(string name);
        bool DelVariable(string name);

        bool OnInit(string filename, sf::RenderTarget* display);
        bool LoadScript(string filename);
        void OnLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);
        void OnCleanup();
        void OnSaveData();
        void OnLoadData();
};

#endif