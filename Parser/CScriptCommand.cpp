/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CScriptCommand.h"
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Sound/CSoundBank.h"
#include "../Gui/CButton.h"
#include "../Common/CResourceControl.h"
#include "../Common/CCommon.h"
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Effect/CParticleSystem.h"
#include "../GSM_Window/CLogBox.h"
#include "../GSM_Window/CMessageBox.h"
#include <iostream>
#include <algorithm>
#include "../Action/CClassFuncArgsOfAction.h"
#include "../Gui/CText.h"


int Common_YieldCont(lua_State *L, int, lua_KContext ctx)
{
    cout << "Common_YieldCont(): resume suspends." << endl;
    return 0;
}

bool Common_GetValue(lua_State* L, const char* fieldName, int& val)
{
    if (lua_istable(L, -1))
    {
        if (lua_getfield(L, -1, fieldName) == LUA_TNUMBER) {
            val = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValue(lua_State* L, const char* fieldName, size_t& val)
{
    if (lua_istable(L, -1))
    {
        if (lua_getfield(L, -1, fieldName) == LUA_TNUMBER) {
            val = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValue(lua_State* L, const char* fieldName, string& val)
{
    if (lua_istable(L, -1))
    {
        if (lua_getfield(L, -1, fieldName) == LUA_TSTRING) {
            val = lua_tostring(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValue(lua_State* L, const char* fieldName, bool& val)
{
    if (lua_istable(L, -1))
    {
        if (lua_getfield(L, -1, fieldName) == LUA_TBOOLEAN) {
            val = lua_toboolean(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValue(lua_State* L, const char* fieldName, float& val)
{
    if (lua_istable(L, -1))
    {
        if (lua_getfield(L, -1, fieldName) == LUA_TNUMBER) {
            val = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValue(lua_State* L, const char* fieldName, vector<string>& val)
{
    if (lua_istable(L, -1))
    {
        if (lua_getfield(L, -1, fieldName) == LUA_TTABLE)
        {
            int __index = 1;
            while (lua_rawgeti(L, -1, __index))
            {
                val.push_back(lua_tostring(L, -1));
                lua_pop(L, 1);
                __index++;
            }
            lua_pop(L, 2);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

enum
{
    CMD_ERR = -1,
    CMD_OK,
    CMD_YIELD
};

int Common_FuncOfColor(string objTypeName, lua_State* args)
{ 
    string __funcName = "Cmd_Color" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    float __cr = 0.0f;
    bool __crIsBe = Common_GetValue(args, "cr", __cr);
    float __cg = 0.0f;
    bool __cgIsBe = Common_GetValue(args, "cg", __cg);
    float __cb = 0.0f;
    bool __cbIsBe = Common_GetValue(args, "cb", __cb);

    if (!__crIsBe && !__cgIsBe && !__cbIsBe)
        return CMD_ERR;

    string __name = "";
    if (objTypeName != "ScrEffect")
    {

        if (!Common_GetValue(args, "n", __name))
        {
            cout << __funcName << "(): parameter \"n\" must be need." << endl;
            return CMD_ERR;
        }
    }
    else
    {
        __name = "screen";
    }

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValue(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);

    CDrawableObjectControl* __doc = 
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;


    if (__doc->IsExists(objTypeName+":"+__name)){
        CImageBaseClass* __obj = static_cast<CImageBaseClass*>(__doc->GetDrawableObject(objTypeName+":"+__name));

        if (__crIsBe && __cgIsBe && __cbIsBe){
            __obj->CreateActionOfColorToForSelf(
                    __inte, 
                    __cr,
                    __cg,
                    __cb,
                    __reset, 
                    __pause);
        }
        else{
            CSimultaneousOfAction* __sim = new CSimultaneousOfAction();

            if (__crIsBe)
                __sim->AddAction(__obj->CreateActionOfColorRedTo(__inte, __cr, __reset, __pause));
            
            if (__cgIsBe)
                __sim->AddAction(__obj->CreateActionOfColorGreenTo(__inte, __cg, __reset, __pause));
            
            if (__cbIsBe)
                __sim->AddAction(__obj->CreateActionOfColorBlueTo(__inte, __cb, __reset, __pause));

            __obj->AddAction(__sim);
        }
        
        return __pause ? CMD_YIELD : CMD_OK;
    }
    else
        cout << __funcName << "(): can't find "<< objTypeName <<" \""<< __name << "\"." <<endl;

    return CMD_ERR;
}


int Common_FuncOfShow(string objTypeName, lua_State* args)
{ 
    string __funcName = "Cmd_Show" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValue(args, "r", __reset);

    float __alpha = 255.0f; //alpha
    Common_GetValue(args, "a", __alpha);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    if (__doc->IsExists(objTypeName+":"+__name)){
        CDrawableClass* __obj = __doc->GetDrawableObject(objTypeName+":"+__name);

        int __layer; // layer
        if (Common_GetValue(args, "l", __layer)){
            __obj->SetLayerOrder(__layer);
        }

        float __x = __obj->GetPosition().x;
        float __y = __obj->GetPosition().y;

        float __vx;
        if (Common_GetValue(args, "x", __vx)) 
            __x = __vx; // x

        float __vy;
        if (Common_GetValue(args, "y", __vy)) 
            __y = __vy; // x
        
        __obj->CreateActionOfAlphaToForSelf(__inte, __alpha, __reset, __pause);
        __obj->SetPosition(__x, __y);
        return __pause ? CMD_YIELD : CMD_OK;
    }
    else
        cout << __funcName << "(): can't find "<< objTypeName <<" \""<< __name << "\"." <<endl;

    return CMD_ERR;
}

int Common_FuncOfHide(string objTypeName, lua_State* args)
{ 
    string __funcName = "Cmd_Hide" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValue(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);
    
    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CDrawableClass* __obj = __doc->GetDrawableObject(objTypeName+":"+__name);

    if (__obj != NULL){
        __obj->CreateActionOfAlphaToForSelf(__inte, 0.0f, __reset, __pause);
        return __pause ? CMD_YIELD : CMD_OK;
    }
    return CMD_ERR;
}

int Common_FuncOfMove(string objTypeName, lua_State* args)
{ 
    string __funcName = "Cmd_Move" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __x = 0.0f;
    bool __xIsBe = Common_GetValue(args, "x", __x);
    float __y = 0.0f;
    bool __yIsBe = Common_GetValue(args, "y", __y);

    if (!__xIsBe && !__yIsBe){
        cout << __funcName << "(): can't find x,y." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValue(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValue(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);
    
    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(__name);//Camera
    }
    else{
        CDrawableObjectControl* __doc =
            CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
            &CResourceControl::_ResourceManager._LoadingObjectControl
                :
            &CResourceControl::_ResourceManager._DrawableObjectControl;

        __obj = __doc->GetDrawableObject(objTypeName+":"+__name);
    }

    if (__obj != NULL){
        if (__xIsBe && __yIsBe){
            if (__isBy)
                __obj->CreateActionOfMoveByForSelf(__inte, __x, __y, __reset, __pause);
            else
                __obj->CreateActionOfMoveToForSelf(__inte, __x, __y, __reset, __pause);
        }
        else
        {
            if (__xIsBe)
            {
                if (__isBy)
                    __obj->CreateActionOfMoveXByForSelf(__inte, __x, __reset, __pause);
                else
                    __obj->CreateActionOfMoveXToForSelf(__inte, __x, __reset, __pause);
            }
            else
            {
                if (__isBy)
                    __obj->CreateActionOfMoveYByForSelf(__inte, __y, __reset, __pause);
                else
                    __obj->CreateActionOfMoveYToForSelf(__inte, __y, __reset, __pause);
            }
        }
        return __pause ? CMD_YIELD : CMD_OK;
    }

    return CMD_ERR;
}

int Common_FuncOfOrigin(string objTypeName, lua_State* args)
{ 
    string __funcName = "Cmd_Origin" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __x = 0.0f;
    bool __xIsBe = Common_GetValue(args, "x", __x);
    float __y = 0.0f;
    bool __yIsBe = Common_GetValue(args, "y", __y);

    if (!__xIsBe && !__yIsBe){
        cout << __funcName << "(): can't find x,y." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValue(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValue(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);
    
    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CImageBaseClass* __obj = NULL;

    __obj = static_cast<CImageBaseClass*>(__doc->GetDrawableObject(objTypeName+":"+__name));

    if (__obj != NULL){
        if (__xIsBe && __yIsBe){
            if (__isBy)
                __obj->CreateActionOfOriginByForSelf(__inte, __x, __y, __reset, __pause);
            else
                __obj->CreateActionOfOriginToForSelf(__inte, __x, __y, __reset, __pause);
        }
        else
        {
            if (__xIsBe)
            {
                if (__isBy)
                    __obj->CreateActionOfOriginXByForSelf(__inte, __x, __reset, __pause);
                else
                    __obj->CreateActionOfOriginXToForSelf(__inte, __x, __reset, __pause);
            }
            else
            {
                if (__isBy)
                    __obj->CreateActionOfOriginYByForSelf(__inte, __y, __reset, __pause);
                else
                    __obj->CreateActionOfOriginYToForSelf(__inte, __y, __reset, __pause);
            }
        }
        return __pause ? CMD_YIELD : CMD_OK;
    }

    return CMD_ERR;
}

int Common_FuncOfRotation(string objTypeName, lua_State* args)
{
    string __funcName = "Cmd_Rotation" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }
    
    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __rotation;
    if (!Common_GetValue(args, "v", __rotation))
    {
        cout << __funcName << "(): parameter \"v\" must be need." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValue(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValue(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);
    
    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(__name);//Camera
    }
    else{
        CDrawableObjectControl* __doc =
            CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
            &CResourceControl::_ResourceManager._LoadingObjectControl
                :
            &CResourceControl::_ResourceManager._DrawableObjectControl;

        __obj = __doc->GetDrawableObject(objTypeName+":"+__name);
    }

    if (__obj != NULL){
        if (__isBy)
            __obj->CreateActionOfRotationByForSelf(__inte, __rotation, __reset, __pause);
        else
            __obj->CreateActionOfRotationToForSelf(__inte, __rotation, __reset, __pause);
        return __pause ? CMD_YIELD : CMD_OK;
    }

    return CMD_ERR;
}

int Common_FuncOfScale(string objTypeName, lua_State* args)
{ 
    string __funcName = "Cmd_Scale" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValue(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValue(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);

    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        float __z;
        if (!Common_GetValue(args, "z", __z))
        {
            cout << __funcName << "(): parameter \"z\" must be need." << endl;
            return CMD_ERR;
        }

        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(__name);//Camera

        if (__obj != NULL){
            if (__isBy)
                __obj->CreateActionOfScaleXByForSelf(__inte, __z, __reset, __pause);
            else
                __obj->CreateActionOfScaleXToForSelf(__inte, __z, __reset, __pause);

            return __pause ? CMD_YIELD : CMD_OK;
        }
    }
    else{
        float __x = 0.0f;
        bool __xIsBe = Common_GetValue(args, "x", __x);
        float __y = 0.0f;
        bool __yIsBe = Common_GetValue(args, "y", __y);

        float __s = 0.0f;
        if (Common_GetValue(args, "s", __s)){
            __x = __y = __s;
            __xIsBe = __yIsBe = true;
        }

        if (!__xIsBe && !__yIsBe){
            cout << __funcName << "(): can't find x,y." << endl;
            return CMD_ERR;
        }

        CDrawableObjectControl* __doc =
            CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
            &CResourceControl::_ResourceManager._LoadingObjectControl
                :
            &CResourceControl::_ResourceManager._DrawableObjectControl;

        __obj = __doc->GetDrawableObject(objTypeName+":"+__name);

        if (__obj != NULL){
            if (__xIsBe && __yIsBe){
                if (__isBy)
                    __obj->CreateActionOfScaleByForSelf(__inte, __x, __y, __reset, __pause);
                else
                    __obj->CreateActionOfScaleToForSelf(__inte, __x, __y, __reset, __pause);
            }
            else{
                if (__xIsBe){
                    if (__isBy)
                        __obj->CreateActionOfScaleXByForSelf(__inte, __x, __reset, __pause);
                    else
                        __obj->CreateActionOfScaleXToForSelf(__inte, __x, __reset, __pause);
                }
                else{
                    if (__isBy)
                        __obj->CreateActionOfScaleYByForSelf(__inte, __y, __reset, __pause);
                    else
                        __obj->CreateActionOfScaleYToForSelf(__inte, __y, __reset, __pause);
                }

            }

            return __pause ? CMD_YIELD : CMD_OK;
        }
    }

    return CMD_ERR;
}

int Common_FuncOfLayerOrder(string objTypeName, lua_State* args)
{ 
    string __funcName = "Cmd_SetLayerOrder" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    string __layer;
    if (!Common_GetValue(args, "l", __layer))
    {
        cout << __funcName << "(): parameter \"l\" must be need." << endl;
        return CMD_ERR;
    }

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CDrawableClass* __obj = NULL;
    __obj = __doc->GetDrawableObject(objTypeName + ":" + __name);

    if (__obj){
        vector<string> __args;
        __args.push_back(__layer);
        __obj->AddAction(new CClassFuncArgsOfAction<CDrawableClass>(__obj, &CImageBaseClass::SetLayerOrder, __args));

        return CMD_OK;
    }
        
    cout << __funcName << "(): " << objTypeName << " \"" << __name << "\" has no existed." << endl;
    return CMD_ERR;
}

int Common_FuncOfFlip(string objTypeName, lua_State* args, bool flipx = true)
{
    string __funcName = (flipx ? "Cmd_FlipX" : "Cmd_FlipY") + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }
    
    if (!lua_isstring(args, 1))
    {
        cout << __funcName << "(): parameter must be string." << endl;
        return CMD_ERR;
    }

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CImgLayer* __obj = NULL;
    __obj = static_cast<CImgLayer*>(__doc->GetDrawableObject(objTypeName + ":" + lua_tostring(args, 1)));

    if (__obj){
        if (flipx)
            __obj->AddAction(new CClassFuncOfAction<CImgLayer>(__obj, &CImgLayer::FlipX));
        else
            __obj->AddAction(new CClassFuncOfAction<CImgLayer>(__obj, &CImgLayer::FlipY));

        return CMD_OK;
    }

    return CMD_ERR;
}

int Common_FuncOfScreen(lua_State* args, bool isShow)
{
    string __funcName = isShow ? "Cmd_ShowCurtain" : "Cmd_HideCurtain";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    bool __pause = false; //pause
    Common_GetValue(args, "p", __pause);

    bool __right = false; //right
    Common_GetValue(args, "r", __right);

    size_t __Type = 0; //type
    Common_GetValue(args, "t", __Type);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValue(args, "i", __inte);

    
    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CScreenEffect* __obj = NULL;
    if (__doc->IsExists("ScrEffect:screen")){
        __obj = static_cast<CScreenEffect*>(__doc->GetDrawableObject("ScrEffect:screen"));
    }
    else{
        cout << __funcName << "(): can't find ScrEffect \"screen\"." <<endl;
        return CMD_ERR;
    }

    int __layer;
    if (Common_GetValue(args, "l", __layer))
        __obj->SetLayerOrder(__layer);

    switch (__Type)
    {
        case 1:
            __obj->CreateActionGradientForSelf(__inte, isShow, __right, __pause);
            break;
        case 2:
            __obj->CreateActionLouverForSelf(__inte, isShow, __right, false, __pause);
            break;
        case 3:
            __obj->CreateActionLouverForSelf(__inte, isShow, __right, true, __pause);
            break;
        default:
            __obj->CreateActionShowOrHideForSelf(__inte, isShow, __pause);
            break;
    }

    return __pause ? CMD_YIELD : CMD_OK;
}

//int Cmd_FuncOfActionForDeleteOrSkip(string funcName, lua_State* args, bool skip)
//{
//    CActionSet& act = &CResourceControl::_ResourceManager._ActionControl;
//
//    if (act == NULL){
//        cout << funcName << "(): action set is null." <<endl;
//        return CMD_ERR;
//    }
//    
//    for (size_t i=0; i<args.size(); i++){
//        act->DeleteAct(args[i], skip);
//    }
//
//    return CMD_OK;
//}

/*==============================================================
    commad of script
===============================================================*/

int Cmd_ShowCharacterLayer(lua_State* args)
{
    if (Common_FuncOfShow("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_MoveCharacterLayer(lua_State* args)
{
    if (Common_FuncOfMove("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ScaleCharacterLayer(lua_State* args)
{
    if (Common_FuncOfScale("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_RotationCharacterLayer(lua_State* args)
{
    if (Common_FuncOfRotation("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_HideCharacterLayer(lua_State* args)
{
    if (Common_FuncOfHide("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_SetPoseCharacterLayer(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_SetPoseCharacterLayer(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    string __name;
    if (!Common_GetValue(args, "n", __name))
    {
        cout << "Cmd_SetPoseCharacterLayer(): parameter \"n\" must be need." << endl;
        return 0;
    }
    
    string __body = "";
    Common_GetValue(args, "b", __body);

    string __eye = "";
    Common_GetValue(args, "e", __eye);

    string __mouth = "";
    Common_GetValue(args, "m", __mouth);

    string __skip = "";
    Common_GetValue(args, "s", __skip);

    vector<string> __args;
    __args.push_back(__body);
    __args.push_back(__eye);
    __args.push_back(__mouth);
    __args.push_back(__skip);
    
    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    if (!__doc->IsExists("CharacterLayer:"+__name)){
        cout << "Cmd_SetPoseCharacterLayer(): can't find character layer \""<< __name << "\"." <<endl;
        return 0;
    }

    CCharacterLayer* __chara = static_cast<CCharacterLayer*>(__doc->GetDrawableObject("CharacterLayer:"+__name));

    __chara->AddAction(new CClassFuncArgsOfAction<CCharacterLayer>(__chara, &CCharacterLayer::SetPose, __args));
        
    return 0;
}

int Cmd_SetCharacterLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_FlipXCharacterLayer(lua_State* args)
{
    if (Common_FuncOfFlip("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_FlipYCharacterLayer(lua_State* args)
{
    if (Common_FuncOfFlip("CharacterLayer", args, false) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_OriginCharacterLayer(lua_State* args)
{
    if (Common_FuncOfOrigin("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ColorCharacterLayer(lua_State* args)
{
    if (Common_FuncOfColor("CharacterLayer", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

//===========================================
//
//===========================================

/*
    Cmd_AddImg: comand of add image.
    args[0]: set image name.
    args[1]: set image path.
    args[2]: set image postion of x.
    args[3]: set image postion of y.
*/
//int Cmd_AddImg(lua_State* args)
//{
//    return Common_FuncOfAdd("Img", args);
//}

int Cmd_ShowImg(lua_State* args)
{
    if (Common_FuncOfShow("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_HideImg(lua_State* args)
{
    if (Common_FuncOfHide("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_MoveImg(lua_State* args)
{
    if (Common_FuncOfMove("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ScaleImg(lua_State* args)
{
    if (Common_FuncOfScale("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_RotationImg(lua_State* args)
{
    if (Common_FuncOfRotation("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_SetImgLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_FlipXImg(lua_State* args)
{
    if (Common_FuncOfFlip("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_FlipYImg(lua_State* args)
{
    if (Common_FuncOfFlip("Img", args, false) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_OriginImg(lua_State* args)
{
    if (Common_FuncOfOrigin("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ColorImg(lua_State* args)
{
    if (Common_FuncOfColor("Img", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ShowText(lua_State* args)
{
    if (Common_FuncOfShow("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_HideText(lua_State* args)
{
    if (Common_FuncOfHide("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_MoveText(lua_State* args)
{
    if (Common_FuncOfMove("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ScaleText(lua_State* args)
{
    if (Common_FuncOfScale("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_RotationText(lua_State* args)
{
    if (Common_FuncOfRotation("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_SetTextLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_OriginText(lua_State* args)
{
    if (Common_FuncOfOrigin("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ColorText(lua_State* args)
{
    if (Common_FuncOfColor("Text", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_SetText(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_SetText(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    string __name;//name
    if (!Common_GetValue(args, "n", __name))
    {
        cout << "Cmd_SetText(): parameter \"n\" must be need." << endl;
        return 0;
    }

    string __font = "";//font
    Common_GetValue(args, "f", __font);

    size_t __size = 0;//size
    Common_GetValue(args, "s", __size);

    string __text = "";//text
    bool _isBeT = Common_GetValue(args, "t", __text);

    bool __shadow = "";//shadow
    Common_GetValue(args, "h", __shadow);

    float __shadowpercent = -1.0f;//shadowpercent
    Common_GetValue(args, "c", __shadowpercent);

    string __colorRed = "";//color red
    Common_GetValue(args, "cr", __colorRed);

    string __colorGreen = "";//color green
    Common_GetValue(args, "cg", __colorGreen);

    string __colorBlue = "";//color blue
    Common_GetValue(args, "cb", __colorBlue);

    string __styleRegular = "";//style regular
    Common_GetValue(args, "sr", __styleRegular);

    string __styleBold = "";//style bold
    Common_GetValue(args, "sb", __styleBold);

    string __styleItalic = "";//style italic
    Common_GetValue(args, "si", __styleItalic);

    string __styleUnderlined = "";//style underlined
    Common_GetValue(args, "su", __styleUnderlined);

    string __styleStrikeThrough = "";//style strikeThrough
    Common_GetValue(args, "ss", __styleStrikeThrough);

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::STOP ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    if (!__doc->IsExists("Text:"+__name)){
        cout << "Cmd_SetText(): can't find text \""<< __name << "\"." <<endl;
        return 0;
    }
    
    CText* __txt = static_cast<CText*>(__doc->GetDrawableObject("Text:"+__name));
    
    __txt->SetShadowEnable(__shadow);

    if (!(__shadowpercent < 0.0f)){
        __txt->SetShadowPercent(__shadowpercent);
    }

    if (__font != ""){
        __txt->SetFont(__font);
    }

    if (__size > 0){
        __txt->SetCharacterSize(__size);
    }
    
    if (_isBeT){
        __txt->SetString(__text);
    }
    
    if (__colorRed != "" ||
        __colorGreen != "" ||
        __colorBlue != ""){
        
        sf::Color __color = __txt->GetColor();
        
        if (__colorRed != ""){
            __color.r = atoi(__colorRed.c_str());
        }

        if (__colorGreen != ""){
            __color.g = atoi(__colorGreen.c_str());
        }

        if (__colorBlue != ""){
            __color.b = atoi(__colorBlue.c_str());
        }

        __txt->SetColor(__color.r, __color.g, __color.b);
    }

    vector<string> __args;
    if (__styleRegular != "" ||
        __styleBold != "" ||
        __styleItalic != "" ||
        __styleUnderlined != "" ||
        __styleStrikeThrough != "")
    {        
        if (__styleRegular != ""){
            __args.push_back("-sr");
            __txt->SetStyle(__args);
        }else{
            if (__styleBold != "")
                __args.push_back("-sb");

            if (__styleItalic != "")
                __args.push_back("-si");

            if (__styleUnderlined != "")
                __args.push_back("-su");

            if (__styleStrikeThrough != "")
                __args.push_back("-ss");

            __txt->SetStyle(__args);
        }
    }

    return 0;
}

int Cmd_PlayBGM(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_PlayBGM(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    string __name;//name
    if (!Common_GetValue(args, "n", __name))
    {
        cout << "Cmd_PlayBGM(): parameter \"n\" must be need." << endl;
        return 0;
    }

    float __vol = 1.0f;
    Common_GetValue(args, "v", __vol);

    bool __loop = false;
    Common_GetValue(args, "l", __loop);

    CResourceControl::_ResourceManager._SoundControl.PlayBgm(__name, __vol, __loop);
    return 0;
}

int Cmd_SetBGMVolume(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_SetBGMVolume(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    float __vol = 1.0f;//vol
    if (!Common_GetValue(args, "v", __vol))
    {
        cout << "Cmd_SetBGMVolume(): parameter \"v\" must be need." << endl;
        return 0;
    }

    size_t __inte = CCommon::_Common.INTERVAL;//incr
    Common_GetValue(args, "i", __inte);

    bool __isBy = false;// isBy
    Common_GetValue(args, "b", __isBy);

    bool __pause = false;//pause
    Common_GetValue(args, "p", __pause);

    bool __reset = false;//reset
    Common_GetValue(args, "r", __reset);

    if (__isBy)
        CResourceControl::_ResourceManager._ActionControl.AddAction(
            CResourceControl::_ResourceManager._SoundControl.CreateActionOfMusicVolBy(
                __inte, __vol, __reset, __pause));
    else
        CResourceControl::_ResourceManager._ActionControl.AddAction(
            CResourceControl::_ResourceManager._SoundControl.CreateActionOfMusicVolTo(
                __inte, __vol, __reset, __pause));

    if (__pause)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_PauseBGM(lua_State* args)
{
    CResourceControl::_ResourceManager._SoundControl.PauseBgm();
    return 0;
}

int Cmd_ResumeBGM(lua_State* args)
{
    CResourceControl::_ResourceManager._SoundControl.PlayBgm();
    return 0;
}

int Cmd_StopBGM(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_StopBGM(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    size_t __inte = 0;//incr
    Common_GetValue(args, "i", __inte);

    bool __pause = 0;//pause
    Common_GetValue(args, "p", __pause);

    CSequenceOfAction* __seq = new CSequenceOfAction();
    __seq->AddAction(CResourceControl::_ResourceManager._SoundControl.CreateActionOfMusicVolTo(__inte, 0.0f, false, __pause));
    __seq->AddAction(new CClassFuncOfAction<CSoundBank>(
        &CResourceControl::_ResourceManager._SoundControl, &CSoundBank::StopBgm));
    
    CResourceControl::_ResourceManager._ActionControl.AddAction(__seq);

    if (__pause)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_StopSE(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_StopSE(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }
    
    vector<string> __args;
    if (!Common_GetValue(args, "n", __args))
    {
        cout << "Cmd_StopSE(): parameter \"n\" must be need." << endl;
        return 0;
    }

    for (size_t i = 0; i < __args.size(); i++)
    {
        CResourceControl::_ResourceManager._SoundControl.StopSE(__args[i]);
    }

    return 0;
}

int Cmd_PlaySE(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_PlaySE(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    string __name;//name
    if (!Common_GetValue(args, "n", __name))
    {
        cout << "Cmd_SetBGMVolume(): parameter \"n\" must be need." << endl;
        return 0;
    }

    float __vol = 1.0f;//vol
    Common_GetValue(args, "v", __vol);

    bool __loop = false; //loop
    Common_GetValue(args, "l", __loop);

    CResourceControl::_ResourceManager._SoundControl.PlaySE(__name, __vol, __loop);

    return 0;

    //cout << "Cmd_PlaySE(): can't find SE \""<< _name << "\"." << endl;
    //return CMD_ERR;
}

int Cmd_ShowButton(lua_State* args)
{
    if (Common_FuncOfShow("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_HideButton(lua_State* args)
{
    if (Common_FuncOfHide("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_MoveButton(lua_State* args)
{
    if (Common_FuncOfMove("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ScaleButton(lua_State* args)
{
    if (Common_FuncOfScale("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_RotationButton(lua_State* args)
{
    if (Common_FuncOfRotation("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_SetButtonLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_FlipXButton(lua_State* args)
{
    if (Common_FuncOfFlip("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_FlipYButton(lua_State* args)
{
    if (Common_FuncOfFlip("Button", args, false) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_OriginButton(lua_State* args)
{
    if (Common_FuncOfOrigin("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ColorButton(lua_State* args)
{
    if (Common_FuncOfColor("Button", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}
//
//
//void  Cmd_FullScreen()
//{
//    SDL_Event e;
//    e.key.type = SDL_KEYDOWN;
//    e.key.state = SDL_PRESSED;
//    e.key.keysym.sym = SDLK_F4;
//    SDL_PushEvent(&e);
//}
//
//void  Cmd_Window()
//{
//    SDL_Event e;
//    e.key.type = SDL_KEYDOWN;
//    e.key.state = SDL_PRESSED;
//    e.key.keysym.sym = SDLK_F5;
//    SDL_PushEvent(&e);
//}
//

int Cmd_Message(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_Message(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    string __msgBoxName;//MessageBoxName
    if (!Common_GetValue(args, "n", __msgBoxName))
    {
        cout << "Cmd_Message(): parameter \"n\" must be need." << endl;
        return 0;
    }

    string __msg;//message
    if (!Common_GetValue(args, "m", __msg))
    {
        cout << "Cmd_Message(): parameter \"m\" must be need." << endl;
        return 0;
    }

    string __speakerName = "";
    Common_GetValue(args, "s", __speakerName);

    string __voiceName = "";
    Common_GetValue(args, "v", __voiceName);

    vector<string> __cOfArg;
    Common_GetValue(args, "c", __cOfArg);

    CDrawableClass* __obj = 
        CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("MessageBox:"+__msgBoxName);

    if(__obj == NULL){
        cout << "Cmd_Message(): MessageBox \"" << __msgBoxName << "\" has no existed." <<endl;
        return 0;
    }

    CMessageBox* __msgbox = static_cast<CMessageBox*>(__obj);
    CSimultaneousOfAction* __sim = new CSimultaneousOfAction();
    vector<string> __args;

    if (__cOfArg.size() != 0){
        for (size_t i = 0; i < __cOfArg.size(); i++){
            if (__cOfArg[i] != ""){
                __obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("CharacterLayer:" + __cOfArg[i]);
                if(__obj == NULL)
                    cout << "Cmd_Message(): CharacterLayer \"" << __cOfArg[i] << "\" has no existed." << endl;
                else{
                    CCharacterLayer* __chara = static_cast<CCharacterLayer*>(__obj);
                    __args.push_back(__voiceName);
                    __sim->AddAction(new CClassFuncArgsOfAction<CCharacterLayer>(__chara, &CCharacterLayer::SetVoice, __args));
                }
            }
        }
    }
    
    __args.clear();
    __args.push_back(__msg);
    __sim->AddAction(new CClassFuncArgsOfAction<CMessageBox>(__msgbox, &CMessageBox::SetText, __args));

    __args.clear();
    __args.push_back(__speakerName);
    __sim->AddAction(new CClassFuncArgsOfAction<CMessageBox>(__msgbox, &CMessageBox::SetSpeakerName, __args));

    if (__voiceName != ""){
        __args.clear();
        __args.push_back(__voiceName);
        __sim->AddAction(new CClassFuncArgsOfAction<CSoundBank>(
            &CResourceControl::_ResourceManager._SoundControl, &CSoundBank::PlayVoice, __args));
    }

    __msgbox->AddAction(__sim);
    lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ShowMessageBox(lua_State* args)
{   
    if (Common_FuncOfShow("MessageBox", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_HideMessageBox(lua_State* args)
{
    if (Common_FuncOfHide("MessageBox", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_SetMessageBoxLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("MessageBox", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_CleanMessageBox(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << "Cmd_CleanMessageBox(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    string __msgBoxName;//MessageBoxName
    if (!Common_GetValue(args, "n", __msgBoxName))
    {
        cout << "Cmd_CleanMessageBox(): parameter \"n\" must be need." << endl;
        return 0;
    }
    
    CDrawableClass* __obj = 
        CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("MessageBox:" + __msgBoxName);

    if(__obj == NULL){
        cout << "Cmd_CleanMessageBox(): MessageBox \"" << __msgBoxName << "\" has no existed." << endl;
        return 0;
    }
    
    CMessageBox* __msgbox = static_cast<CMessageBox*>(__obj);

    __msgbox->ClearText();
    return 0;
}

int Cmd_ShowLogBox(lua_State* args)
{
    if (Common_FuncOfShow("LogBox", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_HideLogBox(lua_State* args)
{
    if (Common_FuncOfHide("LogBox", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_SetLogBoxLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("LogBox", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

//int Cmd_ShowParticleSystem(lua_State* args)
//{
//    bool CResourceControl::_ResourceManager.IsLoadingProcessRunning() = args[0] == "q(-_-)p";
//    args.erase(args.begin());
//
//    if (args.size() < 1){
//        cout << "Cmd_ShowParticleSystem(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return CMD_ERR;
//    }
//    
//    CDrawableObjectControl* __doc = CResourceControl::_ResourceManager.IsLoadingProcessRunning() ? 
//        &CResourceControl::_ResourceManager._LoadingObjectControl
//            :
//        &CResourceControl::_ResourceManager._DrawableObjectControl;
//
//    for (size_t i=0; i<args.size(); i++){
//        if (!__doc->IsExists("ParticleSystem:"+args[i])){
//            cout << "Cmd_ShowParticleSystem(): can't find ParticleSystem \"" << args[i] << "\"." <<endl;
//        }
//        else{
//            CParticleSystem* __par = static_cast<CParticleSystem*>(__doc->GetDrawableObject("ParticleSystem:"+args[i]));
//            
//            if (__par->GetEnable())
//                cout << "Cmd_ShowParticleSystem(): ParticleSystem \"" << args[i] << "\" has showed." << endl;
//            else
//                __par->SetEnable(true);
//        }
//    }
//
//    return CMD_OK;
//}
//
//int Cmd_HideParticleSystem(lua_State* args)
//{
//    bool CResourceControl::_ResourceManager.IsLoadingProcessRunning() = args[0] == "q(-_-)p";
//    args.erase(args.begin());
//
//    if (args.size() < 1){
//        cout << "Cmd_HideParticleSystem(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return CMD_ERR;
//    }
//
//    CDrawableObjectControl* __doc = CResourceControl::_ResourceManager.IsLoadingProcessRunning() ? 
//        &CResourceControl::_ResourceManager._LoadingObjectControl
//            :
//        &CResourceControl::_ResourceManager._DrawableObjectControl;
//    
//    for (size_t i=0; i<args.size(); i++){
//        if (!__doc->IsExists("ParticleSystem:"+args[i])){
//            cout << "Cmd_ShowParticleSystem(): can't find ParticleSystem \"" << args[i] << "\"." <<endl;
//        }
//        else{
//            CParticleSystem* __par = static_cast<CParticleSystem*>(__doc->GetDrawableObject(args[i]));
//            
//            if (__par->GetEnable())
//                cout << "Cmd_ShowParticleSystem(): ParticleSystem \"" << args[i] << "\" has showed." << endl;
//            else
//                __par->SetEnable(false);
//        }
//    }
//
//    return CMD_OK;
//}
//
//int Cmd_SetParticleSystemLayerOrder(lua_State* args)
//{
//    return Common_FuncOfLayerOrder("ParticleSystem", args);
//}
//
//int Cmd_AddVariable(lua_State* args)
//{
//    args.erase(args.begin());
//    if (args.size() != 2){
//        cout << "Cmd_AddVariable(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return CMD_ERR;
//    }
//
//    string __name = args[0];
//    string __val = args[1];
//    __name = "$" + __name;
//    
//    return CResourceControl::_ResourceManager.AddVariable(__name, __val);
//}

//int Cmd_SetVariable(lua_State* args)
//{
//    args.erase(args.begin());
//    if (args.size() != 2){
//        cout << "Cmd_SetVariable(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return CMD_ERR;
//    }
//
//    string __name = args[0];
//    string __val = args[1];
//    __name = "$" + __name;
//    
//    return CResourceControl::_ResourceManager.SetVariable(__name, __val);
//}
//
//int Cmd_DelVariable(lua_State* args)
//{
//    args.erase(args.begin());
//    if (args.size() < 1){
//        cout << "Cmd_DelVariable(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return CMD_ERR;
//    }
//
//    for (size_t i=0; i<args.size(); i++){
//        CResourceControl::_ResourceManager.DelVariable("$"+args[i]);
//    }
//
//    return CMD_OK;
//}

//int Cmd_DelAction(lua_State* args)
//{
//    return Cmd_FuncOfActionForDeleteOrSkip("Cmd_DelAction", args, act, false);
//}
//
//int Cmd_SkipAction(lua_State* args)
//{
//    return Cmd_FuncOfActionForDeleteOrSkip("Cmd_SkipAction", args, act, true);
//}

int Cmd_ShowCurtain(lua_State* args)
{
    if (Common_FuncOfScreen(args, true) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_HideCurtain(lua_State* args)
{
    if (Common_FuncOfScreen(args, false) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ColorCurtain(lua_State* args)
{
    if (Common_FuncOfColor("ScrEffect", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_UseCamera(lua_State* args)
{
    int __numOfargs = lua_gettop(args);
    if (__numOfargs == 0){
        CResourceControl::_ResourceManager._CameraControl.UseDefaultCamera();
    }
    else{
        string __name = "";// Name
        Common_GetValue(args, "n", __name);
        CResourceControl::_ResourceManager._CameraControl.UseCamera(__name);
    }
    return 0;
}

int Cmd_MoveCamera(lua_State* args)
{
    if (Common_FuncOfMove("Camera", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_ScaleCamera(lua_State* args)
{
    if (Common_FuncOfScale("Camera", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

int Cmd_RotationCamera(lua_State* args)
{
    if (Common_FuncOfRotation("Camera", args) == CMD_YIELD)
        lua_yieldk(args, 0, 0, Common_YieldCont);

    return 0;
}

//int Cmd_Pause(lua_State* args)
//{
//    if (act == NULL){
//        cout << "Cmd_Pause(): action set is null." <<endl;
//        return CMD_ERR;
//    }
//
//    act->AddAction(new CClassFuncOfAction<CResourceControl>(&CResourceControl::_ResourceManager, &CResourceControl::PauseForUserConfrim));
//    return CMD_OK;
//}

int Cmd_LoadScript(lua_State* args)
{
    //if (act == NULL){
    //    cout << "Cmd_LoadScript(): action set is null." <<endl;
    //    return CMD_ERR;
    //}

    //if (args.size() < 1){
    //    cout << "Cmd_LoadScript(): command invaild. can't set " << args.size()
    //        << " argument(s) in the command." <<endl;
    //    return CMD_ERR;
    //}

    //act->AddAction(new CClassFuncArgsOfAction<CResourceControl>(&CResourceControl::_ResourceManager, &CResourceControl::LoadScript, args));
    return CMD_OK;
}
