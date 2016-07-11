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

int RegYOYOLibs(lua_State *L)
{
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

        { "show_txt", Cmd_ShowText },
        { "hide_txt", Cmd_HideText },
        { "move_txt", Cmd_MoveText },
        { "scale_txt", Cmd_ScaleText },
        { "rota_txt", Cmd_RotationText },
        { "order_txt", Cmd_SetTextLayerOrder },
        { "origin_txt", Cmd_OriginText },
        { "set_txt", Cmd_SetText },
        { "color_txt", Cmd_ColorText },

        { "show_msgbox", Cmd_ShowMessageBox },
        { "hide_msgbox", Cmd_HideMessageBox },
        { "order_msgbox", Cmd_SetMessageBoxLayerOrder },
        { "clean_msgbox", Cmd_CleanMessageBox },
        { "msg", Cmd_Message },

        { "show_logbox", Cmd_ShowLogBox },
        { "hide_logbox", Cmd_HideLogBox },
        { "order_logbox", Cmd_SetLogBoxLayerOrder },

        { "play_se", Cmd_PlayBGM },
        { "pause_bgm", Cmd_PauseBGM },
        { "resume_bgm", Cmd_ResumeBGM },
        { "stop_bgm", Cmd_StopBGM },
        { "vol_bgm", Cmd_SetBGMVolume },

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


        { "use_camera", Cmd_UseCamera },
        { "move_camera", Cmd_MoveCamera },
        { "zoom_camera", Cmd_ScaleCamera },
        { "rota_camera", Cmd_RotationCamera },

        //{ "add_var", Cmd_AddVariable },
        //{ "set_var", Cmd_SetVariable },
        //{ "del_var", Cmd_DelVariable },

        //{ "del_act", Cmd_DelAction },
        //{ "skip_act", Cmd_SkipAction },

        { "show_curtain", Cmd_ShowCurtain },
        { "hide_curtain", Cmd_HideCurtain },
        { "color_curtain", Cmd_ColorCurtain },

        //{ "show_particle", Cmd_ShowParticleSystem },
        //{ "hide_particle", Cmd_HideParticleSystem },
        //{ "order_particle", Cmd_SetParticleSystemLayerOrder },

        //{ "delay", Cmd_Delay },
        //{ "pause", Cmd_Pause },
        { "load_script", Cmd_LoadScript },
        { "exit", Cmd_LoadScript },
        { NULL, NULL }
    };

    luaL_newlib(L, __YOYOlibs);
    return 1;
}

///////////////////////////////////////

CLua::CLua() : _thread(&CLua::RunScript, this)
{
    _luaThread = 
    _luaState = NULL;
    _codeAtBeginOfScript =
    _codeAtEndOfScript =
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
        { "yoyo", RegYOYOLibs },
        { NULL, NULL }
    };
    //3.注册Lua标准库并清空栈
    const luaL_Reg *lib = lualibs;
    for (; lib->func != NULL; lib++)
    {
        luaL_requiref(_luaState, lib->name, lib->func, 1);
        lua_pop(_luaState, 1);
    }

    if (LUA_OK != luaL_dostring(_luaState, "YOYO_LUA_THREAD_RUNNING = false"))
    {
        cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
        return false;
    }

    return true;
}

void CLua::RunScript()
{
    _luaThread = lua_newthread(_luaState);
    _mutex.lock();
    string __scr = _codeAtBeginOfScript +
        ";YOYO_LUA_THREAD_RUNNING = true;" +
        Cio::LoadTxtFile(_currentScriptName) + 
        "\n YOYO_LUA_THREAD_RUNNING = false\n" +
        _codeAtEndOfScript;

    if (LUA_OK != luaL_loadstring(_luaThread, __scr.c_str()))
    {
        cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
    }
    _mutex.unlock();

    if (LUA_YIELD < lua_resume(_luaThread, NULL, 0))
    {
        cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
    }
}

bool CLua::LoadScript(string filename, string codeAtB, string codeAtE)
{
    _codeAtBeginOfScript = codeAtB;
    _codeAtBeginOfScript = codeAtE;
    _thread.terminate();
    _mutex.lock();
    _currentScriptName = filename;
    _mutex.unlock();
    _thread.launch();
    return true;
}

void CLua::OnCleanup()
{
    if (_luaState != NULL)
        lua_close(_luaState);

    _thread.terminate();
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

int CLua::ResumeLuaThread()
{
    int __result = GetLuaThreadStatus();
    if (__result == LUA_YIELD)
    {
        __result = lua_resume(_luaThread, NULL, 0);
        if (LUA_YIELD < __result)
        {
            cout << "[LUA]:" << lua_tostring(_luaThread, -1) << endl;
        }
    }

    return __result;
}
