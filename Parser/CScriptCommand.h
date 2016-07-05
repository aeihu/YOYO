/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CSCRIPTCOMMAND_H_ 
    #define _CSCRIPTCOMMAND_H_
#include <string>
#include "../Action/CActionSet.h"
#include "lua.hpp"

using namespace std;

int Cmd_ShowCharacterLayer(lua_State* args);
int Cmd_HideCharacterLayer(lua_State* args);
int Cmd_MoveCharacterLayer(lua_State* args);
int Cmd_ScaleCharacterLayer(lua_State* args);
int Cmd_RotationCharacterLayer(lua_State* args);
int Cmd_SetPoseCharacterLayer(lua_State* args);
int Cmd_SetCharacterLayerOrder(lua_State* args);
int Cmd_FlipXCharacterLayer(lua_State* args);
int Cmd_FlipYCharacterLayer(lua_State* args);
int Cmd_OriginCharacterLayer(lua_State* args);
int Cmd_ColorCharacterLayer(lua_State* args);

int Cmd_ShowImg(lua_State* args);
int Cmd_HideImg(lua_State* args);
int Cmd_MoveImg(lua_State* args);
int Cmd_ScaleImg(lua_State* args);
int Cmd_RotationImg(lua_State* args);
int Cmd_SetImgLayerOrder(lua_State* args);
int Cmd_FlipXImg(lua_State* args);
int Cmd_FlipYImg(lua_State* args);
int Cmd_OriginImg(lua_State* args);
int Cmd_ColorImg(lua_State* args);

int Cmd_ShowText(lua_State* args);
int Cmd_HideText(lua_State* args);
int Cmd_MoveText(lua_State* args);
int Cmd_ScaleText(lua_State* args);
int Cmd_RotationText(lua_State* args);
int Cmd_SetTextLayerOrder(lua_State* args);
int Cmd_OriginText(lua_State* args);
int Cmd_SetText(lua_State* args);
int Cmd_ColorText(lua_State* args);

int Cmd_PlayBGM(lua_State* args);
int Cmd_SetBGMVolume(lua_State* args);
int Cmd_PauseBGM(lua_State* args);
int Cmd_ResumeBGM(lua_State* args);
int Cmd_StopBGM(lua_State* args);

int Cmd_StopSE(lua_State* args);
int Cmd_PlaySE(lua_State* args);

int Cmd_ShowButton(lua_State* args);
int Cmd_HideButton(lua_State* args);
int Cmd_MoveButton(lua_State* args);
int Cmd_ScaleButton(lua_State* args);
int Cmd_RotationButton(lua_State* args);
int Cmd_SetButtonLayerOrder(lua_State* args);
int Cmd_FlipXButton(lua_State* args);
int Cmd_FlipYButton(lua_State* args);
int Cmd_OriginButton(lua_State* args);
int Cmd_ColorButton(lua_State* args);

int Cmd_Message(lua_State* args);
int Cmd_ShowMessageBox(lua_State* args);
int Cmd_HideMessageBox(lua_State* args);
int Cmd_SetMessageBoxLayerOrder(lua_State* args);
int Cmd_CleanMessageBox(lua_State* args);

int Cmd_ShowLogBox(lua_State* args);
int Cmd_HideLogBox(lua_State* args);
int Cmd_SetLogBoxLayerOrder(lua_State* args);

//int Cmd_ShowParticleSystem(lua_State* args);
//int Cmd_HideParticleSystem(lua_State* args);
//int Cmd_SetParticleSystemLayerOrder(lua_State* args);

//int Cmd_AddVariable(lua_State* args);
//int Cmd_SetVariable(lua_State* args);
//int Cmd_DelVariable(lua_State* args);

int Cmd_DelAction(lua_State* args);
int Cmd_SkipAction(lua_State* args);

int Cmd_ShowCurtain(lua_State* args);
int Cmd_HideCurtain(lua_State* args);
int Cmd_ColorCurtain(lua_State* args);

int Cmd_UseCamera(lua_State* args);
int Cmd_MoveCamera(lua_State* args);
int Cmd_ScaleCamera(lua_State* args);
int Cmd_RotationCamera(lua_State* args);

int Cmd_Pause(lua_State* args);
int Cmd_LoadScript(lua_State* args);

#endif
