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
#include "../Action/CRepeatOfAction.h"
#include "../Action/CFuncArgsOfAction.h"

string func_name = "";

int Common_YieldCont(lua_State *L, int, lua_KContext ctx)
{
    cout << func_name << "(): resume thread." << endl;
    return 0;
}

int Common_RetrunYield(lua_State *L, string funcname)
{
    func_name = funcname;
    cout << funcname << "(): suspends thread." << endl;
    return lua_yieldk(L, 0, 0, Common_YieldCont);
}

//for mutex
//int Common_RetrunYield(string funcname)
//{
//    cout << funcname << "(): suspends thread." << endl;
//    CResourceControl::_ResourceManager.LockMutexInLua();
//    cout << funcname << "(): resume thread." << endl;
//    return 0;
//}

bool Common_GetValue(lua_State* L, string& val)
{
    if (lua_isstring(L, -1)){
        val = lua_tostring(L, -1);
        lua_pop(L, 1);
        return true;
    }

    return false;
}

bool Common_GetValue(lua_State* L, int& val)
{
    if (lua_isnumber(L, -1)){
        val = lua_tonumber(L, -1);
        lua_pop(L, 1);
        return true;
    }

    return false;
}

bool Common_GetValue(lua_State* L, size_t& val)
{
    if (lua_isnumber(L, -1)){
        val = lua_tonumber(L, -1);
        lua_pop(L, 1);
        return true;
    }

    return false;
}

bool Common_GetValue(lua_State* L, float& val)
{
    if (lua_isnumber(L, -1)){
        val = lua_tonumber(L, -1);
        lua_pop(L, 1);
        return true;
    }

    return false;
}

bool Common_GetValue(lua_State* L, bool& val)
{
    if (lua_isboolean(L, -1)){
        val = lua_toboolean(L, -1);
        lua_pop(L, 1);
        return true;
    }

    return false;
}

