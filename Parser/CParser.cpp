/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CParser.h"
#include  <cstring>

CParser CParser::parser;

CParser::CParser()
{
	_Delay = 0;
	_pRunning = NULL;
}

void CParser::SetRunning(bool* running)
{
	_pRunning = running;
}

void CParser::SetDeplay(int ms)
{
	_Delay =  ms + CCommon::common.GetTicks();
}

bool CParser::IsDeplaying()
{
	return (CCommon::common.GetTicks() < _Delay ? true : false);
}

bool CParser::FindSection(list<string> &Commands, const char* Section)
{
	for (list<string>::iterator it=Commands.begin();
		it!=Commands.end(); it++){
		if (Cio::IsNested((*it),'[',']')){
			if ((*it).find(Section) != string::npos){
				Commands.erase(Commands.begin(), ++it);
				return true;
			}
		}
	}

	return false;
}

bool CParser::LoadScript(const char* FileName, const char* Section, list<string> &Commands)
{
	list<string> __commands = Cio::LoadTxtFile(FileName, ";]", false);

	if (Section != NULL)
	{
		if (!FindSection(__commands, Section))
		{
			cout << "LoadScript(): can't find section [" << Section << "]"<<endl;
			return false;
		}
	}
	
	for (list<string>::iterator it=__commands.begin();
		it!=__commands.end(); it++){
		if ((*it).find("@end") != string::npos){
			__commands.erase(it, __commands.end());
			break;
		}

		(*it).erase((*it).find_last_of(";"),1);
		while ((*it).find_first_of("\n\r") != string::npos)
			(*it).erase((*it).find_first_of("\n\r"),1);
	}
	
	Commands.insert(Commands.begin(), __commands.begin(), __commands.end());

	return true;
}


bool CParser::LoadScript(const char* FileName, const char* Section)
{
	if (CParser::LoadScript(FileName, Section, _CmdList))
	{
		//Pause = false;
		return true;
	}
	else
		return false;
}

void CParser::OnCleanup() {
	_CmdList.clear();
	_pRunning = NULL;
}


