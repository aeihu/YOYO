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

using namespace std;

//bool Cmd_ShowInfo(vector<string>&);//

bool Cmd_AddPosition(vector<string>&);//(string name, float x, float y);
bool Cmd_DelPosition(vector<string>&);//(string name);
//bool Cmd_AddCharacterLayer(vector<string>);
//bool Cmd_DelCharacterLayer(vector<string>);
bool Cmd_ShowCharacterLayer(vector<string>&);//(string name, const char* filename, string position, char type, float buf, float incr, bool pause);
bool Cmd_HideCharacterLayer(vector<string>&);//(string name, char type, float buf, float incr, bool pause);
bool Cmd_MoveCharacterLayer(vector<string>&);//(string name, float x, float y, float incr, bool pause);
bool Cmd_SetFaceCharacterLayer(vector<string>&);//(string name, string face);
bool Cmd_SetCharacterLayerOrder(vector<string>&);

//bool Cmd_AddBackground(vector<string>);//(string name, const char* filename, float x=0.0f, float y=0.0f);
bool Cmd_ShowBackground(vector<string>&);//(string name, int inrc, bool pause);
bool Cmd_HideBackground(vector<string>&);//(string name, int inrc, bool pause);
//bool Cmd_DelBackground(vector<string>);//(string name);
bool Cmd_SetBackgroundLayerOrder(vector<string>&);
////
//bool Cmd_AddImg(vector<string>);//(string name, const char* filename, float x=0.0f, float y=0.0f);
bool Cmd_ShowImg(vector<string>&);//(string name, int inrc, bool pause);
bool Cmd_HideImg(vector<string>&);//(string name, int inrc, bool pause);
//bool Cmd_DelImg(vector<string>);//(string name);
bool Cmd_SetImgLayerOrder(vector<string>&);

bool Cmd_PlayBGM(vector<string>&);//(const char* filename);
bool Cmd_PauseBGM(vector<string>&);//();
bool Cmd_ResumeBGM(vector<string>&);//();
////
//bool Cmd_AddSE(vector<string>);//(vector<string>);//(const char* name, const char* filename);
bool Cmd_DelSE(vector<string>&);//(string name);
bool Cmd_PlaySE(vector<string>&);//(const char* name);

//bool Cmd_AddVoice(vector<string>);
//bool Cmd_DelVoice(vector<string>);
////
//bool Cmd_AddButton(vector<string>);//(string name, const char* filename);
//bool Cmd_DelButton(vector<string>);//(string name);
bool Cmd_ShowButton(vector<string>&);//(string name, int incr, bool pause);
bool Cmd_HideButton(vector<string>&);//(string name, int incr, bool pause);
bool Cmd_SetButtonLayerOrder(vector<string>&);

bool Cmd_Message(vector<string>&);//(string name, string msg);
//bool Cmd_AddMessageBox(vector<string>);//(string name, const char* filename);
//bool Cmd_DelMessageBox(vector<string>);//(string name);
bool Cmd_ShowMessageBox(vector<string>&);//(string name, int incr, bool pause);
bool Cmd_HideMessageBox(vector<string>&);//(string name, int incr, bool pause);
bool Cmd_SetMessageBoxLayerOrder(vector<string>&);

//bool Cmd_AddLogBox(vector<string>);
bool Cmd_ShowLogBox(vector<string>&);
bool Cmd_HideLogBox(vector<string>&);
//bool Cmd_DelLogBox(vector<string>);
bool Cmd_SetLogBoxLayerOrder(vector<string>&);

//bool Cmd_AddParticleSystem(vector<string>);
//bool Cmd_DelParticleSystem(vector<string>);
bool Cmd_ShowParticleSystem(vector<string>&);
bool Cmd_HideParticleSystem(vector<string>&);
bool Cmd_SetParticleSystemLayerOrder(vector<string>&);

//bool Cmd_AddFont(vector<string>);
//bool Cmd_DelFont(vector<string>);

bool Cmd_AddVariable(vector<string>&);//(string name, string val, map<string, string> &var_table);
bool Cmd_SetVariable(vector<string>&);//(string name, string val, map<string, string> &var_table);
bool Cmd_DelVariable(vector<string>&);//(string name, map<string, string> &var_table);

bool Cmd_UseCamera(vector<string>&);
//bool Cmd_DelCamera(vector<string>&);

#endif
