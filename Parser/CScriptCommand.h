/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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

//int Cmd_Move(const char* name, int x, int y, bool pause);
//bool Cmd_ViewPoint(const char* name);
//bool Cmd_ViewPointMove(int x, int y);
//
//int Cmd_DeleteCharacter(const char* name);
//bool Cmd_CreateCharacter(const char* name, int x, int y, const char* filename, int width, int height, int maxframes, bool isNPC);
//
bool Cmd_ShowInfo(vector<string>);//

bool Cmd_AddPosition(vector<string>);//(string name, float x, float y);
bool Cmd_DelPosition(vector<string>);//(string name);
bool Cmd_AddCharacterLayer(vector<string>);
bool Cmd_DelCharacterLayer(vector<string>);
bool Cmd_ShowCharacterLayer(vector<string>);//(string name, const char* filename, string position, char type, float buf, float incr, bool pause);
bool Cmd_HideCharacterLayer(vector<string>);//(string name, char type, float buf, float incr, bool pause);
bool Cmd_MoveCharacterLayer(vector<string>);//(string name, float x, float y, float incr, bool pause);
bool Cmd_SetFaceCharacterLayer(vector<string>);//(string name, string face);
////bool Cmd_AlphaCharacterLayer(char postion, int alpha);
////
////bool Cmd_LoadMap(const char* name);
////bool Cmd_LoadScript(const char* filename, const char* Section);
////
bool Cmd_AddBackground(vector<string>);//(string name, const char* filename, float x=0.0f, float y=0.0f);
bool Cmd_ShowBackground(vector<string>);//(string name, int inrc, bool pause);
bool Cmd_HideBackground(vector<string>);//(string name, int inrc, bool pause);
bool Cmd_DelBackground(vector<string>);//(string name);
////
bool Cmd_AddImg(vector<string>);//(string name, const char* filename, float x=0.0f, float y=0.0f);
bool Cmd_ShowImg(vector<string>);//(string name, int inrc, bool pause);
bool Cmd_HideImg(vector<string>);//(string name, int inrc, bool pause);
bool Cmd_DelImg(vector<string>);//(string name);
////
////void Cmd_WhiteScreen(int msec);
////void Cmd_BlackScreen(int msec);
////
//bool Cmd_Say(vector<string>);//(const char* filename);
//
bool Cmd_PlayBGM(vector<string>);//(const char* filename);
bool Cmd_PauseBGM(vector<string>);//();
bool Cmd_ResumeBGM(vector<string>);//();
////
bool Cmd_AddSE(vector<string>);//(vector<string>);//(const char* name, const char* filename);
bool Cmd_DelSE(vector<string>);//(string name);
bool Cmd_PlaySE(vector<string>);//(const char* name);

bool Cmd_AddVoice(vector<string>);
bool Cmd_DelVoice(vector<string>);
////
bool Cmd_AddButton(vector<string>);//(string name, const char* filename);
bool Cmd_DelButton(vector<string>);//(string name);
bool Cmd_ShowButton(vector<string>);//(string name, int incr, bool pause);
bool Cmd_HideButton(vector<string>);//(string name, int incr, bool pause);
////
////void Cmd_FullScreen();
////void Cmd_Window();
////
////void Cmd_SetFontShadow(bool b);
bool Cmd_Message(vector<string>);//(string name, string msg);
////bool Cmd_SetMessageBoxSpeakerName(string name);
bool Cmd_AddMessageBox(vector<string>);//(string name, const char* filename);
bool Cmd_DelMessageBox(vector<string>);//(string name);
bool Cmd_ShowMessageBox(vector<string>);//(string name, int incr, bool pause);
bool Cmd_HideMessageBox(vector<string>);//(string name, int incr, bool pause);
////
////bool Cmd_MenuBoxAddBtn(string name, const char* filename, const char* section);
////bool Cmd_MenuBoxDelBtn(string name);
////int Cmd_ShowMenuBox(const char* filename, const char* section, bool pause);
////bool Cmd_HideMenuBox(bool pause);
////
////bool Cmd_ShowInfoBox(bool pause);
////bool Cmd_HideInfoBox(bool pause);
////void Cmd_PrintInfoBox(string id);
////
////bool Cmd_ShowLogBox(bool pause);
////bool Cmd_HideLogBox(bool pause);
////
////bool Cmd_AddVariable(string name, string val, map<string, string> &var_table);
////bool Cmd_SetVariable(string name, string val, map<string, string> &var_table);
////bool Cmd_DelVariable(string name, map<string, string> &var_table);
////
////void Cmd_DelCommand(vector<string> &cmdlist, int num);
////bool Cmd_DelCommand(vector<string> &cmdlist, string flag);
////
////bool Cmd_AddMapEvent(string name, const char* filename, const char* section);
////bool Cmd_AddMapEventPoint(string name, int x, int y);
////bool Cmd_DelMapEvent(string name);
////void Cmd_ClearMapEvent();
////
////bool Cmd_EditEquipList(string id, int num);
////bool Cmd_EditItemList(string id, int num);
////void Cmd_EditMoney(int num);
////
////bool Cmd_PlayAnimation(string name, int x, int y);
////int Cmd_ToNextAnimationData(string name);
////int Cmd_StopAnimation(string name);
////int Cmd_AddAnimationScript(string name, int framerate);
////int Cmd_DelAnimationScript(string name);
////int Cmd_AddAnimationData(string scrname,string dataname,string filename, 
////    int startindex, int maxframes, bool loop, int size, string se);
////int Cmd_DelAnimationData(string scrname, string dataname);
////
////int Cmd_If(string op, string val1, string val2);
#endif