bool Common_GetValueInTable(lua_State* L, const char* fieldName, int& val)
{
    if (lua_istable(L, -1)){
        if (lua_getfield(L, -1, fieldName) == LUA_TNUMBER) {
            val = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValueInTable(lua_State* L, const char* fieldName, size_t& val)
{
    if (lua_istable(L, -1)){
        if (lua_getfield(L, -1, fieldName) == LUA_TNUMBER) {
            val = lua_tonumber(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValueInTable(lua_State* L, const char* fieldName, string& val)
{
    if (lua_istable(L, -1)){
        if (lua_getfield(L, -1, fieldName) == LUA_TSTRING) {
            val = lua_tostring(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValueInTable(lua_State* L, const char* fieldName, bool& val)
{
    if (lua_istable(L, -1)){
        if (lua_getfield(L, -1, fieldName) == LUA_TBOOLEAN) {
            val = lua_toboolean(L, -1);
            lua_pop(L, 1);
            return true;
        }

        lua_pop(L, 1);
    }

    return false;
}

bool Common_GetValueInTable(lua_State* L, const char* fieldName, float& val)
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

bool Common_GetValueInTable(lua_State* L, const char* fieldName, vector<string>& val)
{
    if (lua_istable(L, -1)){
        if (lua_getfield(L, -1, fieldName) == LUA_TTABLE){
            int __index = 1;
            while (lua_rawgeti(L, -1, __index)){
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

CActionBaseClass* Common_GetResumeIntoActset(CActionBaseClass* act)
{
    CSequenceOfAction* __seq = new CSequenceOfAction();
    __seq->AddAction(act);

    // for Mutex
    //__seq->AddAction(new CClassFuncOfAction<CResourceControl, void>(
    //    &CResourceControl::_ResourceManager,
    //    &CResourceControl::UnlockMutexInMain));

    __seq->AddAction(new CClassFuncOfAction<CLua, int>(
        &CResourceControl::_ResourceManager._LuaControl,
        &CLua::ResumeLuaThread));

    return __seq;
}

int Common_AddAction(lua_State* args, char flag, string funcname)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs != 1){
            cout << funcname << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;

            lua_pushboolean(args, false);
            return 1;
        }
    }

    if (lua_isnil(args, 1)){
        cout << funcname << "(): argument(s) is nil. " << endl;
        lua_pushboolean(args, false);
        return 1;
    }

    CActionBaseClass* __act = (CActionBaseClass*)lua_topointer(args, 1);

    if (__act){
        switch (flag){
            case 0:
                CResourceControl::_ResourceManager._ActionControl.AddAction(__act);
                break;
            case 1:
                CResourceControl::_ResourceManager._ActForLoadingBegin.AddAction(__act);
                CActionBaseClass::ClearListOfActions(__act);
                break;
            case 2:
                CResourceControl::_ResourceManager._ActForLoadingFinish.AddAction(__act);
                CActionBaseClass::ClearListOfActions(__act);
                break;
        }
        lua_pushboolean(args, true);
    }
    else
        lua_pushboolean(args, false);

    return 1;
}

enum
{
    CMD_ERR = -1,
    CMD_OK,
    CMD_YIELD
};

int Common_FuncOfColor(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{ 
    string __funcName = isCreateAction ? 
        "Cmd_CreateActionForColor" + objTypeName : "Cmd_Color" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    float __cr = 0.0f;
    bool __crIsBe = Common_GetValueInTable(args, "cr", __cr);
    float __cg = 0.0f;
    bool __cgIsBe = Common_GetValueInTable(args, "cg", __cg);
    float __cb = 0.0f;
    bool __cbIsBe = Common_GetValueInTable(args, "cb", __cb);

    if (!__crIsBe && !__cgIsBe && !__cbIsBe)
        return CMD_ERR;

    string __name = "";
    if (objTypeName != "ScrEffect")
    {

        if (!Common_GetValueInTable(args, "n", __name))
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
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValueInTable(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;


    if (__doc->IsExists(objTypeName+":"+__name)){
        CImageBaseClass* __obj = static_cast<CImageBaseClass*>(__doc->GetDrawableObject(objTypeName + ":" + __name));
        CSimultaneousOfAction* __sim = new CSimultaneousOfAction();

        if (__crIsBe && __cgIsBe && __cbIsBe){
            __sim->AddAction(__obj->CreateActionOfColorTo(
                    __inte, 
                    __cr,
                    __cg,
                    __cb,
                    __reset));
        }
        else{
            if (__crIsBe)
                __sim->AddAction(__obj->CreateActionOfColorRedTo(__inte, __cr, __reset));
            
            if (__cgIsBe)
                __sim->AddAction(__obj->CreateActionOfColorGreenTo(__inte, __cg, __reset));
            
            if (__cbIsBe)
                __sim->AddAction(__obj->CreateActionOfColorBlueTo(__inte, __cb, __reset));
        }

        CActionBaseClass* __result = __sim;

        if (isCreateAction)
            *act = __result;
        else{
            if (__pause)
                __result = Common_GetResumeIntoActset(__sim);
            
            __obj->AddAction(__result);
        }
        
        return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
    }
    else
        cout << __funcName << "(): can't find "<< objTypeName <<" \""<< __name << "\"." <<endl;

    return CMD_ERR;
}


int Common_FuncOfShow(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{ 
    string __funcName = isCreateAction ? 
        "Cmd_CreateActionForShow" + objTypeName : "Cmd_Show" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    bool __pause = false; //pause
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValueInTable(args, "r", __reset);

    float __alpha = 255.0f; //alpha
    Common_GetValueInTable(args, "a", __alpha);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    if (__doc->IsExists(objTypeName+":"+__name)){
        CDrawableClass* __obj = __doc->GetDrawableObject(objTypeName + ":" + __name);
        CSimultaneousOfAction* __sim = new CSimultaneousOfAction();

        int __layer; // layer
        if (Common_GetValueInTable(args, "l", __layer)){
            __sim->AddAction(new CClassFuncArgsOfAction<CDrawableClass, char, void>(__obj, &CDrawableClass::SetLayerOrder, (char)__layer));
        }

        float __x = __obj->GetPosition().x;
        float __y = __obj->GetPosition().y;

        float __vx;
        if (Common_GetValueInTable(args, "x", __vx)) 
            __x = __vx; // x

        float __vy;
        if (Common_GetValueInTable(args, "y", __vy)) 
            __y = __vy; // x

        vector<float> __args;
        __args.push_back(__x);
        __args.push_back(__y);
        __sim->AddAction(new CClassFuncArgsOfAction<CDrawableClass, typename vector<float>, void>(__obj, &CDrawableClass::SetPosition, __args));
        __sim->AddAction(__obj->CreateActionOfAlphaTo(__inte, __alpha, __reset));

        CActionBaseClass* __result = __sim;

        if (isCreateAction)
            *act = __result;
        else{
            if (__pause)
                __result = Common_GetResumeIntoActset(__sim);

            __obj->AddAction(__result);
        }

        return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
    }
    else
        cout << __funcName << "(): can't find "<< objTypeName <<" \""<< __name << "\"." <<endl;

    return CMD_ERR;
}

int Common_FuncOfHide(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{ 
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForHide" + objTypeName : "Cmd_Hide" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    bool __pause = false; //pause
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValueInTable(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);
    
    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CDrawableClass* __obj = __doc->GetDrawableObject(objTypeName+":"+__name);

    if (__obj != NULL){
        CActionBaseClass* __result = __obj->CreateActionOfAlphaTo(__inte, 0.0f, __reset);

        if (isCreateAction)
            *act = __result;
        else{
            if (__pause)
                __result = Common_GetResumeIntoActset(__result);

            __obj->AddAction(__result);
        }

        return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
    }
    return CMD_ERR;
}

int Common_FuncOfMove(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{ 
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForMove" + objTypeName : "Cmd_Move" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __x = 0.0f;
    bool __xIsBe = Common_GetValueInTable(args, "x", __x);
    float __y = 0.0f;
    bool __yIsBe = Common_GetValueInTable(args, "y", __y);

    if (!__xIsBe && !__yIsBe){
        cout << __funcName << "(): can't find x,y." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValueInTable(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValueInTable(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);
    
    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(__name);//Camera
    }
    else{
        CDrawableObjectControl* __doc =
            CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
            &CResourceControl::_ResourceManager._LoadingObjectControl
                :
            &CResourceControl::_ResourceManager._DrawableObjectControl;

        __obj = __doc->GetDrawableObject(objTypeName+":"+__name);
    }

    if (__obj != NULL){
        CActionBaseClass* __result = NULL;
        if (__xIsBe && __yIsBe){
            if (__isBy)
                __result = __obj->CreateActionOfMoveBy(__inte, __x, __y, __reset);
            else
                __result = __obj->CreateActionOfMoveTo(__inte, __x, __y, __reset);
        }
        else{
            if (__xIsBe){
                if (__isBy)
                    __result = __obj->CreateActionOfMoveXBy(__inte, __x, __reset);
                else
                    __result = __obj->CreateActionOfMoveXTo(__inte, __x, __reset);
            }
            else{
                if (__isBy)
                    __result = __obj->CreateActionOfMoveYBy(__inte, __y, __reset);
                else
                    __result = __obj->CreateActionOfMoveYTo(__inte, __y, __reset);
            }
        }

        if (isCreateAction)
            *act = __result;
        else{
            if (__pause)
                __result = Common_GetResumeIntoActset(__result);

            __obj->AddAction(__result);
        }

        return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
    }

    return CMD_ERR;
}

int Common_FuncOfOrigin(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{ 
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForOrigin" + objTypeName : "Cmd_Origin" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __x = 0.0f;
    bool __xIsBe = Common_GetValueInTable(args, "x", __x);
    float __y = 0.0f;
    bool __yIsBe = Common_GetValueInTable(args, "y", __y);

    if (!__xIsBe && !__yIsBe){
        cout << __funcName << "(): can't find x,y." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValueInTable(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValueInTable(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);
    
    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CImageBaseClass* __obj = NULL;

    __obj = static_cast<CImageBaseClass*>(__doc->GetDrawableObject(objTypeName+":"+__name));
    if (__obj != NULL){
        CActionBaseClass* __result = NULL;
        if (__xIsBe && __yIsBe){
            if (__isBy)
                __result = __obj->CreateActionOfOriginBy(__inte, __x, __y, __reset);
            else
                __result = __obj->CreateActionOfOriginTo(__inte, __x, __y, __reset);
        }
        else{
            if (__xIsBe){
                if (__isBy)
                    __result = __obj->CreateActionOfOriginXBy(__inte, __x, __reset);
                else
                    __result = __obj->CreateActionOfOriginXTo(__inte, __x, __reset);
            }
            else{
                if (__isBy)
                    __result = __obj->CreateActionOfOriginYBy(__inte, __y, __reset);
                else
                    __result = __obj->CreateActionOfOriginYTo(__inte, __y, __reset);
            }
        }

        if (isCreateAction)
            *act = __result;
        else{
            if (__pause)
                __result = Common_GetResumeIntoActset(__result);

            __obj->AddAction(__result);
        }

        return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
    }

    return CMD_ERR;
}

int Common_FuncOfRotation(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForRotation" + objTypeName : "Cmd_Rotation" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }
    
    string __name;
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __rotation;
    if (!Common_GetValueInTable(args, "v", __rotation))
    {
        cout << __funcName << "(): parameter \"v\" must be need." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValueInTable(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValueInTable(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);
    
    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(__name);//Camera
    }
    else{
        CDrawableObjectControl* __doc =
            CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
            &CResourceControl::_ResourceManager._LoadingObjectControl
                :
            &CResourceControl::_ResourceManager._DrawableObjectControl;

        __obj = __doc->GetDrawableObject(objTypeName+":"+__name);
    }

    if (__obj != NULL){
        CActionBaseClass* __result = NULL;
        if (__isBy)
            __result = __obj->CreateActionOfRotationBy(__inte, __rotation, __reset);
        else
            __result = __obj->CreateActionOfRotationTo(__inte, __rotation, __reset);
        

        if (isCreateAction)
            *act = __result;
        else{
            if (__pause)
                __result = Common_GetResumeIntoActset(__result);

            __obj->AddAction(__result);
        }

        return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
    }

    return CMD_ERR;
}

int Common_FuncOfScale(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForScale" + objTypeName : "Cmd_Scale" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    bool __isBy = false; //isBy
    Common_GetValueInTable(args, "b", __isBy);

    bool __pause = false; //pause
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false; //reset
    Common_GetValueInTable(args, "r", __reset);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);

    CBaiscProperties* __obj = NULL;
    CActionBaseClass* __result = NULL;

    if (objTypeName == "Camera"){
        float __z;
        if (!Common_GetValueInTable(args, "z", __z))
        {
            cout << __funcName << "(): parameter \"z\" must be need." << endl;
            return CMD_ERR;
        }

        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(__name);//Camera

        if (__obj != NULL){
            if (__isBy)
                __result = __obj->CreateActionOfScaleXBy(__inte, __z, __reset);
            else
                __result = __obj->CreateActionOfScaleXTo(__inte, __z, __reset);

            if (isCreateAction)
                *act = __result;
            else{
                if (__pause)
                    __result = Common_GetResumeIntoActset(__result);

                __obj->AddAction(__result);
            }

            return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
        }
    }
    else{
        float __x = 0.0f;
        bool __xIsBe = Common_GetValueInTable(args, "x", __x);
        float __y = 0.0f;
        bool __yIsBe = Common_GetValueInTable(args, "y", __y);

        float __s = 0.0f;
        if (Common_GetValueInTable(args, "s", __s)){
            __x = __y = __s;
            __xIsBe = __yIsBe = true;
        }

        if (!__xIsBe && !__yIsBe){
            cout << __funcName << "(): can't find x,y." << endl;
            return CMD_ERR;
        }

        CDrawableObjectControl* __doc =
            CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
            &CResourceControl::_ResourceManager._LoadingObjectControl
                :
            &CResourceControl::_ResourceManager._DrawableObjectControl;

        __obj = __doc->GetDrawableObject(objTypeName+":"+__name);

        if (__obj != NULL){
            if (__xIsBe && __yIsBe){
                if (__isBy)
                    __result = __obj->CreateActionOfScaleBy(__inte, __x, __y, __reset);
                else
                    __result = __obj->CreateActionOfScaleTo(__inte, __x, __y, __reset);
            }
            else{
                if (__xIsBe){
                    if (__isBy)
                        __result = __obj->CreateActionOfScaleXBy(__inte, __x, __reset);
                    else
                        __result = __obj->CreateActionOfScaleXTo(__inte, __x, __reset);
                }
                else{
                    if (__isBy)
                        __result = __obj->CreateActionOfScaleYBy(__inte, __y, __reset);
                    else
                        __result = __obj->CreateActionOfScaleYTo(__inte, __y, __reset);
                }
            }

            if (isCreateAction)
                *act = __result;
            else{
                if (__pause)
                    __result = Common_GetResumeIntoActset(__result);

                __obj->AddAction(__result);
            }

            return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
        }
    }

    return CMD_ERR;
}

int Common_FuncOfLayerOrder(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForSetLayerOrder" + objTypeName : "Cmd_SetLayerOrder" + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValueInTable(args, "n", __name)){
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    int __layer;
    if (!Common_GetValueInTable(args, "l", __layer)){
        cout << __funcName << "(): parameter \"l\" must be need." << endl;
        return CMD_ERR;
    }

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CDrawableClass* __obj = NULL;
    __obj = __doc->GetDrawableObject(objTypeName + ":" + __name);

    if (__obj){
        if (isCreateAction)
            *act = new CClassFuncArgsOfAction<CDrawableClass, char, void>(__obj, &CImageBaseClass::SetLayerOrder, (char)__layer);
        else
            __obj->AddAction(new CClassFuncArgsOfAction<CDrawableClass, char, void>(__obj, &CImageBaseClass::SetLayerOrder, (char)__layer));

        return CMD_OK;
    }
        
    cout << __funcName << "(): " << objTypeName << " \"" << __name << "\" has no existed." << endl;
    return CMD_ERR;
}

int Common_FuncOfFlip(string objTypeName, lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false, bool flipx = true)
{
    string __funcName = isCreateAction ?
        (flipx ? "Cmd_CreateActionForFlipX" : "Cmd_CreateActionForFlipY") + objTypeName :
        (flipx ? "Cmd_FlipX" : "Cmd_FlipY") + objTypeName;

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }
    
    if (!lua_isstring(args, 1)){
        cout << __funcName << "(): parameter must be string." << endl;
        return CMD_ERR;
    }

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
            :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    CImgLayer* __obj = NULL;
    __obj = static_cast<CImgLayer*>(__doc->GetDrawableObject(objTypeName + ":" + lua_tostring(args, 1)));

    if (__obj){
        if (flipx){
            if (isCreateAction)
                *act = new CClassFuncOfAction<CImgLayer, void>(__obj, &CImgLayer::FlipX);
            else
                __obj->AddAction(new CClassFuncOfAction<CImgLayer, void>(__obj, &CImgLayer::FlipX));
        }
        else{
            if (isCreateAction)
                *act = new CClassFuncOfAction<CImgLayer, void>(__obj, &CImgLayer::FlipY);
            else
                __obj->AddAction(new CClassFuncOfAction<CImgLayer, void>(__obj, &CImgLayer::FlipY));
        }

        return CMD_OK;
    }

    return CMD_ERR;
}

int Common_FuncOfScreen(lua_State* args, bool isShow, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        isShow ? "Cmd_CreateActionForShowCurtain" : "Cmd_CreateActionForHideCurtain" :
        isShow ? "Cmd_ShowCurtain" : "Cmd_HideCurtain";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    bool __pause = false; //pause
    Common_GetValueInTable(args, "p", __pause);

    bool __right = false; //right
    Common_GetValueInTable(args, "r", __right);

    size_t __Type = 0; //type
    Common_GetValueInTable(args, "t", __Type);

    size_t __inte = CCommon::_Common.INTERVAL; //interval
    Common_GetValueInTable(args, "i", __inte);

    
    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
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

    CSimultaneousOfAction* __sim = new CSimultaneousOfAction();

    int __layer;
    if (Common_GetValueInTable(args, "l", __layer)){
        __sim->AddAction(new CClassFuncArgsOfAction<CDrawableClass, char, void>(__obj, &CDrawableClass::SetLayerOrder, (char)__layer));
    }

    switch (__Type)
    {
        case 1:
            __sim->AddAction(__obj->CreateActionGradient(__inte, isShow, __right));
            break;
        case 2:
            __sim->AddAction(__obj->CreateActionLouver(__inte, isShow, __right, false));
            break;
        case 3:
            __sim->AddAction(__obj->CreateActionLouver(__inte, isShow, __right, true));
            break;
        default:
            __sim->AddAction(__obj->CreateActionShowOrHide(__inte, isShow));
            break;
    }

    CActionBaseClass* __result = __sim;

    if (isCreateAction)
        *act = __result;
    else{
        if (__pause)
            __result = Common_GetResumeIntoActset(__result);

        __obj->AddAction(__result);
    }

    return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
}

int Common_SetPoseCharacterLayer(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForSetPoseCharacterLayer" : "Cmd_SetPoseCharacterLayer";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    string __body = "";
    Common_GetValueInTable(args, "b", __body);

    string __eye = "";
    Common_GetValueInTable(args, "e", __eye);

    string __mouth = "";
    Common_GetValueInTable(args, "m", __mouth);

    bool __skip = "";
    Common_GetValueInTable(args, "s", __skip);

    vector<string> __args;
    __args.push_back(__body);
    __args.push_back(__eye);
    __args.push_back(__mouth);

    if (__skip)
        __args.push_back("");

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
        :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    if (!__doc->IsExists("CharacterLayer:" + __name)){
        cout << __funcName << "(): can't find character layer \"" << __name << "\"." << endl;
        return CMD_ERR;
    }

    CCharacterLayer* __chara = static_cast<CCharacterLayer*>(__doc->GetDrawableObject("CharacterLayer:" + __name));

    if (isCreateAction)
        *act = new CClassFuncArgsOfAction<CCharacterLayer, vector<string>, void>(__chara, &CCharacterLayer::SetPose, __args);
    else
        __chara->AddAction(new CClassFuncArgsOfAction<CCharacterLayer, vector<string>, void>(__chara, &CCharacterLayer::SetPose, __args));

    return CMD_OK;
}

int Common_SetText(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForSetText" : "Cmd_SetText";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;//name
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    string __font = "";//font
    Common_GetValueInTable(args, "f", __font);

    size_t __size = 0;//size
    Common_GetValueInTable(args, "s", __size);

    string __text = "";//text
    bool _isBeT = Common_GetValueInTable(args, "t", __text);

    bool __shadow = "";//shadow
    Common_GetValueInTable(args, "h", __shadow);

    float __shadowpercent = -1.0f;//shadowpercent
    Common_GetValueInTable(args, "c", __shadowpercent);

    string __colorRed = "";//color red
    Common_GetValueInTable(args, "cr", __colorRed);

    string __colorGreen = "";//color green
    Common_GetValueInTable(args, "cg", __colorGreen);

    string __colorBlue = "";//color blue
    Common_GetValueInTable(args, "cb", __colorBlue);

    string __styleRegular = "";//style regular
    Common_GetValueInTable(args, "sr", __styleRegular);

    string __styleBold = "";//style bold
    Common_GetValueInTable(args, "sb", __styleBold);

    string __styleItalic = "";//style italic
    Common_GetValueInTable(args, "si", __styleItalic);

    string __styleUnderlined = "";//style underlined
    Common_GetValueInTable(args, "su", __styleUnderlined);

    string __styleStrikeThrough = "";//style strikeThrough
    Common_GetValueInTable(args, "ss", __styleStrikeThrough);

    CDrawableObjectControl* __doc =
        CResourceControl::_ResourceManager.GetLoadingProcessStatus() == CResourceControl::INIT ?
        &CResourceControl::_ResourceManager._LoadingObjectControl
        :
        &CResourceControl::_ResourceManager._DrawableObjectControl;

    if (!__doc->IsExists("Text:" + __name)){
        cout << __funcName << "(): can't find text \"" << __name << "\"." << endl;
        return CMD_ERR;
    }

    CText* __txt = static_cast<CText*>(__doc->GetDrawableObject("Text:" + __name));
    CSimultaneousOfAction* __sim = new CSimultaneousOfAction();

    __sim->AddAction(new CClassFuncArgsOfAction<CText, bool, void>(__txt, &CText::SetShadowEnable, __shadow));
    
    if (!(__shadowpercent < 0.0f))
        __sim->AddAction(new CClassFuncArgsOfAction<CText, float, void>(__txt, &CText::SetShadowPercent, __shadowpercent));
    
    if (__size > 0)
        __sim->AddAction(new CClassFuncArgsOfAction<CText, size_t, void>(__txt, &CText::SetCharacterSize, __size));
    
    if (__colorRed != "" ||
        __colorGreen != "" ||
        __colorBlue != ""){

        __sim->AddAction(new CClassFuncArgsOfAction<CText, int, void>(
            __txt, &CText::SetRed, __colorRed == "" ? __txt->GetRed() : atoi(__colorRed.c_str())));

        __sim->AddAction(new CClassFuncArgsOfAction<CText, int, void>(
            __txt, &CText::SetGreen, __colorGreen == "" ? __txt->GetGreen() : atoi(__colorGreen.c_str())));

        __sim->AddAction(new CClassFuncArgsOfAction<CText, int, void>(
            __txt, &CText::SetBlue, __colorBlue == "" ? __txt->GetBlue() : atoi(__colorBlue.c_str())));
    }

    if (__font != "")
        __sim->AddAction(new CClassFuncArgsOfAction<CText, string ,void>(__txt, &CText::SetFont, __font));

    if (_isBeT)
        __sim->AddAction(new CClassFuncArgsOfAction<CText, string, void>(__txt, &CText::SetString, __text));

    if (__styleRegular != "" ||
        __styleBold != "" ||
        __styleItalic != "" ||
        __styleUnderlined != "" ||
        __styleStrikeThrough != "")
    {
        vector<string> __args;
        __args.clear();
        if (__styleRegular != ""){
            __args.push_back("-sr");
            __sim->AddAction(new CClassFuncArgsOfAction<CText, vector<string>, void>(__txt, &CText::SetStyle, __args));
        }
        else{
            if (__styleBold != "")
                __args.push_back("-sb");

            if (__styleItalic != "")
                __args.push_back("-si");

            if (__styleUnderlined != "")
                __args.push_back("-su");

            if (__styleStrikeThrough != "")
                __args.push_back("-ss");

            __sim->AddAction(new CClassFuncArgsOfAction<CText, vector<string>, void>(__txt, &CText::SetStyle, __args));
        }
    }

    if (isCreateAction)
        *act = __sim;
    else
        __txt->AddAction(__sim);

    return CMD_OK;
}

int Common_PlayBGM(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForPlayBGM" : "Cmd_PlayBGM";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;//name
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << __funcName << "(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __vol = 1.0f;
    Common_GetValueInTable(args, "v", __vol);

    bool __loop = false;
    Common_GetValueInTable(args, "l", __loop);

    vector<string> __args;
    __args.push_back(__name);
    __args.push_back(CCommon::_Common.ConvertToString(__vol));
    if (__loop)
        __args.push_back("l");

    if (isCreateAction)
        *act = new CClassFuncArgsOfAction<CSoundBank, vector<string>, void>(
            &CResourceControl::_ResourceManager._SoundControl, &CSoundBank::PlayBgm, __args);
    else
        CResourceControl::_ResourceManager._ActionControl.AddAction(
        new CClassFuncArgsOfAction<CSoundBank, vector<string>, void>(
                &CResourceControl::_ResourceManager._SoundControl, &CSoundBank::PlayBgm, __args));

    return CMD_OK;
}

int Common_SetBGMVolume(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForSetBGMVolume" : "Cmd_SetBGMVolume";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    float __vol = 1.0f;//vol
    if (!Common_GetValueInTable(args, "v", __vol))
    {
        cout << "Cmd_SetBGMVolume(): parameter \"v\" must be need." << endl;
        return CMD_ERR;
    }

    size_t __inte = CCommon::_Common.INTERVAL;//incr
    Common_GetValueInTable(args, "i", __inte);

    bool __isBy = false;// isBy
    Common_GetValueInTable(args, "b", __isBy);

    bool __pause = false;//pause
    Common_GetValueInTable(args, "p", __pause);

    bool __reset = false;//reset
    Common_GetValueInTable(args, "r", __reset);

    CActionBaseClass* __result = NULL;
    if (__isBy)
        CActionBaseClass* __result = CResourceControl::_ResourceManager._SoundControl.CreateActionOfMusicVolBy(
            __inte, __vol, __reset);
    else
        CActionBaseClass* __result = CResourceControl::_ResourceManager._SoundControl.CreateActionOfMusicVolTo(
            __inte, __vol, __reset);

    if (isCreateAction)
        *act = __result;
    else{
        if (__pause)
            __result = Common_GetResumeIntoActset(__result);

        CResourceControl::_ResourceManager._ActionControl.AddAction(__result);
    }

    return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
}

int Common_StopBGM(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForStopBGM" : "Cmd_StopBGM";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return 0;
        }
    }

    size_t __inte = 0;//incr
    Common_GetValueInTable(args, "i", __inte);

    bool __pause = false;//pause
    Common_GetValueInTable(args, "p", __pause);

    CSequenceOfAction* __seq = new CSequenceOfAction();
    __seq->AddAction(CResourceControl::_ResourceManager._SoundControl.CreateActionOfMusicVolTo(__inte, 0.0f, false));
    __seq->AddAction(new CClassFuncOfAction<CSoundBank, void>(
        &CResourceControl::_ResourceManager._SoundControl, &CSoundBank::StopBgm));

    CActionBaseClass* __result = __seq;

    if (isCreateAction)
        *act = __result;
    else{
        if (__pause)
            __result = Common_GetResumeIntoActset(__result);

        CResourceControl::_ResourceManager._ActionControl.AddAction(__result);
    }

    return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
}

int Common_StopSE(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForStopSE" : "Cmd_StopSE";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_YIELD;
        }
    }

    string __name;
    vector<string> __args;
    if (Common_GetValueInTable(args, "n", __name)){
        __args.push_back(__name);
    }
    else{
        if (!Common_GetValueInTable(args, "n", __args)){
            cout << __funcName << "(): parameter \"n\" must be need." << endl;
            return CMD_YIELD;
        }
    }

    if (isCreateAction)
        *act = new CClassFuncArgsOfAction<CSoundBank, vector<string>, void>(
            &CResourceControl::_ResourceManager._SoundControl,
            &CSoundBank::StopSE,
            __args);
    else
        CResourceControl::_ResourceManager._ActionControl.AddAction(
            new CClassFuncArgsOfAction<CSoundBank, vector<string>, void>(
                &CResourceControl::_ResourceManager._SoundControl,
                &CSoundBank::StopSE,
                __args));

    return CMD_OK;
}

int Common_PlaySE(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForPlaySE" : "Cmd_PlaySE";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    string __name;//name
    if (!Common_GetValueInTable(args, "n", __name))
    {
        cout << "Cmd_PlaySE(): parameter \"n\" must be need." << endl;
        return CMD_ERR;
    }

    float __vol = 1.0f;//vol
    Common_GetValueInTable(args, "v", __vol);

    bool __loop = false; //loop
    Common_GetValueInTable(args, "l", __loop);

    vector<string> __args;
    __args.push_back(__name);
    __args.push_back(CCommon::_Common.ConvertToString(__vol));
    if (__loop)
        __args.push_back("");

    if (isCreateAction)
        *act = new CClassFuncArgsOfAction<CSoundBank, vector<string>, void>(
            &CResourceControl::_ResourceManager._SoundControl,
            &CSoundBank::PlaySE,
            __args);
    else
        CResourceControl::_ResourceManager._ActionControl.AddAction(
            new CClassFuncArgsOfAction<CSoundBank, vector<string>, void>(
                &CResourceControl::_ResourceManager._SoundControl,
                &CSoundBank::PlaySE,
                __args));

    return CMD_OK;
}

int Common_UseCamera(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForUseCamera" : "Cmd_UseCamera";

    int __numOfargs = lua_gettop(args);
    if (__numOfargs == 0){
        if (isCreateAction)
            *act = new CClassFuncOfAction<CCameraControl, void>(
                &CResourceControl::_ResourceManager._CameraControl,
                &CCameraControl::UseDefaultCamera);
        else
            CResourceControl::_ResourceManager._ActionControl.AddAction(
                new CClassFuncOfAction<CCameraControl, void>(
                    &CResourceControl::_ResourceManager._CameraControl,
                    &CCameraControl::UseDefaultCamera));
    }
    else{
        string __name = "";// Name
        Common_GetValueInTable(args, "n", __name);

        if (isCreateAction)
            *act = new CClassFuncArgsOfAction<CCameraControl, string, bool>(
                &CResourceControl::_ResourceManager._CameraControl,
                &CCameraControl::UseCamera,
                __name);
        else
            CResourceControl::_ResourceManager._ActionControl.AddAction(
                new CClassFuncArgsOfAction<CCameraControl, string, bool>(
                    &CResourceControl::_ResourceManager._CameraControl,
                    &CCameraControl::UseCamera,
                    __name));
    }

    return CMD_OK;
}

int Common_Delay(lua_State* args, CActionBaseClass** act = NULL, bool isCreateAction = false)
{
    string __funcName = isCreateAction ?
        "Cmd_CreateActionForDelay" : "Cmd_Delay";

    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __funcName << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;
            return CMD_ERR;
        }
    }

    size_t __time;//name
    if (!Common_GetValueInTable(args, "t", __time))
    {
        cout << __funcName << "(): parameter \"t\" must be need." << endl;
        return CMD_ERR;
    }

    bool __pause = false;//pause
    Common_GetValueInTable(args, "p", __pause);

    CActionBaseClass* __result = new CDeplayOfAction(__time);

    if (isCreateAction)
        *act = __result;
    else{
        if (__pause)
            __result = Common_GetResumeIntoActset(__result);

        CResourceControl::_ResourceManager._ActionControl.AddAction(__result);
    }

    return !__pause || isCreateAction  ? CMD_OK : CMD_YIELD;
}

int Common_CreateActionSet(lua_State* args, string funcname)
{
    int __numOfargs = lua_gettop(args);
    if (__numOfargs < 1){
        cout << funcname << "(): command invaild. can't set " << __numOfargs
            << " argument(s) in the command." << endl;

        lua_pushnil(args);
        return 1;
    }

    int __loopNum = -1;
    if (funcname == "Cmd_CreateRepeat" && __numOfargs > 1){
        Common_GetValue(args, __loopNum);
    }

    string __name = "";
    Common_GetValue(args, __name);

    CActionBaseClass **_act =
        (CActionBaseClass**)lua_newuserdata(args, sizeof(CActionBaseClass*));

    if (funcname == "Cmd_CreateSequence"){
        *_act = new CSequenceOfAction(__name);
        luaL_getmetatable(args, "yoyo.seq");
    }
    else if (funcname == "Cmd_CreateSimultaneous"){
        *_act = new CSimultaneousOfAction(__name);
        luaL_getmetatable(args, "yoyo.sim");
    }
    else{
        *_act = new CRepeatOfAction(__name,  __loopNum);
        luaL_getmetatable(args, "yoyo.rep");
    }

    lua_setmetatable(args, -2);
    return 1;
}

////////////////////////////////////////

typedef int(*fun3arg)(lua_State*, CActionBaseClass**, bool);
typedef int(*fun4arg)(string, lua_State*, CActionBaseClass**, bool);
typedef int(*fun5arg)(string, lua_State*, CActionBaseClass**, bool, bool);

int Common_CreateActionForXXX(
    fun3arg func,
    lua_State* args)
{
    CActionBaseClass* __act = NULL;
    if (func(args, &__act, true) != CMD_ERR){
        if (__act == NULL)
            lua_pushnil(args);
        else
            lua_pushlightuserdata(args, __act);

        return 1;
    }

    lua_pushnil(args);
    return 1;
}

int Common_CreateActionForXXX(
    fun4arg func,
    string objTypeName, 
    lua_State* args)
{
    CActionBaseClass* __act = NULL;
    if (func(objTypeName, args, &__act, true) != CMD_ERR){
        if (__act == NULL)
            lua_pushnil(args);
        else
            lua_pushlightuserdata(args, __act);

        return 1;
    }

    lua_pushnil(args);
    return 1;
}

int Common_CreateActionForXXX(
    fun5arg func,
    string objTypeName,
    lua_State* args,
    bool flipx)
{
    CActionBaseClass* __act = NULL;
    if (func(objTypeName, args, &__act, true, flipx) != CMD_ERR){
        if (__act == NULL)
            lua_pushnil(args);
        else
            lua_pushlightuserdata(args, __act);

        return 1;
    }

    lua_pushnil(args);
    return 1;
}

/*==============================================================
    commad of script
===============================================================*/

int Cmd_ShowCharacterLayer(lua_State* args)
{
    if (Common_FuncOfShow("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForShowCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfShow, "CharacterLayer", args);
}

int Cmd_MoveCharacterLayer(lua_State* args)
{
    if (Common_FuncOfMove("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForMoveCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfMove, "CharacterLayer", args);
}

int Cmd_ScaleCharacterLayer(lua_State* args)
{
    if (Common_FuncOfScale("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForScaleCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfScale, "CharacterLayer", args);
}

int Cmd_RotationCharacterLayer(lua_State* args)
{
    if (Common_FuncOfRotation("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForRotationCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfRotation, "CharacterLayer", args);
}

int Cmd_HideCharacterLayer(lua_State* args)
{
    if (Common_FuncOfHide("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForHideCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfHide, "CharacterLayer", args);
}

int Cmd_SetPoseCharacterLayer(lua_State* args)
{
    if (Common_SetPoseCharacterLayer(args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetPoseCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_SetPoseCharacterLayer, args);
}

int Cmd_SetCharacterLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetCharacterLayerOrder(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfLayerOrder, "CharacterLayer", args);
}

int Cmd_FlipXCharacterLayer(lua_State* args)
{
    if (Common_FuncOfFlip("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForFlipXCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfFlip, "CharacterLayer", args, true);
}


int Cmd_FlipYCharacterLayer(lua_State* args)
{
    if (Common_FuncOfFlip("CharacterLayer", args, NULL, false, false) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForFlipYCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfFlip, "CharacterLayer", args, false);
}

int Cmd_OriginCharacterLayer(lua_State* args)
{
    if (Common_FuncOfOrigin("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForOriginCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfOrigin, "CharacterLayer", args);
}

int Cmd_ColorCharacterLayer(lua_State* args)
{
    if (Common_FuncOfColor("CharacterLayer", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForColorCharacterLayer(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfColor, "CharacterLayer", args);
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
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForShowImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfShow, "Img", args);
}

int Cmd_HideImg(lua_State* args)
{
    if (Common_FuncOfHide("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForHideImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfHide, "Img", args);
}

int Cmd_MoveImg(lua_State* args)
{
    if (Common_FuncOfMove("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForMoveImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfMove, "Img", args);
}

int Cmd_ScaleImg(lua_State* args)
{
    if (Common_FuncOfScale("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForScaleImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfScale, "Img", args);
}

int Cmd_RotationImg(lua_State* args)
{
    if (Common_FuncOfRotation("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForRotationImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfRotation, "Img", args);
}

int Cmd_SetImgLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetImgLayerOrder(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfLayerOrder, "Img", args);
}

int Cmd_FlipXImg(lua_State* args)
{
    if (Common_FuncOfFlip("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForFlipXImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfFlip, "Img", args, true);
}

int Cmd_FlipYImg(lua_State* args)
{
    if (Common_FuncOfFlip("Img", args, false) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForFlipYImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfFlip, "Img", args, false);
}

int Cmd_OriginImg(lua_State* args)
{
    if (Common_FuncOfOrigin("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForOriginImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfOrigin, "Img", args);
}

int Cmd_ColorImg(lua_State* args)
{
    if (Common_FuncOfColor("Img", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForColorImg(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfColor, "Img", args);
}

int Cmd_ShowText(lua_State* args)
{
    if (Common_FuncOfShow("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForShowText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfShow, "Text", args);
}

int Cmd_HideText(lua_State* args)
{
    if (Common_FuncOfHide("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForHideText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfHide, "Text", args);
}

int Cmd_MoveText(lua_State* args)
{
    if (Common_FuncOfMove("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForMoveText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfMove, "Text", args);
}

int Cmd_ScaleText(lua_State* args)
{
    if (Common_FuncOfScale("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForScaleText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfScale, "Text", args);
}

int Cmd_RotationText(lua_State* args)
{
    if (Common_FuncOfRotation("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForRotationText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfRotation, "Text", args);
}

int Cmd_SetTextLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetTextLayerOrder(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfLayerOrder, "Text", args);
}

int Cmd_OriginText(lua_State* args)
{
    if (Common_FuncOfOrigin("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForOriginText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfOrigin, "Text", args);
}

int Cmd_ColorText(lua_State* args)
{
    if (Common_FuncOfColor("Text", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForColorText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfColor, "Text", args);
}

int Cmd_SetText(lua_State* args)
{
    if (Common_SetText(args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetText(lua_State* args)
{
    return Common_CreateActionForXXX(Common_SetText, args);
}

int Cmd_PlayBGM(lua_State* args)
{
    if (Common_PlayBGM(args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForPlayBGM(lua_State* args)
{
    return Common_CreateActionForXXX(Common_PlayBGM, args);
}

int Cmd_SetBGMVolume(lua_State* args)
{
    if (Common_SetBGMVolume(args) == CMD_YIELD)
    Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetBGMVolume(lua_State* args)
{
    return Common_CreateActionForXXX(Common_SetBGMVolume, args);
}

int Cmd_PauseBGM(lua_State* args)
{
    CResourceControl::_ResourceManager._ActionControl.AddAction(
        new CClassFuncOfAction<CSoundBank, void>(
            &CResourceControl::_ResourceManager._SoundControl,
            &CSoundBank::PauseBgm));

    return 0;
}

int Cmd_CreateActionForPauseBGM(lua_State* args)
{
    lua_pushlightuserdata(args, new CClassFuncOfAction<CSoundBank, void>(
        &CResourceControl::_ResourceManager._SoundControl,
        &CSoundBank::PauseBgm));

    return 1;
}

int Cmd_ResumeBGM(lua_State* args)
{
    CResourceControl::_ResourceManager._ActionControl.AddAction(
        new CClassFuncOfAction<CSoundBank, void>(
        &CResourceControl::_ResourceManager._SoundControl,
        &CSoundBank::PlayBgm));

    return 0;
}

int Cmd_CreateActionForResumeBGM(lua_State* args)
{
    lua_pushlightuserdata(args, new CClassFuncOfAction<CSoundBank, void>(
        &CResourceControl::_ResourceManager._SoundControl,
        &CSoundBank::PlayBgm));

    return 1;
}

int Cmd_StopBGM(lua_State* args)
{
    if (Common_StopBGM(args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForStopBGM(lua_State* args)
{
    return Common_CreateActionForXXX(Common_StopBGM, args);
}

int Cmd_StopSE(lua_State* args)
{
    if (Common_StopSE(args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForStopSE(lua_State* args)
{
    return Common_CreateActionForXXX(Common_StopSE, args);
}

int Cmd_PlaySE(lua_State* args)
{
    if (CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::LOADEDSAVEDATA)
        if (Common_PlaySE(args) == CMD_YIELD)
            Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForPlaySE(lua_State* args)
{
    if (CResourceControl::_ResourceManager.GetLoadingProcessStatus() != CResourceControl::LOADEDSAVEDATA)
        return Common_CreateActionForXXX(Common_PlaySE, args);
    else{
        lua_pushnil(args);
        return 1;
    }
}

int Cmd_ShowButton(lua_State* args)
{
    if (Common_FuncOfShow("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForShowButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfShow, "Button", args);
}

int Cmd_HideButton(lua_State* args)
{
    if (Common_FuncOfHide("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForHideButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfHide, "Button", args);
}

int Cmd_MoveButton(lua_State* args)
{
    if (Common_FuncOfMove("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForMoveButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfMove, "Button", args);
}

int Cmd_ScaleButton(lua_State* args)
{
    if (Common_FuncOfScale("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForScaleButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfScale, "Button", args);
}

int Cmd_RotationButton(lua_State* args)
{
    if (Common_FuncOfRotation("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForRotationButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfRotation, "Button", args);
}

int Cmd_SetButtonLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetButtonLayerOrder(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfLayerOrder, "Button", args);
}

int Cmd_FlipXButton(lua_State* args)
{
    if (Common_FuncOfFlip("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForFlipXButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfFlip, "Button", args, true);
}

int Cmd_FlipYButton(lua_State* args)
{
    if (Common_FuncOfFlip("Button", args, false) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForFlipYButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfFlip, "Button", args, false);
}

int Cmd_OriginButton(lua_State* args)
{
    if (Common_FuncOfOrigin("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForOriginButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfOrigin, "Button", args);
}

int Cmd_ColorButton(lua_State* args)
{
    if (Common_FuncOfColor("Button", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForColorButton(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfColor, "Button", args);
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
    if (!Common_GetValueInTable(args, "n", __msgBoxName)){
        cout << "Cmd_Message(): parameter \"n\" must be need." << endl;
        return 0;
    }

    string __msg;//message
    if (!Common_GetValueInTable(args, "m", __msg)){
        cout << "Cmd_Message(): parameter \"m\" must be need." << endl;
        return 0;
    }

    string __speakerName = "";
    Common_GetValueInTable(args, "s", __speakerName);

    string __voiceName = "";
    Common_GetValueInTable(args, "v", __voiceName);

    vector<string> __cOfArg;
    Common_GetValueInTable(args, "c", __cOfArg);

    CDrawableClass* __obj = 
        CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("MessageBox:"+__msgBoxName);

    if(__obj == NULL){
        cout << "Cmd_Message(): MessageBox \"" << __msgBoxName << "\" has no existed." <<endl;
        return 0;
    }

    CMessageBox* __msgbox = static_cast<CMessageBox*>(__obj);
    CSimultaneousOfAction* __sim = new CSimultaneousOfAction();

    if (__cOfArg.size() != 0){
        for (size_t i = 0; i < __cOfArg.size(); i++){
            if (__cOfArg[i] != ""){
                __obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("CharacterLayer:" + __cOfArg[i]);
                if(__obj == NULL)
                    cout << "Cmd_Message(): CharacterLayer \"" << __cOfArg[i] << "\" has no existed." << endl;
                else{
                    CCharacterLayer* __chara = static_cast<CCharacterLayer*>(__obj);
                    __sim->AddAction(new CClassFuncArgsOfAction<CCharacterLayer, string, void>(__chara, &CCharacterLayer::SetVoice, __voiceName));
                }
            }
        }
    }
    
    __sim->AddAction(new CClassFuncArgsOfAction<CMessageBox, string, void>(__msgbox, &CMessageBox::SetText, __msg));
    __sim->AddAction(new CClassFuncArgsOfAction<CMessageBox, string, void>(__msgbox, &CMessageBox::SetSpeakerName, __speakerName));

    if (__voiceName != "")
        __sim->AddAction(new CClassFuncArgsOfAction<CSoundBank, string, bool>(
            &CResourceControl::_ResourceManager._SoundControl, &CSoundBank::PlayVoice, __voiceName));

    __msgbox->AddAction(__sim);
    CResourceControl::_ResourceManager.OnMsgboxPause();
    Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_ShowMessageBox(lua_State* args)
{   
    if (Common_FuncOfShow("MessageBox", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForShowMessageBox(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfShow, "MessageBox", args);
}

int Cmd_HideMessageBox(lua_State* args)
{
    if (Common_FuncOfHide("MessageBox", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForHideMessageBox(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfHide, "MessageBox", args);
}

int Cmd_SetMessageBoxLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("MessageBox", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetMessageBoxLayerOrder(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfLayerOrder, "MessageBox", args);
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
    if (!Common_GetValueInTable(args, "n", __msgBoxName)){
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
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForShowLogBox(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfShow, "LogBox", args);
}

int Cmd_HideLogBox(lua_State* args)
{
    if (Common_FuncOfHide("LogBox", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForHideLogBox(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfHide, "LogBox", args);
}

int Cmd_SetLogBoxLayerOrder(lua_State* args)
{
    if (Common_FuncOfLayerOrder("LogBox", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForSetLogBoxLayerOrder(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfLayerOrder, "LogBox", args);
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
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForShowCurtain(lua_State* args)
{
    CActionBaseClass* __act = NULL;
    if (Common_FuncOfScreen(args, true, & __act, true) != CMD_ERR){
        if (__act == NULL)
            lua_pushnil(args);
        else
            lua_pushlightuserdata(args, __act);

        return 1;
    }

    lua_pushnil(args);
    return 1;
}

int Cmd_HideCurtain(lua_State* args)
{
    if (Common_FuncOfScreen(args, false) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForHideCurtain(lua_State* args)
{
    CActionBaseClass* __act = NULL;
    if (Common_FuncOfScreen(args, false, &__act, true) != CMD_ERR){
        if (__act == NULL)
            lua_pushnil(args);
        else
            lua_pushlightuserdata(args, __act);

        return 1;
    }

    lua_pushnil(args);
    return 1;
}

int Cmd_ColorCurtain(lua_State* args)
{
    if (Common_FuncOfColor("ScrEffect", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForColorCurtain(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfColor, "ScrEffect", args);
}

int Cmd_UseCamera(lua_State* args)
{
    if (Common_UseCamera(args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForUseCamera(lua_State* args)
{
    return Common_CreateActionForXXX(Common_UseCamera, args);
}

int Cmd_MoveCamera(lua_State* args)
{
    if (Common_FuncOfMove("Camera", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForMoveCamera(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfMove, "Camera", args);
}

int Cmd_ScaleCamera(lua_State* args)
{
    if (Common_FuncOfScale("Camera", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForScaleCamera(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfScale, "Camera", args);
}

int Cmd_RotationCamera(lua_State* args)
{
    if (Common_FuncOfRotation("Camera", args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForRotationCamera(lua_State* args)
{
    return Common_CreateActionForXXX(Common_FuncOfRotation, "Camera", args);
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
int Cmd_Delay(lua_State* args)
{
    if (Common_Delay(args) == CMD_YIELD)
        Common_RetrunYield(args, __FUNCTION__);

    return 0;
}

int Cmd_CreateActionForDelay(lua_State* args)
{
    return Common_CreateActionForXXX(Common_Delay, args);
}

int Cmd_DeleteOrSkipAction(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __FUNCTION__ <<"(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;

            lua_pushboolean(args, false);
            return CMD_ERR;
        }
    }

    //bool __skip = true;
    //Common_GetValue(args, __skip);

    string __name = "";
    if (!Common_GetValue(args, __name)){
        cout << __FUNCTION__ << "(): type of first argument must string." << endl;
        lua_pushboolean(args, false);
        return CMD_ERR;
    }

    CResourceControl::_ResourceManager._ActionControl.AddAction(
        new CClassFuncArgsOfAction<CResourceControl, string, void>(
            &CResourceControl::_ResourceManager, 
            &CResourceControl::DelActionForActionControl, 
            __name));

    lua_pushboolean(args, true);
    return CMD_OK;
}

int Cmd_LoadScript(lua_State* args)
{
    {
        int __numOfargs = lua_gettop(args);
        if (__numOfargs < 1){
            cout << __FUNCTION__ << "(): command invaild. can't set " << __numOfargs
                << " argument(s) in the command." << endl;

            lua_pushboolean(args, false);
            return CMD_ERR;
        }
    }

    string __filename = "";
    if (!Common_GetValue(args, __filename)){
        cout << __FUNCTION__ << "(): type of first argument must string." << endl;
        return CMD_ERR;
    }

    //CResourceControl::_ResourceManager.LoadScript(__filename);
    CResourceControl::_ResourceManager._ActionControl.AddAction(
        new CClassFuncArgsOfAction<CResourceControl, string, bool>(
            &CResourceControl::_ResourceManager,
            &CResourceControl::LoadScript,
            __filename));

    return lua_yield(args, 0);
}

int Cmd_AddAction(lua_State* args)
{
    return Common_AddAction(args, 0, __FUNCTION__);
}

int Cmd_AddActionForLoadBegin(lua_State* args)
{
    return Common_AddAction(args, 1, __FUNCTION__);
}

int Cmd_AddActionForLoadFinish(lua_State* args)
{
    return Common_AddAction(args, 2, __FUNCTION__);
}

int Cmd_CreateActionOfResume(lua_State* args)
{
    //for mutex
    //CActionBaseClass *__act = new CClassFuncOfAction<CResourceControl, void>(
    //    &CResourceControl::_ResourceManager,
    //    &CResourceControl::UnlockMutexInMain);

    CActionBaseClass *__act = new CClassFuncOfAction<CLua, int>(
        &CResourceControl::_ResourceManager._LuaControl,
        &CLua::ResumeLuaThread);

    lua_pushlightuserdata(args, __act);
    return 1;
}

int Cmd_CreateActionOfPause(lua_State* args)
{
    //CActionBaseClass* __act = new CFuncArgsOfAction<string, int>(
    //    &Common_RetrunYield, __FUNCTION__);

    //lua_pushlightuserdata(args, __act);
    return 1;
}

int Cmd_CreateSimultaneous(lua_State* args)
{
    Common_CreateActionSet(args, __FUNCTION__);
    return 1;
}

int Cmd_CreateSequence(lua_State* args)
{
    Common_CreateActionSet(args, __FUNCTION__);
    return 1;
}

int Cmd_CreateRepeat(lua_State* args)
{
    Common_CreateActionSet(args, __FUNCTION__);
    return 1;
}
