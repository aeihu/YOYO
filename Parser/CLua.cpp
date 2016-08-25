/*
* Copyright (C) 2012-2016, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CLua.h"
#include "CScriptCommand.h"
#include "../Common/Cio.h"
#include "../Action/CSequenceOfAction.h"
#include "../Action/CSimultaneousOfAction.h"
#include "../Action/CRepeatOfAction.h"

int seq_AddAction(lua_State *L)
{
    CSequenceOfAction **__seq = (CSequenceOfAction**)luaL_checkudata(L, 1, "yoyo.seq");
    luaL_argcheck(L, __seq != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TLIGHTUSERDATA);

    (*__seq)->AddAction((CSequenceOfAction*)lua_topointer(L, -1));
    return 0;
}

int seq_GetAction(lua_State *L)
{
    CSequenceOfAction **__seq = (CSequenceOfAction**)luaL_checkudata(L, 1, "yoyo.seq");
    luaL_argcheck(L, __seq != NULL, 1, "invalid user data");

    lua_pushlightuserdata(L, *__seq);
    return 1;
}

int seq_CpoyAction(lua_State *L)
{
    CSequenceOfAction **__seq = (CSequenceOfAction**)luaL_checkudata(L, 1, "yoyo.seq");
    luaL_argcheck(L, __seq != NULL, 1, "invalid user data");

    lua_pushlightuserdata(L, (*__seq)->Copy());
    return 1;
}

int seq_GC(lua_State *L)
{
    //CSequenceOfAction **_act = (CSequenceOfAction**)luaL_checkudata(L, 1, "yoyo.seq");
    //if (*_act){
    //    delete *_act;
    //    *_act = NULL;
    //}

    return 0;
}

int sim_AddAction(lua_State *L)
{
    CSimultaneousOfAction **__sim = (CSimultaneousOfAction**)luaL_checkudata(L, 1, "yoyo.sim");
    luaL_argcheck(L, __sim != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TLIGHTUSERDATA);

    (*__sim)->AddAction((CSimultaneousOfAction*)lua_topointer(L, -1));
    return 0;
}

int sim_GetAction(lua_State *L)
{
    CSimultaneousOfAction **__sim = (CSimultaneousOfAction**)luaL_checkudata(L, 1, "yoyo.sim");
    luaL_argcheck(L, __sim != NULL, 1, "invalid user data");

    lua_pushlightuserdata(L, *__sim);
    return 1;
}

int sim_CpoyAction(lua_State *L)
{
    CSimultaneousOfAction **__sim = (CSimultaneousOfAction**)luaL_checkudata(L, 1, "yoyo.sim");
    luaL_argcheck(L, __sim != NULL, 1, "invalid user data");

    lua_pushlightuserdata(L, (*__sim)->Copy());
    return 1;
}

int sim_GC(lua_State *L)
{
    //CSimultaneousOfAction **_act = (CSimultaneousOfAction**)luaL_checkudata(L, 1, "yoyo.sim");
    //if (*_act){
    //    delete *_act;
    //    *_act = NULL;
    //}

    return 0;
}

int rep_AddAction(lua_State *L)
{
    CRepeatOfAction **__rep = (CRepeatOfAction**)luaL_checkudata(L, 1, "yoyo.rep");
    luaL_argcheck(L, __rep != NULL, 1, "invalid user data");

    luaL_checktype(L, -1, LUA_TLIGHTUSERDATA);

    (*__rep)->AddAction((CRepeatOfAction*)lua_topointer(L, -1));
    return 0;
}

int rep_GetAction(lua_State *L)
{
    CRepeatOfAction **__rep = (CRepeatOfAction**)luaL_checkudata(L, 1, "yoyo.rep");
    luaL_argcheck(L, __rep != NULL, 1, "invalid user data");

    lua_pushlightuserdata(L, *__rep);
    return 1;
}

int rep_CpoyAction(lua_State *L)
{
    CRepeatOfAction **__rep = (CRepeatOfAction**)luaL_checkudata(L, 1, "yoyo.rep");
    luaL_argcheck(L, __rep != NULL, 1, "invalid user data");

    lua_pushlightuserdata(L, (*__rep)->Copy());
    return 1;
}

int rep_GC(lua_State *L)
{
    //CRepeatOfAction **_act = (CRepeatOfAction**)luaL_checkudata(L, 1, "yoyo.rep");
    //if (*_act){
    //    delete *_act;
    //    *_act = NULL;
    //}

    return 0;
}

int luaopen_yoyo(lua_State *L) {

    static const luaL_Reg __YOYOlibs[] =
    {
        { "show_chara", Cmd_ShowCharacterLayer },
        { "hide_chara", Cmd_HideCharacterLayer },
        { "move_chara", Cmd_MoveCharacterLayer },
        { "scale_chara", Cmd_ScaleCharacterLayer },
        { "rota_chara", Cmd_RotationCharacterLayer },
        { "pose_chara", Cmd_SetPoseCharacterLayer },
        { "order_chara", Cmd_SetCharacterLayerOrder },
        { "flipx_chara", Cmd_FlipXCharacterLayer },
        { "flipy_chara", Cmd_FlipYCharacterLayer },
        { "origin_chara", Cmd_OriginCharacterLayer },
        { "color_chara", Cmd_ColorCharacterLayer },

        { "act_show_chara", Cmd_CreateActionForShowCharacterLayer },
        { "act_hide_chara", Cmd_CreateActionForHideCharacterLayer },
        { "act_move_chara", Cmd_CreateActionForMoveCharacterLayer },
        { "act_scale_chara", Cmd_CreateActionForScaleCharacterLayer },
        { "act_rota_chara", Cmd_CreateActionForRotationCharacterLayer },
        { "act_pose_chara", Cmd_CreateActionForSetPoseCharacterLayer },
        { "act_order_chara", Cmd_CreateActionForSetCharacterLayerOrder },
        { "act_flipx_chara", Cmd_CreateActionForFlipXCharacterLayer },
        { "act_flipy_chara", Cmd_CreateActionForFlipYCharacterLayer },
        { "act_origin_chara", Cmd_CreateActionForOriginCharacterLayer },
        { "act_color_chara", Cmd_CreateActionForColorCharacterLayer },

        { "show_img", Cmd_ShowImg },
        { "hide_img", Cmd_HideImg },
        { "move_img", Cmd_MoveImg },
        { "scale_img", Cmd_ScaleImg },
        { "rota_img", Cmd_RotationImg },
        { "order_img", Cmd_SetImgLayerOrder },
        { "flipx_img", Cmd_FlipXImg },
        { "flipy_img", Cmd_FlipYImg },
        { "origin_img", Cmd_OriginImg },
        { "color_img", Cmd_ColorImg },

        { "act_show_img", Cmd_CreateActionForShowImg },
        { "act_hide_img", Cmd_CreateActionForHideImg },
        { "act_move_img", Cmd_CreateActionForMoveImg },
        { "act_scale_img", Cmd_CreateActionForScaleImg },
        { "act_rota_img", Cmd_CreateActionForRotationImg },
        { "act_order_img", Cmd_CreateActionForSetImgLayerOrder },
        { "act_flipx_img", Cmd_CreateActionForFlipXImg },
        { "act_flipy_img", Cmd_CreateActionForFlipYImg },
        { "act_origin_img", Cmd_CreateActionForOriginImg },
        { "act_color_img", Cmd_CreateActionForColorImg },

        { "show_txt", Cmd_ShowText },
        { "hide_txt", Cmd_HideText },
        { "move_txt", Cmd_MoveText },
        { "scale_txt", Cmd_ScaleText },
        { "rota_txt", Cmd_RotationText },
        { "order_txt", Cmd_SetTextLayerOrder },
        { "origin_txt", Cmd_OriginText },
        { "set_txt", Cmd_SetText },
        { "color_txt", Cmd_ColorText },

        { "act_show_txt", Cmd_CreateActionForShowText },
        { "act_hide_txt", Cmd_CreateActionForHideText },
        { "act_move_txt", Cmd_CreateActionForMoveText },
        { "act_scale_txt", Cmd_CreateActionForScaleText },
        { "act_rota_txt", Cmd_CreateActionForRotationText },
        { "act_order_txt", Cmd_CreateActionForSetTextLayerOrder },
        { "act_origin_txt", Cmd_CreateActionForOriginText },
        { "act_set_txt", Cmd_CreateActionForSetText },
        { "act_color_txt", Cmd_CreateActionForColorText },

        { "show_msgbox", Cmd_ShowMessageBox },
        { "hide_msgbox", Cmd_HideMessageBox },
        { "order_msgbox", Cmd_SetMessageBoxLayerOrder },
        { "clean_msgbox", Cmd_CleanMessageBox },
        { "msg", Cmd_Message },

        { "act_show_msgbox", Cmd_CreateActionForShowMessageBox },
        { "act_hide_msgbox", Cmd_CreateActionForHideMessageBox },
        { "act_order_msgbox", Cmd_CreateActionForSetMessageBoxLayerOrder },

        { "show_logbox", Cmd_ShowLogBox },
        { "hide_logbox", Cmd_HideLogBox },
        { "order_logbox", Cmd_SetLogBoxLayerOrder },

        { "act_show_logbox", Cmd_CreateActionForShowLogBox },
        { "act_hide_logbox", Cmd_CreateActionForHideLogBox },
        { "act_order_logbox", Cmd_CreateActionForSetLogBoxLayerOrder },

        { "play_se", Cmd_PlaySE },
        { "stop_se", Cmd_StopSE },

        { "act_play_se", Cmd_CreateActionForPlaySE },
        { "act_stop_se", Cmd_CreateActionForStopSE },

        { "play_bgm", Cmd_PlayBGM },
        { "pause_bgm", Cmd_PauseBGM },
        { "resume_bgm", Cmd_ResumeBGM },
        { "stop_bgm", Cmd_StopBGM },
        { "vol_bgm", Cmd_SetBGMVolume },

        { "act_play_bgm", Cmd_CreateActionForPlayBGM },
        { "act_pause_bgm", Cmd_CreateActionForPauseBGM },
        { "act_resume_bgm", Cmd_CreateActionForResumeBGM },
        { "act_stop_bgm", Cmd_CreateActionForStopBGM },
        { "act_vol_bgm", Cmd_CreateActionForSetBGMVolume },

        { "show_btn", Cmd_ShowButton },
        { "hide_btn", Cmd_HideButton },
        { "move_btn", Cmd_MoveButton },
        { "scale_btn", Cmd_ScaleButton },
        { "rota_btn", Cmd_RotationButton },
        { "order_btn", Cmd_SetButtonLayerOrder },
        { "flipx_btn", Cmd_FlipXButton },
        { "flipy_btn", Cmd_FlipYButton },
        { "origin_btn", Cmd_OriginButton },
        { "color_btn", Cmd_ColorButton },

        { "act_show_btn", Cmd_CreateActionForShowButton },
        { "act_hide_btn", Cmd_CreateActionForHideButton },
        { "act_move_btn", Cmd_CreateActionForMoveButton },
        { "act_scale_btn", Cmd_CreateActionForScaleButton },
        { "act_rota_btn", Cmd_CreateActionForRotationButton },
        { "act_order_btn", Cmd_CreateActionForSetButtonLayerOrder },
        { "act_flipx_btn", Cmd_CreateActionForFlipXButton },
        { "act_flipy_btn", Cmd_CreateActionForFlipYButton },
        { "act_origin_btn", Cmd_CreateActionForOriginButton },
        { "act_color_btn", Cmd_CreateActionForColorButton },

        { "use_camera", Cmd_UseCamera },
        { "move_camera", Cmd_MoveCamera },
        { "zoom_camera", Cmd_ScaleCamera },
        { "rota_camera", Cmd_RotationCamera },

        { "act_use_camera", Cmd_CreateActionForUseCamera },
        { "act_move_camera", Cmd_CreateActionForMoveCamera },
        { "act_zoom_camera", Cmd_CreateActionForScaleCamera },
        { "act_rota_camera", Cmd_CreateActionForRotationCamera },

        //{ "add_var", Cmd_AddVariable },
        //{ "set_var", Cmd_SetVariable },
        //{ "del_var", Cmd_DelVariable },

        { "show_curtain", Cmd_ShowCurtain },
        { "hide_curtain", Cmd_HideCurtain },
        { "color_curtain", Cmd_ColorCurtain },

        { "act_show_curtain", Cmd_CreateActionForShowCurtain },
        { "act_hide_curtain", Cmd_CreateActionForHideCurtain },
        { "act_color_curtain", Cmd_CreateActionForColorCurtain },

        { "create_sim", Cmd_CreateSimultaneous },
        { "create_seq", Cmd_CreateSequence },
        { "create_rep", Cmd_CreateRepeat },
        //{ "create_pause", Cmd_CreateActionOfPause },
        { "create_resume", Cmd_CreateActionOfResume },

        { "add_act", Cmd_AddAction },
        { "del_act", Cmd_DeleteOrSkipAction },

        { "add_lb", Cmd_AddActionForLoadBegin },
        { "add_lf", Cmd_AddActionForLoadFinish },

        //{ "show_particle", Cmd_ShowParticleSystem },
        //{ "hide_particle", Cmd_HideParticleSystem },
        //{ "order_particle", Cmd_SetParticleSystemLayerOrder },

        { "delay", Cmd_Delay },
        { "act_delay", Cmd_CreateActionForDelay },
        //{ "pause", Cmd_Pause },
        { "load_script", Cmd_LoadScript },
        { "exit", Cmd_LoadScript },
        { NULL, NULL }
    };

    static const struct luaL_Reg __seq[] = {
        { "add_act", seq_AddAction },
        { "get_act", seq_GetAction },
        { "copy_act", seq_CpoyAction },
        { "__gc", seq_GC },
        { NULL, NULL }
    };
    luaL_newmetatable(L, "yoyo.seq");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, __seq, 0);

    static const struct luaL_Reg __sim[] = {
        { "add_act", sim_AddAction },
        { "get_act", sim_GetAction },
        { "copy_act", sim_CpoyAction },
        { "__gc", sim_GC },
        { NULL, NULL }
    };
    luaL_newmetatable(L, "yoyo.sim");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, __sim, 0);

    static const struct luaL_Reg __rep[] = {
        { "add_act", rep_AddAction },
        { "get_act", rep_GetAction },
        { "copy_act", rep_CpoyAction },
        { "__gc", rep_GC },
        { NULL, NULL }
    };
    luaL_newmetatable(L, "yoyo.rep");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, __rep, 0);

    luaL_newlib(L, __YOYOlibs);
    return 1;
}

///////////////////////////////////////

CLua::CLua() : _thread(&CLua::RunScript, this)
{
    _luaThread = 
    _luaState = NULL;
    _currentScriptName = "";
}

CLua::~CLua()
{
}

bool CLua::OnInit()
{
    _luaState = luaL_newstate();
    
    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { "coroutine", luaopen_coroutine },
        { "table", luaopen_table },
        { "io", luaopen_io },
        { "math", luaopen_math },
        { "string", luaopen_string },
        { "os", luaopen_os },
        { "utf8", luaopen_utf8 },
        { "bit32", luaopen_bit32 },
        { "debug", luaopen_debug },
        { "package", luaopen_package },
        { "yoyo", luaopen_yoyo },
        { NULL, NULL }
    };

    const luaL_Reg *lib = lualibs;
    for (; lib->func != NULL; lib++){
        luaL_requiref(_luaState, lib->name, lib->func, 1);
        lua_pop(_luaState, 1);
    }

    if (LUA_OK != luaL_dostring(_luaState, "YOYO_LUA_THREAD_RUNNING = false")){
        cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
        return false;
    }

    return true;
}

void CLua::RunScript()
{
    _luaThread = lua_newthread(_luaState);
    _mutex.lock();
    string __scr = "YOYO_LUA_THREAD_RUNNING = true;" +
        Cio::LoadTxtFile(_currentScriptName) + 
        "\n YOYO_LUA_THREAD_RUNNING = false\n";

    if (LUA_OK != luaL_loadstring(_luaThread, __scr.c_str())){
        cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
        _mutex.unlock();
        return;
    }

    _mutex.unlock();

    if (LUA_YIELD < lua_resume(_luaThread, NULL, 0))
        cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
}

bool CLua::LoadScript(string filename, bool wait)
{
    _thread.terminate();
    _mutex.lock();
    _currentScriptName = filename;
    _mutex.unlock();
    _thread.launch();

    if (wait)
        _thread.wait();

    return true;
}

void CLua::OnCleanup()
{
    _thread.terminate();
    if (_luaState != NULL)
        lua_close(_luaState);
}

bool CLua::GetGlobal(const char* name, bool &val)
{
    if (lua_getglobal(_luaState, name) == LUA_TBOOLEAN) {
        val = lua_toboolean(_luaState, -1);
        return true;
    }

    return false;
}

int CLua::GetLuaThreadStatus() const
{
    int __status = lua_status(_luaThread);
    switch (__status)
    {
        case LUA_YIELD:
            return LUA_YIELD;// 1
        break;
        case LUA_OK:
            if (lua_getglobal(_luaState, "YOYO_LUA_THREAD_RUNNING") == LUA_TBOOLEAN)
                if (lua_toboolean(_luaState, -1))
                    return 7;

            return LUA_OK;
        break;
        default:
            return __status;
        break;
    } 
}

void CLua::GetLuaThreadInfo() const
{
    Object __json;
    lua_Debug __ar;
    lua_getstack(_luaThread, 1, &__ar);
    lua_getinfo(_luaThread, "nSltufL", &__ar);

    __json << "currentline" << __ar.currentline;
    __json << "linedefined" << __ar.linedefined;
    __json << "lastlinedefined" << __ar.lastlinedefined;
    __json << "what" << __ar.what;
    if (__ar.name != NULL)
        __json << "name" << __ar.name;
}


int CLua::ResumeLuaThread()
{
    int __result = GetLuaThreadStatus();
    if (__result == LUA_YIELD){
        __result = lua_resume(_luaThread, NULL, 0);
        if (LUA_YIELD < __result){
            cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
        }
    }

    return __result;
}
