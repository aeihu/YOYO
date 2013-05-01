/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSCRIPTCOMMAND_H_ 
    #define _CSCRIPTCOMMAND_H_
#include <string>
#include <map>

using namespace std;

//int Cmd_Move(const char* name, int x, int y, bool pause);
//bool Cmd_ViewPoint(const char* name);
//bool Cmd_ViewPointMove(int x, int y);
//
//int Cmd_DeleteCharacter(const char* name);
//bool Cmd_CreateCharacter(const char* name, int x, int y, const char* filename, int width, int height, int maxframes, bool isNPC);
//

void Cmd_AddPosition(string name, float x, float y);
void Cmd_DelPosition(string name);
bool Cmd_ShowCharacterLayer(string name, const char* filename, float x, float y, char type, float buf, float incr, bool pause);
bool Cmd_ShowCharacterLayer(string name, const char* filename, string position, char type, float buf, float incr, bool pause);
bool Cmd_HideCharacterLayer(string name, char type, float buf, float incr, bool pause);
bool Cmd_MoveCharacterLayer(string name, float x, float y, float incr, bool pause);
bool Cmd_MoveCharacterLayer(string name, string position, float incr, bool pause);
void Cmd_SetFaceCharacterLayer(string name, string face);
//bool Cmd_AlphaCharacterLayer(char postion, int alpha);
//
//bool Cmd_LoadMap(const char* name);
//bool Cmd_LoadScript(const char* filename, const char* Section);
//
bool Cmd_ShowBackground(const char* filename, float x, float y, int inrc, int msec);
bool Cmd_HideBackground(int inrc, int msec);
//
bool Cmd_ShowImg(string name, const char* filename, float x, float y,  int inrc, int msec, bool pause);
bool Cmd_HideImg(string name, int inrc, int msec, bool pause);
//
//void Cmd_WhiteScreen(int msec);
//void Cmd_BlackScreen(int msec);
//
bool Cmd_Say(const char* filename);

bool Cmd_PlayBGM(const char* filename);
void Cmd_PauseBGM();
void Cmd_ResumeBGM();
//
int Cmd_AddSE(const char* name, const char* filename);
bool Cmd_DelSE(string name);
bool Cmd_PlaySE(const char* name);
//
bool Cmd_AddButton(string name, const char* filename);
bool Cmd_DelButton(string name);
bool Cmd_ShowButton(string name, int incr, int msec, bool pause);
bool Cmd_HideButton(string name, int incr, int msec, bool pause);
//
//void Cmd_FullScreen();
//void Cmd_Window();
//
//void Cmd_SetFontShadow(bool b);
bool Cmd_Message(string name, string msg);
//bool Cmd_SetMessageBoxSpeakerName(string name);
bool Cmd_AddMessageBox(string name, const char* filename);
bool Cmd_DelMessageBox(string name);
bool Cmd_ShowMessageBox(string name, int incr, int msec, bool pause);
bool Cmd_HideMessageBox(string name, int incr, int msec, bool pause);
//
//bool Cmd_MenuBoxAddBtn(string name, const char* filename, const char* section);
//bool Cmd_MenuBoxDelBtn(string name);
//int Cmd_ShowMenuBox(const char* filename, const char* section, bool pause);
//bool Cmd_HideMenuBox(bool pause);
//
//bool Cmd_ShowInfoBox(bool pause);
//bool Cmd_HideInfoBox(bool pause);
//void Cmd_PrintInfoBox(string id);
//
//bool Cmd_ShowLogBox(bool pause);
//bool Cmd_HideLogBox(bool pause);
//
//bool Cmd_AddVariable(string name, string val, map<string, string> &var_table);
//bool Cmd_SetVariable(string name, string val, map<string, string> &var_table);
//bool Cmd_DelVariable(string name, map<string, string> &var_table);
//
//void Cmd_DelCommand(vector<string> &cmdlist, int num);
//bool Cmd_DelCommand(vector<string> &cmdlist, string flag);
//
//bool Cmd_AddMapEvent(string name, const char* filename, const char* section);
//bool Cmd_AddMapEventPoint(string name, int x, int y);
//bool Cmd_DelMapEvent(string name);
//void Cmd_ClearMapEvent();
//
//bool Cmd_EditEquipList(string id, int num);
//bool Cmd_EditItemList(string id, int num);
//void Cmd_EditMoney(int num);
//
//bool Cmd_PlayAnimation(string name, int x, int y);
//int Cmd_ToNextAnimationData(string name);
//int Cmd_StopAnimation(string name);
//int Cmd_AddAnimationScript(string name, int framerate);
//int Cmd_DelAnimationScript(string name);
//int Cmd_AddAnimationData(string scrname,string dataname,string filename, 
//	int startindex, int maxframes, bool loop, int size, string se);
//int Cmd_DelAnimationData(string scrname, string dataname);
//
//int Cmd_If(string op, string val1, string val2);
#endif
