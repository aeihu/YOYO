/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CRESOURCECONTROL_H_
    #define _CRESOURCECONTROL_H_

#include <string>
#include "CCommon.h"
#include "CEvent.h"
#include "CObjectControl.h"
#include "../Graphics/CCamera.h"
#include "../Sound/CSoundBank.h"
#include "../Graphics/CDrawableObjectControl.h"
#include "../Graphics/CCameraControl.h"
#include "../Action/CClassFuncOfAction.h"
#include "../Effect/CScreenEffect.h"
#include "../GSM_Window/CMessageBox.h"
#include "../Parser/CLua.h"

using namespace std;

/*
LoadScript()->BeginLoadProcess()->LoadAsset()->EndLoadProcess()
*/

class CResourceControl
{
    public:
        enum EProcStatus{
            INIT = 0,

            LOADING_ASSET = 10,
            LOADED_ASSET,
            LOADING_SAVEDATA,
            LOADED,
            EXIT_LOADING,

            PLAYING = 20,
            PLAYING_MSGBOX_TYPING,
            PLAYING_MSGBOX_TYPED,
            PLAYING_LOGBOX,
            PLAYING_SAVEBOX,
            PLAYING_LOADBOX
        };
    private:
        sf::Thread                      _threadOfLoading;

        string                          _fileNameOfCurrentRunningScript;
        string                          _fileNameOfLuaForRun;

        unsigned long                   _oldTimeForAuto;
        int                             _currentMgsLine;

        Object                          _playerData;
        Object                          _scriptConfig;
        Object                          _gameBaiscAsset;

        bool                            _isLoadPlayerData;
        bool                            _msgboxPauseRequest;

        EProcStatus                     _processStatus;

        bool                            _isAuto;
        bool                            _flagForAuto;

        map<string, string>             _userVariableList;
        map<string, string>             _systemVariableList;
        
        void LoadPlayerDataProcess();
        void ThreadOfLoadAsset();
        void Compare(Object& src, Object& des, string colName);

        bool JsonProcess(Object& src, Object& des, string colName);
        bool LoadJson(Object& obj, string filename);

        char CheckIn(Object& json, string colName, string objTypeName);
        bool CheckOut(Object& json, string colName, string objTypeName);

        void AutoToNextStep();
        void ExitLoadingStatus();
        void CopyActForLoadingFinishToActionControl();
    protected:

        CResourceControl();
    public:
        static CResourceControl                 _ResourceManager;
        CSoundBank                              _SoundControl;
        CDrawableObjectControl                  _DrawableObjectControl;
        CDrawableObjectControl                  _LoadingObjectControl;
        CObjectControl                          _ObjectControl;
        CCameraControl                          _CameraControl;
        CSimultaneousOfAction                   _ActionControl;
        CSimultaneousOfAction                   _ActForLoadingBegin;
        CSimultaneousOfAction                   _ActForLoadingFinish;
        CLua                                    _LuaControl;

        void SkipOn();
        void SkipOff();
        bool AddVariable(string name, string val);
        bool SetVariable(string name, string val);
        bool DelVariable(string name);

        void DelActionForActionControl(string name);

        EProcStatus GetProcessStatus() const;
        bool GetAuto() const;
        void SetAuto(bool isAuto);
        string GetVariable(string name);

        bool GetMsgboxPauseStatus() const;
        void OnMsgboxPause();
        void OffMsgboxPause();

        //void LockMutexInLua();
        //void UnlockMutexInMain();

        bool OnInit(string filename, sf::RenderWindow* Window);
        bool LoadScript(string filename);
        void OnLoop();
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
        bool OnSaveData(int index) const;
        bool OnLoadData(int index);
        
        void OnLButtonDown(int mX, int mY);
        void OnLButtonUp(int mX, int mY);
        void OnRButtonDown(int mX, int mY);
        void OnRButtonUp(int mX, int mY);
        void OnMouseMove(int mX, int mY);
};

#endif