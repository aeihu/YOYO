/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSCRIPTCOMMAND_H_ 
    #define _CSCRIPTCOMMAND_H_
#include <string>
#include <map>
#include <vector>
#include "../Common/CActionSet.h"

using namespace std;

bool Cmd_AddPosition(vector<string>& args, CActionSet* act);//(string name, float x, float y);
bool Cmd_DelPosition(vector<string>& args, CActionSet* act);//(string name);

bool Cmd_ShowCharacterLayer(vector<string>& args, CActionSet* act);
bool Cmd_HideCharacterLayer(vector<string>& args, CActionSet* act);
bool Cmd_MoveCharacterLayer(vector<string>& args, CActionSet* act);
bool Cmd_ScaleCharacterLayer(vector<string>& args, CActionSet* act);
bool Cmd_RotationCharacterLayer(vector<string>& args, CActionSet* act);
bool Cmd_SetFaceCharacterLayer(vector<string>& args, CActionSet* act);
bool Cmd_SetCharacterLayerOrder(vector<string>& args, CActionSet* act);

bool Cmd_ShowBackground(vector<string>& args, CActionSet* act);//(string name, int inrc, bool pause);
bool Cmd_HideBackground(vector<string>& args, CActionSet* act);//(string name, int inrc, bool pause);
bool Cmd_MoveBackground(vector<string>& args, CActionSet* act);
bool Cmd_ScaleBackground(vector<string>& args, CActionSet* act);
bool Cmd_RotationBackground(vector<string>& args, CActionSet* act);
bool Cmd_SetBackgroundLayerOrder(vector<string>& args, CActionSet* act);
////
bool Cmd_ShowImg(vector<string>& args, CActionSet* act);//(string name, int inrc, bool pause);
bool Cmd_HideImg(vector<string>& args, CActionSet* act);//(string name, int inrc, bool pause);
bool Cmd_MoveImg(vector<string>& args, CActionSet* act);
bool Cmd_ScaleImg(vector<string>& args, CActionSet* act);
bool Cmd_RotationImg(vector<string>& args, CActionSet* act);
bool Cmd_SetImgLayerOrder(vector<string>& args, CActionSet* act);

bool Cmd_PlayBGM(vector<string>& args, CActionSet* act);//(const char* filename);
bool Cmd_PauseBGM(vector<string>& args, CActionSet* act);//();
bool Cmd_ResumeBGM(vector<string>& args, CActionSet* act);//();

bool Cmd_DelSE(vector<string>& args, CActionSet* act);//(string name);
bool Cmd_PlaySE(vector<string>& args, CActionSet* act);//(const char* name);

bool Cmd_ShowButton(vector<string>& args, CActionSet* act);//(string name, int incr, bool pause);
bool Cmd_HideButton(vector<string>& args, CActionSet* act);//(string name, int incr, bool pause);
bool Cmd_MoveButton(vector<string>& args, CActionSet* act);
bool Cmd_ScaleButton(vector<string>& args, CActionSet* act);
bool Cmd_RotationButton(vector<string>& args, CActionSet* act);
bool Cmd_SetButtonLayerOrder(vector<string>& args, CActionSet* act);

bool Cmd_Message(vector<string>& args, CActionSet* act);//(string name, string msg);
bool Cmd_ShowMessageBox(vector<string>& args, CActionSet* act);//(string name, int incr, bool pause);
bool Cmd_HideMessageBox(vector<string>& args, CActionSet* act);//(string name, int incr, bool pause);
bool Cmd_SetMessageBoxLayerOrder(vector<string>& args, CActionSet* act);

bool Cmd_ShowLogBox(vector<string>& args, CActionSet* act);
bool Cmd_HideLogBox(vector<string>& args, CActionSet* act);
bool Cmd_SetLogBoxLayerOrder(vector<string>& args, CActionSet* act);

bool Cmd_ShowParticleSystem(vector<string>& args, CActionSet* act);
bool Cmd_HideParticleSystem(vector<string>& args, CActionSet* act);
bool Cmd_SetParticleSystemLayerOrder(vector<string>& args, CActionSet* act);

bool Cmd_AddVariable(vector<string>& args, CActionSet* act);//(string name, string val, map<string, string> &var_table);
bool Cmd_SetVariable(vector<string>& args, CActionSet* act);//(string name, string val, map<string, string> &var_table);
bool Cmd_DelVariable(vector<string>& args, CActionSet* act);//(string name, map<string, string> &var_table);

bool Cmd_UseCamera(vector<string>& args, CActionSet* act);
bool Cmd_MoveCamera(vector<string>& args, CActionSet* act);
bool Cmd_ScaleCamera(vector<string>& args, CActionSet* act);
bool Cmd_RotationCamera(vector<string>& args, CActionSet* act);
//bool Cmd_DelCamera(vector<string>&);

#endif
