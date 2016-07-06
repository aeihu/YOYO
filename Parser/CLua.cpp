/*
* Copyright (C) 2012-2016, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CLua.h"
#include "CScriptCommand.h"

CLua CLua::_Lua;

CLua::CLua() : _thread(&CLua::RunScript, this)
{
	_luaState = NULL;
	_currentScriptName = "";
}

CLua::~CLua()
{
}

int CLua::OnInit()
{
	_luaState = luaL_newstate();

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
	//2.设置待注册的Lua标准库，这个库是给你的Lua脚本用的
	//因为接下来我们只想在Lua脚本里面输出hello world，所以只引入基本库就可以了
	static const luaL_Reg lualibs[] =
	{
		{ "base", luaopen_base },
		{ NULL, NULL }
	};
	//3.注册Lua标准库并清空栈
	const luaL_Reg *lib = lualibs;
	for (; lib->func != NULL; lib++)
	{
		luaL_requiref(_luaState, lib->name, lib->func, 1);
		lua_pop(_luaState, 1);
	}

	return 0;
}

void CLua::RunScript()
{
	lua_State *__luaThread = lua_newthread(_luaState); 
	_mutex.lock();
	luaL_loadfile(__luaThread, _currentScriptName.c_str());
	_mutex.unlock();
	lua_resume(__luaThread, NULL, 0);
}

bool CLua::LoadScript(string filename)
{
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