void CParser::ExecuteCmd(string cmd)
{
	vector<string> cmd_para_list;
	//sscanf(cmd.c_str()," @%[^ ;]", command);

	switch (AnalysisOfParameters(cmd, cmd_para_list))
	{
		case 0:
		break;
		case 1:
//			if (cmd_para_list[0] == "@pause_bgm")
//			{
//				Cmd_PauseBGM();
//			}
//			else if (cmd_para_list[0] == "@resume_bgm")
//			{
//				Cmd_ResumeBGM();
//			}
//			else if (cmd_para_list[0] == "@fullscreen")
//			{
//				Cmd_FullScreen();
//			}
//			else if (cmd_para_list[0] == "@window")
//			{
//				Cmd_Window();
//			}
			//else 
			if (cmd_para_list[0] == "@hide_bg")
			{
				Cmd_HideBackground(
					CCommon::common.BACKGROUNDLAYER_ALPHA_INCREMENT,
					CCommon::common.BACKGROUNDLAYER_ALPHA_INTERVAL);
			}
//			else if (cmd_para_list[0] == "@hide_menubox")
//			{
//				if (!Cmd_HideMenuBox(false))
//					cout << "Cmd_HideMenuBox(): menubox has been hidden." <<endl;
//			}
//			else if (cmd_para_list[0] == "@phide_menubox")
//			{
//				if (!Cmd_HideMenuBox(true))
//					cout << "Cmd_HideMenuBox(): menubox has been hidden." <<endl;
//				else
//					Pause = true;
//			}
//			else if (cmd_para_list[0] == "@show_infobox")
//			{
//				if (!Cmd_ShowInfoBox(false))
//					cout << "Cmd_ShowInfoBox(): infobox has been shown." <<endl;
//			}
//			else if (cmd_para_list[0] == "@pshow_infobox")
//			{
//				if (!Cmd_ShowInfoBox(true))
//					cout << "Cmd_ShowInfoBox(): infobox has been shown." <<endl;
//				else
//					Pause = true;
//			}
//			else if (cmd_para_list[0] == "@hide_infobox")
//			{
//				if (!Cmd_HideInfoBox(false))
//					cout << "Cmd_HideInfoBox(): infobox has been hidden." <<endl;
//			}
//			else if (cmd_para_list[0] == "@phide_infobox")
//			{
//				if (!Cmd_HideInfoBox(true))
//					cout << "Cmd_HideInfoBox(): infobox has been hidden." <<endl;
//				else
//					Pause = true;
//			}
//			
//			else if (cmd_para_list[0] == "@show_logbox")
//			{
//				if (!Cmd_ShowLogBox(false))
//					cout << "Cmd_ShowLogBox(): logbox has been shown." <<endl;
//			}
//			else if (cmd_para_list[0] == "@pshow_logbox")
//			{
//				if (!Cmd_ShowLogBox(true))
//					cout << "Cmd_ShowLogBox(): logbox has been shown." <<endl;
//				else
//					Pause = true;
//			}
//			else if (cmd_para_list[0] == "@hide_logbox")
//			{
//				if (!Cmd_HideLogBox(false))
//					cout << "Cmd_HideLogBox(): logbox has been hidden." <<endl;
//			}
//			else if (cmd_para_list[0] == "@phide_logbox")
//			{
//				if (!Cmd_HideLogBox(true))
//					cout << "Cmd_HideLogBox(): logbox has been hidden." <<endl;
//				else
//					Pause = true;
//			}
//
//			else if (cmd_para_list[0] == "@clear_event")
//			{
//				Cmd_ClearMapEvent();
//			}
			else if (cmd_para_list[0] == "@exit")
			{
				if (_pRunning != NULL)
					*_pRunning = false;
			}
			else
			{
				goto flag_default;
				//cout << "syntax error: " << cmd << "." << endl;
			}
		break;
		case 2:
			if (cmd_para_list[0] == "@say")
			{
				if (!Cmd_Say(cmd_para_list[1].c_str()))
					cout << "Cmd_Say(): failed to play voice \""<< cmd_para_list[1] << "\"." <<endl;
			}
			else if (cmd_para_list[0] == "@play_se")
			{
				if (!Cmd_PlaySE(cmd_para_list[1].c_str()))
					cout << "Cmd_PlaySE(): can't find SE \""<< cmd_para_list[1] << "\"." <<endl;
			}
			else if (cmd_para_list[0] == "@hide_img")
			{
				Cmd_HideImg(cmd_para_list[1].c_str() ,
					CCommon::common.IMAGELAYER_ALPHA_INCREMENT,
					CCommon::common.IMAGELAYER_ALPHA_INTERVAL,true);
			}
			else if (cmd_para_list[0] == "@deplay")
			{
				SetDeplay(atoi(cmd_para_list[1].c_str()));
			}
//			else if (cmd_para_list[0] == "@speaker")
//			{
//				if (!Cmd_SetMessageBoxSpeakerName(cmd_para_list[1]))
//					cout << "Cmd_SetMessageBoxSpeakerName(): failed to set speaker name." <<endl;
//			}
//			else if (cmd_para_list[0] == "@viewpoint")
//			{
//				if (!Cmd_ViewPoint(cmd_para_list[1].c_str()))
//					cout << "Cmd_ViewPoint(): can't find character \"" << cmd_para_list[1] << "\"." <<endl;
//			}
			else if (cmd_para_list[0] == "@play_bgm")
			{
				if (!Cmd_PlayBGM(cmd_para_list[1].c_str()))
					cout << "Cmd_PlayBGM(): failed to play BGM \"" << cmd_para_list[1] << "\"." <<endl;
			}
			else if (cmd_para_list[0] == "@del_se")
			{
				if (!Cmd_DelSE(cmd_para_list[1].c_str()))
					cout << "Cmd_DelSE(): can't find SE \""<< cmd_para_list[1] << "\"." <<endl;
			}
			else if (cmd_para_list[0] == "@del_position")
			{
				Cmd_DelPosition(cmd_para_list[1]);
			}
			else if (cmd_para_list[0] == "@show_msgbox")
			{
				Cmd_ShowMessageBox(cmd_para_list[1],
					CCommon::common.BOX_ALPHA_INCREMENT,
					CCommon::common.BOX_ALPHA_INTERVAL,
					true);
			}
			else if (cmd_para_list[0] == "@hide_msgbox")
			{
				Cmd_HideMessageBox(cmd_para_list[1],
					CCommon::common.BOX_ALPHA_INCREMENT,
					CCommon::common.BOX_ALPHA_INTERVAL,
					true);
			}
			else if (cmd_para_list[0] == "@del_msgbox")
			{
				Cmd_DelMessageBox(cmd_para_list[1]);
			}
			else if (cmd_para_list[0] == "@show_btn")
			{
				Cmd_ShowButton(cmd_para_list[1],
					CCommon::common.BOX_ALPHA_INCREMENT,
					CCommon::common.BOX_ALPHA_INTERVAL,
					true);
			}
			else if (cmd_para_list[0] == "@hide_btn")
			{
				Cmd_HideButton(cmd_para_list[1],
					CCommon::common.BOX_ALPHA_INCREMENT,
					CCommon::common.BOX_ALPHA_INTERVAL,
					true);
			}
			else if (cmd_para_list[0] == "@del_btn")
			{
				Cmd_DelButton(cmd_para_list[1]);
			}



//			else if (cmd_para_list[0] == "@del_xpc")
//			{
//				int result = Cmd_DeleteCharacter(cmd_para_list[1].c_str());
//				cout << "Cmd_DeleteCharacter(): delete "<< result << " of character(s)."  <<endl;
//			}
//			else if (cmd_para_list[0] == "@map")
//			{
//				if (!Cmd_LoadMap(cmd_para_list[1].c_str()))
//					cout << "Cmd_LoadMap(): failed to load map \"" << cmd_para_list[1] <<"\"." <<endl;
//			}
//			else if (cmd_para_list[0] == "@wscreen")
//			{
//				Cmd_WhiteScreen(atoi(cmd_para_list[1].c_str()));
//			}
//			else if (cmd_para_list[0] == "@bscreen")
//			{
//				Cmd_BlackScreen(atoi(cmd_para_list[1].c_str()));
//			}
//			else if (cmd_para_list[0] == "@edit_money")
//			{
//				Cmd_EditMoney(atoi(cmd_para_list[1].c_str()));
//			}
			else if (cmd_para_list[0] == "@show_bg")
			{
				Cmd_ShowBackground(cmd_para_list[1].c_str(),
						CCommon::common.BACKGROUNDLAYER_X,
						CCommon::common.BACKGROUNDLAYER_Y,
						CCommon::common.BACKGROUNDLAYER_ALPHA_INCREMENT,
						CCommon::common.BACKGROUNDLAYER_ALPHA_INTERVAL);
			}
//			else if (cmd_para_list[0] == "@delay")
//			{
//				Cmd_Delay(atoi(cmd_para_list[1].c_str()));
//			}
//			else if (cmd_para_list[0] == "@del_menubtn")
//			{
//				if(!Cmd_MenuBoxDelBtn(cmd_para_list[1]))
//					cout << "Cmd_MenuBoxDelBtn(): failed to delete MenuBoxButton \"" << cmd_para_list[1] << "\"." <<endl;
//			}
//			else if (cmd_para_list[0] == "@del_var")
//			{
//				if (!Cmd_DelVariable(cmd_para_list[1], CCommon::common.PlayerVariableTable))
//					cout << "Cmd_DelVariable(): variable \""<< cmd_para_list[1] << "\" has not existed in player variable table." <<endl;
//			}
//			else if (cmd_para_list[0] == "@del_sys_var")
//			{
//				if (!Cmd_DelVariable(cmd_para_list[1], CCommon::common.SystemVariableTable))
//					cout << "Cmd_DelVariable(): variable \""<< cmd_para_list[1] << "\" has not existed in system variable table." <<endl;
//			}
//			else if (cmd_para_list[0] == "@ldel_cmd")
//			{
//				Cmd_DelCommand(_CmdList, atoi(cmd_para_list[1].c_str()));
//			}
//			else if (cmd_para_list[0] == "@fdel_cmd")
//			{
//				if(!Cmd_DelCommand(_CmdList, cmd_para_list[1]))
//					cout << "Cmd_DelCommand(): can't find flag \"#"<< cmd_para_list[1] << "\"." <<endl;
//			}
//			else if (cmd_para_list[0] == "@del_event")
//			{
//				if (!Cmd_DelMapEvent(cmd_para_list[1]))
//					cout << "Cmd_DelMapEvent(): can't find event \""<< cmd_para_list[1] <<"\"." <<endl;
//			}
//			else if (cmd_para_list[0] == "@del_anime_src")
//			{
//				switch (Cmd_DelAnimationScript(cmd_para_list[1]))
//				{
//					case -1:
//						cout << "Cmd_DelAnimationScript(): animation script \""<< cmd_para_list[1] << "\" has not existed." <<endl;
//					break;
//					case 0:
//						cout << "Cmd_DelAnimationScript(): can't delete animation script \""<< cmd_para_list[1] << "\" when it's running." <<endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@next_anime_data")
//			{
//				switch (Cmd_ToNextAnimationData(cmd_para_list[1]))
//				{
//					case -2:
//						cout << "Cmd_ToNextAnimationData(): animation script \""<< cmd_para_list[1] << "\" isn't running." <<endl;
//					break;
//					case -1:
//						cout << "Cmd_ToNextAnimationData(): animation script \""<< cmd_para_list[1] << "\" has not existed." <<endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@stop_anime")
//			{
//				switch (Cmd_ToNextAnimationData(cmd_para_list[1]))
//				{
//					case -2:
//						cout << "Cmd_StopAnimation(): animation script \""<< cmd_para_list[1] << "\" isn't running." <<endl;
//					break;
//					case -1:
//						cout << "Cmd_StopAnimation(): animation script \""<< cmd_para_list[1] << "\" has not existed." <<endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@set_font_shadow")
//			{
//				Cmd_SetFontShadow(atoi(cmd_para_list[1].c_str()));
//			}
			else
			{
				goto flag_default;
				//cout << "syntax error: " << cmd << "." << endl;
			}
		break;
		case 3:
//			if (cmd_para_list[0] == "@lscript")
//			{
//				if (!Cmd_LoadScript(cmd_para_list[1].c_str(), cmd_para_list[2].c_str()))
//					cout << "Cmd_LoadScript(): failed to load script." <<endl;
//			}
//			else if (cmd_para_list[0] == "@vpmove")
//			{
//				Cmd_ViewPointMove(atoi(cmd_para_list[1].c_str()), atoi(cmd_para_list[2].c_str()));
//			}
//			else if (cmd_para_list[0] == "@show_menubox")
//			{
//				switch (Cmd_ShowMenuBox(cmd_para_list[1].c_str(), cmd_para_list[2].c_str(), false))
//				{
//					case -1:
//						cout << "Cmd_ShowMenuBox(): can't load menu button." <<endl;
//					break;
//					case 0:
//						cout << "Cmd_ShowMenuBox(): menubox has been shown." <<endl;
//					break;
//					case 1:
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@pshow_menubox")
//			{
//				switch (Cmd_ShowMenuBox(cmd_para_list[1].c_str(), cmd_para_list[2].c_str(), true))
//				{
//					case -1:
//						cout << "Cmd_ShowMenuBox(): can't load menu button." <<endl;
//					break;
//					case 0:
//						cout << "Cmd_ShowMenuBox(): menubox has been shown." <<endl;
//					break;
//					case 1:
//						Pause = true;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@del_anime_data")
//			{
//				int result = Cmd_DelAnimationData(cmd_para_list[1], cmd_para_list[2]);
//				switch (result)
//				{
//					case -2:
//						cout << "Cmd_DelAnimationData(): can't delete animation data \""<< cmd_para_list[2] << "\" when it's running." <<endl;
//					break;
//					case -1:
//						cout << "Cmd_DelAnimationData(): animation data \""<< cmd_para_list[2] << "\" has not existed." <<endl;
//					break;
//					default:
//						cout << "Cmd_DelAnimationData(): delete "<< result <<  " of animation data(s)." <<endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@add_anime_src")
//			{
//				switch (Cmd_AddAnimationScript(cmd_para_list[1], atoi(cmd_para_list[2].c_str())))
//				{
//					case -1:
//						cout << "Cmd_AddAnimationScript(): framerate cannot be less than 1." <<endl;
//					break;
//					case -2:
//						cout << "Cmd_AddAnimationScript(): animation script \""<< cmd_para_list[1] << "\" has existed." <<endl;
//					break;
//				}
//			}
//			
			//else
			if (cmd_para_list[0] == "@face"){
				Cmd_SetFaceCharacterLayer(cmd_para_list[1], cmd_para_list[2]);
			}
			else if (cmd_para_list[0] == "@show_img")
			{
				Cmd_ShowImg(cmd_para_list[1].c_str(),
					cmd_para_list[2].c_str(),
					CCommon::common.IMAGELAYER_X,
					CCommon::common.IMAGELAYER_Y,
					CCommon::common.IMAGELAYER_ALPHA_INCREMENT,
					CCommon::common.IMAGELAYER_ALPHA_INTERVAL,true);
			}
			else if (cmd_para_list[0] == "@hide_chara")
			{
				Cmd_HideCharacterLayer(cmd_para_list[1],cmd_para_list[2].at(0),
					CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
					CCommon::common.CHARACTERLAYER_MOVE_INCREMENT,false);
			}
			else if (cmd_para_list[0] == "@p_hide_chara")
			{
				Cmd_HideCharacterLayer(cmd_para_list[1],cmd_para_list[2].at(0),
					CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
					CCommon::common.CHARACTERLAYER_MOVE_INCREMENT,true);
			}
			else if (cmd_para_list[0] == "@add_se")
			{
				switch(Cmd_AddSE(cmd_para_list[1].c_str(),cmd_para_list[2].c_str()))
				{
					case -1:
						cout << "Cmd_AddSE(): SE \"" << cmd_para_list[1] << "\" has existed." <<endl;
					break;
					case -2:
						cout << "Cmd_AddSE(): failed to add SE." <<endl;
					break;
				}
			}
			else if (cmd_para_list[0] == "@add_msgbox")
			{
				Cmd_AddMessageBox(cmd_para_list[1],
					cmd_para_list[2].c_str());
			}
			else if (cmd_para_list[0] == "@add_btn")
			{
				Cmd_AddButton(cmd_para_list[1],
					cmd_para_list[2].c_str());
			}

//			else if (cmd_para_list[0] == "@equiplist")
//			{
//				switch (Cmd_EditEquipList(cmd_para_list[1], atoi(cmd_para_list[2].c_str())))
//				{
//					case -1:
//						cout << "Cmd_EditEquipList(): equip \""<< cmd_para_list[1] << "\" has not existed in database." <<endl;
//					break;
//					case -2:
//						cout << "Cmd_EditEquipList(): failed to load equip info." <<endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@itemlist")
//			{
//				switch (Cmd_EditItemList(cmd_para_list[1], atoi(cmd_para_list[2].c_str())))
//				{
//					case -1:
//						cout << "Cmd_EditItemList(): item \""<< cmd_para_list[1] << "\" has not existed in database." <<endl;
//					break;
//					case -2:
//						cout << "Cmd_EditItemList(): failed to load item info." <<endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@set_var")
//			{
//				if (!Cmd_AddVariable(cmd_para_list[1], cmd_para_list[2], CCommon::common.PlayerVariableTable))
//					cout << "Cmd_SetVariable(): variable \""<< cmd_para_list[1] << "\" has not existed in player variable table." <<endl;
//			}
//			else if (cmd_para_list[0] == "@set_sys_var")
//			{
//				if (!Cmd_AddVariable(cmd_para_list[1], cmd_para_list[2], CCommon::common.SystemVariableTable))
//					cout << "Cmd_SetVariable(): variable \""<< cmd_para_list[1] << "\" has not existed in system variable table." <<endl;
//			}
//			else if (cmd_para_list[0] == "@add_var")
//			{
//				if (!Cmd_AddVariable(cmd_para_list[1], cmd_para_list[2], CCommon::common.PlayerVariableTable))
//					cout << "Cmd_AddVariable(): variable \""<< cmd_para_list[1] << "\" has existed in player variable table." <<endl;
//			}
//			else if (cmd_para_list[0] == "@add_sys_var")
//			{
//				if (!Cmd_AddVariable(cmd_para_list[1], cmd_para_list[2], CCommon::common.SystemVariableTable))
//					cout << "Cmd_AddVariable(): variable \""<< cmd_para_list[1] << "\" has existed in system variable table." <<endl;
//			}
//			else if (cmd_para_list[0] == "@hide_chara")
//			{
//				if (!Cmd_HideCharacterLayer(cmd_para_list[1], atoi(cmd_para_list[2].c_str()), false))
//					cout << "Cmd_HideCharacterLayer(): can't find character layer \""<< cmd_para_list[1] <<"\"." <<endl;
//			}
//			else if (cmd_para_list[0] == "@phide_chara")
//			{
//				if (!Cmd_HideCharacterLayer(cmd_para_list[1], atoi(cmd_para_list[2].c_str()), true))
//					cout << "Cmd_HideCharacterLayer(): can't find character layer \""<< cmd_para_list[1] <<"\"." <<endl;
//				else
//					Pause = true;
//			}
			else
			{
				goto flag_default;
				//cout << "syntax error: " << cmd << "." << endl;
			}
		break;
		case 4:
//			if (cmd_para_list[0] == "@move")
//			{
//				if (Cmd_Move(cmd_para_list[1].c_str(), 
//					atoi(cmd_para_list[2].c_str()), 
//					atoi(cmd_para_list[3].c_str()), 
//					false) == 0)
//					cout << "Cmd_Move(): can't find character \"" << cmd_para_list[1] << "\"." <<endl;
//			}
//			else if (cmd_para_list[0] == "@pmove")
//			{
//				if (Cmd_Move(cmd_para_list[1].c_str(), 
//					atoi(cmd_para_list[2].c_str()), 
//					atoi(cmd_para_list[3].c_str()), 
//					true) == 0)
//				{
//					cout << "Cmd_Move(): can't find character \"" << cmd_para_list[1] << "\"." <<endl;
//				}
//				else
//				{
//					Pause = true;
//				}
//			}
//			else if (cmd_para_list[0] == "@add_event")
//			{
//				if (!Cmd_AddMapEvent(cmd_para_list[1], 
//					cmd_para_list[2].c_str(), 
//					cmd_para_list[3].c_str()))
//					cout << "Cmd_AddMapEvent(): failed to load script." <<endl;
//			}
//			else if (cmd_para_list[0] == "@add_eventpoint")
//			{
//				if (!Cmd_AddMapEventPoint(cmd_para_list[1], 
//					atoi(cmd_para_list[2].c_str()), 
//					atoi(cmd_para_list[3].c_str())))
//					cout << "Cmd_AddMapEventPoint(): eventpoint \"event name:" << 
//					cmd_para_list[1] << " X:" <<
//					cmd_para_list[2] << " Y:" <<
//					cmd_para_list[3] << "\" has existed." <<endl;
//			}
//			else
			if (cmd_para_list[0] == "@hide_img")
			{
				Cmd_HideImg(cmd_para_list[1].c_str() ,
					atoi(cmd_para_list[2].c_str()),
					atoi(cmd_para_list[3].c_str()),true);
			}
			else if (cmd_para_list[0] == "@add_position")
			{
				Cmd_AddPosition(cmd_para_list[1],
					atof(cmd_para_list[2].c_str()),
					atof(cmd_para_list[3].c_str()));
			}
			else if (cmd_para_list[0] == "@move_chara")
			{
				Cmd_MoveCharacterLayer(cmd_para_list[1],
					cmd_para_list[2].c_str(),
					atof(cmd_para_list[3].c_str()),
					false);
			}
			else if (cmd_para_list[0] == "@p_move_chara")
			{
				Cmd_MoveCharacterLayer(cmd_para_list[1],
					cmd_para_list[2].c_str(),
					atof(cmd_para_list[3].c_str()),
					true);
			}
//			else if (cmd_para_list[0] == "@play_anime")
//			{
//				switch(!Cmd_PlayAnimation(cmd_para_list[1].c_str(), 
//					atoi(cmd_para_list[2].c_str()),
//					atoi(cmd_para_list[3].c_str())))
//				{
//					case -2:
//						cout << "Cmd_PlayAnimation(): can't find animation script \""<< cmd_para_list[1] << "\"." <<endl;
//					break;
//					case -1:
//						cout << "Cmd_PlayAnimation(): failed to load image." <<endl;
//					break;
//					case 0:
//						cout << "Cmd_PlayAnimation(): animation script \""<< cmd_para_list[1] << "\" has nothing." << endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@add_menubtn")
//			{
//				if(!Cmd_MenuBoxAddBtn(cmd_para_list[1],cmd_para_list[2].c_str(),cmd_para_list[3].c_str()))
//					cout << "Cmd_MenuBoxAddBtn(): failed to add menubox button \"" << cmd_para_list[1] << "\"." <<endl;
//			}
			else
			{
				goto flag_default;
				//cout << "syntax error: " << cmd << "." << endl;
			}
		break;
		case 5:
			if (cmd_para_list[0] == "@show_chara")
			{
				Cmd_ShowCharacterLayer(
					cmd_para_list[1], 
					cmd_para_list[2].c_str(),
					cmd_para_list[3],
					cmd_para_list[4].at(0),
					CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
					CCommon::common.CHARACTERLAYER_MOVE_INCREMENT,
					false);
			}
			else if (cmd_para_list[0] == "@p_show_chara")
			{
				Cmd_ShowCharacterLayer(
					cmd_para_list[1], 
					cmd_para_list[2].c_str(),
					cmd_para_list[3],
					cmd_para_list[4].at(0),
					CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
					CCommon::common.CHARACTERLAYER_MOVE_INCREMENT,
					true);
			}
			else if (cmd_para_list[0] == "@move_chara")
			{
				Cmd_MoveCharacterLayer(cmd_para_list[1],
					atof(cmd_para_list[2].c_str()),
					atof(cmd_para_list[3].c_str()),
					atof(cmd_para_list[4].c_str()),
					false);
			}
			else if (cmd_para_list[0] == "@p_move_chara")
			{
				Cmd_MoveCharacterLayer(cmd_para_list[1],
					atof(cmd_para_list[2].c_str()),
					atof(cmd_para_list[3].c_str()),
					atof(cmd_para_list[4].c_str()),
					true);
			}
			else
			{
				goto flag_default;
				//cout << "syntax error: " << cmd << "." << endl;
			}
		break;
		case 6:
			if (cmd_para_list[0] == "@show_chara")
			{
				Cmd_ShowCharacterLayer(
					cmd_para_list[1], 
					cmd_para_list[2].c_str(),
					atof(cmd_para_list[3].c_str()),
					atof(cmd_para_list[4].c_str()),
					cmd_para_list[5].at(0),
					CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
					CCommon::common.CHARACTERLAYER_MOVE_INCREMENT,
					false);
			}
			else if (cmd_para_list[0] == "@p_show_chara")
			{
				Cmd_ShowCharacterLayer(
					cmd_para_list[1], 
					cmd_para_list[2].c_str(),
					atof(cmd_para_list[3].c_str()),
					atof(cmd_para_list[4].c_str()),
					cmd_para_list[5].at(0),
					CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
					CCommon::common.CHARACTERLAYER_MOVE_INCREMENT,
					true);
			}
			else
			{
				goto flag_default;
				//cout << "syntax error: " << cmd << "." << endl;
			}
		break;
		case 7:

			if (cmd_para_list[0] == "@show_img")
			{
				Cmd_ShowImg(cmd_para_list[1].c_str(), 
					cmd_para_list[2].c_str(), 
					atoi(cmd_para_list[3].c_str()), 
					atoi(cmd_para_list[4].c_str()), 
					atoi(cmd_para_list[5].c_str()), 
					atoi(cmd_para_list[6].c_str()),true);
			}
			else
			{
				goto flag_default;
			}
		break;
//		case 8:
//			if (cmd_para_list[0] == "@crt_npc")
//			{
//				if (!Cmd_CreateCharacter(
//					cmd_para_list[1].c_str(), 
//					atoi(cmd_para_list[2].c_str()), 
//					atoi(cmd_para_list[3].c_str()), 
//					cmd_para_list[4].c_str(), 
//					atoi(cmd_para_list[5].c_str()), 
//					atoi(cmd_para_list[6].c_str()), 
//					atoi(cmd_para_list[7].c_str()), 
//					true))
//					cout << "Cmd_CreateCharacter(): failed to creat NPC \"" << cmd_para_list[1] << "\"." <<endl;
//			}
//			else if (cmd_para_list[0] == "@crt_pc")
//			{
//				if (!Cmd_CreateCharacter(
//					cmd_para_list[1].c_str(), 
//					atoi(cmd_para_list[2].c_str()), 
//					atoi(cmd_para_list[3].c_str()), 
//					cmd_para_list[4].c_str(), 
//					atoi(cmd_para_list[5].c_str()), 
//					atoi(cmd_para_list[6].c_str()), 
//					atoi(cmd_para_list[7].c_str()), 
//					false))
//					cout << "Cmd_CreateCharacter(): failed to creat player character \"" << cmd_para_list[1] << "\"." <<endl;
//			}
//			else 			if (cmd_para_list[0] == "@show_chara")
//			{
//				switch (Cmd_ShowCharacterLayer(
//					cmd_para_list[1], 
//					cmd_para_list[2].c_str(), 
//					atoi(cmd_para_list[3].c_str()), 
//					atoi(cmd_para_list[4].c_str()), 
//					atoi(cmd_para_list[5].c_str()), 
//					cmd_para_list[6][0],
//					atoi(cmd_para_list[7].c_str()),  
//					false))
//				{
//					case -1:
//						cout << "Cmd_ShowCharacterLayer(): failed to creat character layer." <<endl;
//					break;
//					case 0:
//						cout << "Cmd_ShowCharacterLayer(): character layer \""<< cmd_para_list[1] << "\" has existed." <<endl;
//					break;
//				}
//			}
//			else if (cmd_para_list[0] == "@pshow_chara")
//			{
//				switch (Cmd_ShowCharacterLayer(
//					cmd_para_list[1], 
//					cmd_para_list[2].c_str(), 
//					atoi(cmd_para_list[3].c_str()), 
//					atoi(cmd_para_list[4].c_str()), 
//					atoi(cmd_para_list[5].c_str()), 
//					cmd_para_list[6][0],
//					atoi(cmd_para_list[7].c_str()),  
//					true))
//				{
//					case -1:
//						cout << "Cmd_ShowCharacterLayer(): failed to creat character layer." <<endl;
//					break;
//					case 0:
//						cout << "Cmd_ShowCharacterLayer(): character layer \""<< cmd_para_list[1] << "\" has existed." <<endl;
//					break;
//					case 1:
//						Pause = true;
//					break;
//				}
//			}
//			else
//			{
//				goto flag_default;
//				//cout << "syntax error: " << cmd << "." << endl;
//			}
//		break;
//		case 9:
//			if (cmd_para_list[0] == "@add_anime_data")
//			{
//				switch (Cmd_AddAnimationData(cmd_para_list[1], 
//					cmd_para_list[2], 
//					cmd_para_list[3],
//					atoi(cmd_para_list[4].c_str()),
//					atoi(cmd_para_list[5].c_str()),
//					cmd_para_list[6] == "0" ? false : true,
//					atoi(cmd_para_list[7].c_str()),
//					cmd_para_list[8]))
//				{
//					case -1:
//						cout << "Cmd_AddAnimationData(): maxframes cannot be less than 1." <<endl;
//					break;
//					case -2:
//						cout << "Cmd_AddAnimationData(): animation script \""<< cmd_para_list[1] << "\" has not existed." <<endl;
//					break;
//				}
//			}
//			else
//			{
//				goto flag_default;
//				//cout << "syntax error: " << cmd << "." << endl;
//			}
//		break;
//		case 13:
//			if (cmd_para_list[0] == "@add_btn")
//			{
//				switch (Cmd_AddButton(
//					cmd_para_list[1].c_str(), 
//					atoi(cmd_para_list[2].c_str()), 
//					atoi(cmd_para_list[3].c_str()), 
//					atoi(cmd_para_list[4].c_str()), 
//					atoi(cmd_para_list[5].c_str()), 
//					atoi(cmd_para_list[6].c_str()), 
//					atoi(cmd_para_list[7].c_str()), 
//					atoi(cmd_para_list[8].c_str()), 
//					atoi(cmd_para_list[9].c_str()), 
//					cmd_para_list[10].c_str(), 
//					cmd_para_list[11].c_str(),
//					cmd_para_list[12].c_str()))
//				{
//					case -1:
//						cout << "Cmd_AddButton(): button \""<< cmd_para_list[1] << "\" has existed." <<endl;
//						break;
//					case -2:
//						cout << "Cmd_AddButton(): can't find tileset file \""<< cmd_para_list[10] << "\"." <<endl;
//						break;
//					case -3:
//						cout << "Cmd_AddButton(): can't find script file \"" << cmd_para_list[11] 
//							<< "\" or section ["<< cmd_para_list[12] << "]." <<endl;
//						break;
//				}
//			}
//			else
//			{
//				goto flag_default;
//				//cout << "syntax error: " << cmd << "." << endl;
//			}
//		break;
//
		default:
flag_default:
			if (cmd_para_list.size() > 1)
			{
				if (cmd_para_list[0] == "@msg")
				{
					//char msg[1024] = "";
					//sscanf(cmd.c_str(), " @msg %[]", msg);
					string msg = cmd_para_list[1];
					for (unsigned int i = 2; i < cmd_para_list.size(); i++)
						msg += " " + cmd_para_list[i];

					Cmd_Message("msg",msg);
				}
//				else if (cmd_para_list[0] == "@show_btn")
//				{
//					for (int i = 1; i < cmd_para_list.size(); i++)
//					{
//						if (!Cmd_ShowButton(cmd_para_list[i].c_str(), false))
//							cout << "Cmd_ShowButton(): can't find button \""<< cmd_para_list[i] << "\"." <<endl;
//					}
//				}
//				else if (cmd_para_list[0] == "@pshow_btn")
//				{
//					for (int i = 1; i < cmd_para_list.size(); i++)
//					{
//						bool b = i == cmd_para_list.size() - 1;
//						if (!Cmd_ShowButton(cmd_para_list[i].c_str(), b))
//							cout << "Cmd_ShowButton(): can't find button \""<< cmd_para_list[i] << "\"." <<endl;
//						else
//							Pause = true;
//					}
//				}
//				else if (cmd_para_list[0] == "@del_btn")
//				{
//					for (int i = 1; i < cmd_para_list.size(); i++)
//					{
//						if (!Cmd_DelButton(cmd_para_list[i].c_str()))
//							cout << "Cmd_AddButton(): can't find button \""<< cmd_para_list[i] << "\"." <<endl;
//					}
//				}
//				else if (cmd_para_list[0] == "@hide_btn")
//				{
//					for (int i = 1; i < cmd_para_list.size(); i++)
//					{
//						if (!Cmd_HideButton(cmd_para_list[i].c_str(), false))
//							cout << "Cmd_HideButton(): can't find button \""<< cmd_para_list[i] << "\"." <<endl;
//					}
//				}
//				else if (cmd_para_list[0] == "@phide_btn")
//				{
//					for (int i = 1; i < cmd_para_list.size(); i++)
//					{
//						bool b = i == cmd_para_list.size() - 1;
//						if (!Cmd_HideButton(cmd_para_list[i].c_str(), b))
//							cout << "Cmd_HideButton(): can't find button \""<< cmd_para_list[i] << "\"." <<endl;
//						else
//							Pause = true;
//					}
//				}
//				else if (cmd_para_list[0] == "@if")
//				{
//					string str = "";
//					switch (Cmd_If(cmd_para_list[2], cmd_para_list[1], cmd_para_list[3]))
//					{
//						case -1:
//							cout << "syntax error: "<< cmd << " expected a statement." << endl;
//						break;
//
//						case 0:
//						break;
//
//						case 1:
//							for (int i = 4; i < cmd_para_list.size(); i++)
//							{
//								str += cmd_para_list[i] + " ";
//							}
//							_CmdList.insert(_CmdList.begin(), str);
//						break;
//					}
//				}
//				else
//					cout << "syntax error:" << cmd << "." << endl;
			}
//			else
//				cout << "syntax error:" << cmd << "." << endl;
//		break;
	}
	cmd_para_list.clear();
}

