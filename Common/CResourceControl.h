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
#include "CClassFuncOfAction.h"

using namespace std;

class CResourceControl : public CScript
{
    private:
        string                                  _fileNameOfScript;
        string                                  _nameOfLoadingImg;

        Object                                  _script;
        Object                                  _gameBaiscAsset;
        sf::Thread                              _threadOfLoading;
        bool                                    _DrawableObjCtrlEnable;
        bool                                    _EffectObjCtrlEnable;

        string GetNameInFilename(string filename);
        void BeginLoadProcess();
        void EndLoadProcess();
        void LoadAsset();
        char CheckIn(Object& json, string colName, string objTypeName);
        bool CheckOut(Object& json, string colName, string objTypeName);
        bool OnInit(string filename);
    protected:
        //friend bool Common_FuncOfShow(string funcName, CResourceControl* controlBase, vector<string> args);
        //friend bool Cmd_AddVariable(vector<string> args);
        
        //map<string, CCamera*>                   _cameraList;
        //CScript                                 _script;

        CResourceControl();
    public:
        static CResourceControl                 _ResourceManager;
        CSoundBank                              _SoundControl;
        //CPositionControl                        _PositionControl;
        CDrawableObjectControl                  _DrawableObjectControl;
        CDrawableObjectControl                  _EffectObjectControl;
        CObjectControl                          _ObjectControl;
        CCameraControl                          _CameraControl;
        CSimultaneousOfAction                   _ActionControl;
        
        bool OnInit(string filename, sf::RenderTarget* display);
        bool LoadScript(string filename);
        void OnLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);
        void OnCleanup();
        void OnSaveData();
        void OnLoadData();
};

#endif