void CParser::OnLoop()
{
	try
	{
		if (_CmdList.size() > 0)
		{
			string cmd = _CmdList.front();
			_CmdList.erase(_CmdList.begin());
			ExecuteCmd(cmd);
		}
	}
	catch(exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}
}

bool CParser::ExecuteAllCmd(const char* FileName, const char* Section)
{
	list<string> commands;

	if (LoadScript(FileName, Section, commands))
	{
		while (commands.size() > 0)
		{
			string cmd = commands.front();
			commands.erase(commands.begin());
			ExecuteCmd(cmd);
		}
	}
	else
		return false;
	
	return true;
}

void CParser::ExecuteAllCmd(list<string> commands)
{
	while (commands.size() > 0)
	{
		string cmd = commands.front();
		_CmdList.erase(commands.begin());
		ExecuteCmd(cmd);
	}
}

void CParser::InsertCmdList(list<string> commands)
{
	if (commands.size() > 0)
	{
		_CmdList.insert(_CmdList.end(),commands.begin(),commands.end());
		
		//Pause = false;
	}
	commands.clear();
}

int CParser::AnalysisOfParameters(string para, vector<string> &plist)
{
	string __tmp = "";

	while (para.length() != 0)
	{
		if (para[0] != 0x20 && para[0] != 0x09){
			if (para[0] == '"' && __tmp.empty()){
				para.erase(0,1);

				if(para.find("\"")!=string::npos){
					__tmp.insert (0,para,0,para.find("\""));
					plist.push_back(__tmp);
					__tmp.clear();
					para.erase(0,para.find("\"") + 1);
				}
				else{
					plist.clear();
					return -1;
				}
			}
			else{
				__tmp += para[0];
				para.erase(0,1);

				if (para.length() == 0)
					plist.push_back(__tmp);
			}
		}
		else{
			if (!__tmp.empty()){
					plist.push_back(__tmp);
					__tmp.clear();
			}

			para.erase(0,1);
		}
	}

	for (unsigned int i = 1; i < plist.size(); i++)
	{
		if(plist[i].at(0) == '$'){
			if (CCommon::common.PlayerVariableTable.count(plist[i]) > 0){
				plist[i] = CCommon::common.PlayerVariableTable[plist[i]];
			}
		}
	}

	return plist.size();
}
