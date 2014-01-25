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
    return CParser::LoadScript(FileName, Section, _CmdList);
}

void CParser::OnCleanup() {
    _CmdList.clear();
    _pRunning = NULL;
}


void CParser::ExecuteCmd(string cmd)
{
    vector<string> __listOfCmdPara;
    if (AnalysisOfParameters(cmd, __listOfCmdPara) > 0){
        string __commandName = __listOfCmdPara[0];
        __listOfCmdPara.erase(__listOfCmdPara.begin());

        if (__commandName == "@show_info") _pFunc = &Cmd_ShowInfo;

        else if (__commandName == "@add_position") _pFunc = &Cmd_AddPosition;
        else if (__commandName == "@del_position") _pFunc = &Cmd_DelPosition;
        else if (__commandName == "@show_chara") _pFunc = &Cmd_ShowCharacterLayer;
        else if (__commandName == "@hide_chara") _pFunc = &Cmd_HideCharacterLayer;
        else if (__commandName == "@face") _pFunc = &Cmd_SetFaceCharacterLayer;

        else if (__commandName == "@add_bg") _pFunc = &Cmd_AddBackground;
        else if (__commandName == "@show_bg") _pFunc = &Cmd_ShowBackground;
        else if (__commandName == "@hide_bg") _pFunc = &Cmd_HideBackground;
        else if (__commandName == "@del_bg") _pFunc = &Cmd_DelBackground;
        
        else if (__commandName == "@add_img") _pFunc = &Cmd_AddImg;
        else if (__commandName == "@show_img") _pFunc = &Cmd_ShowImg;
        else if (__commandName == "@hide_img") _pFunc = &Cmd_HideImg;
        else if (__commandName == "@del_img") _pFunc = &Cmd_DelImg;
        else 
            return;

        _pFunc(__listOfCmdPara);
    }

//    switch (AnalysisOfParameters(cmd, __cmd_para_list))
//    {
//        case 0:
//        break;
//        case 1:
//            if (__cmd_para_list[0] == "@exit")
//            {
//                if (_pRunning != NULL)
//                    *_pRunning = false;
//            }
//            else if (__cmd_para_list[0] == "@show_info")
//            {
//                Cmd_ShowInfo();
//            }
//            else
//            {
//                goto flag_default;
//                //cout << "syntax error: " << cmd << "." << endl;
//            }
//        break;
//        case 2:
//            if (__cmd_para_list[0] == "@say")
//            {
//                if (!Cmd_Say(__cmd_para_list[1].c_str()))
//                    cout << "Cmd_Say(): failed to play voice \""<< __cmd_para_list[1] << "\"." <<endl;
//            }
//            else if (__cmd_para_list[0] == "@play_se")
//            {
//                if (!Cmd_PlaySE(__cmd_para_list[1].c_str()))
//                    cout << "Cmd_PlaySE(): can't find SE \""<< __cmd_para_list[1] << "\"." <<endl;
//            }
////=========================================================
//            else if (__cmd_para_list[0] == "@show_img_nb")
//            {
//                Cmd_ShowImg(__cmd_para_list[1].c_str(),
//                    CCommon::common.INCREMENT,false);
//            }
//            else if (__cmd_para_list[0] == "@show_img")
//            {
//                Cmd_ShowImg(__cmd_para_list[1].c_str(),
//                    CCommon::common.INCREMENT,true);
//            }
//            else if (__cmd_para_list[0] == "@hide_img_nb")
//            {
//                Cmd_HideImg(__cmd_para_list[1].c_str() ,
//                    CCommon::common.INCREMENT,false);
//            }
//            else if (__cmd_para_list[0] == "@hide_img")
//            {
//                Cmd_HideImg(__cmd_para_list[1].c_str() ,
//                    CCommon::common.INCREMENT,true);
//            }
//            else if (__cmd_para_list[0] == "@del_img")
//            {
//                Cmd_DelImg(__cmd_para_list[1]);
//            }
//
////=========================================================
//            else if (__cmd_para_list[0] == "@show_bg_nb")
//            {
//                Cmd_ShowBackground(__cmd_para_list[1].c_str(),
//                    CCommon::common.INCREMENT,false);
//            }
//            else if (__cmd_para_list[0] == "@show_bg")
//            {
//                Cmd_ShowBackground(__cmd_para_list[1].c_str(),
//                    CCommon::common.INCREMENT,true);
//            }
//            else if (__cmd_para_list[0] == "@hide_bg_nb")
//            {
//                Cmd_HideBackground(__cmd_para_list[1].c_str() ,
//                    CCommon::common.INCREMENT,false);
//            }
//            else if (__cmd_para_list[0] == "@hide_bg")
//            {
//                Cmd_HideBackground(__cmd_para_list[1].c_str() ,
//                    CCommon::common.INCREMENT,true);
//            }
//            else if (__cmd_para_list[0] == "@del_bg")
//            {
//                Cmd_DelBackground(__cmd_para_list[1]);
//            }
////=========================================================
//            else if (__cmd_para_list[0] == "@deplay")
//            {
//                SetDeplay(atoi(__cmd_para_list[1].c_str()));
//            }
//            else if (__cmd_para_list[0] == "@play_bgm")
//            {
//                if (!Cmd_PlayBGM(__cmd_para_list[1].c_str()))
//                    cout << "Cmd_PlayBGM(): failed to play BGM \"" << __cmd_para_list[1] << "\"." <<endl;
//            }
//            else if (__cmd_para_list[0] == "@del_se")
//            {
//                if (!Cmd_DelSE(__cmd_para_list[1].c_str()))
//                    cout << "Cmd_DelSE(): can't find SE \""<< __cmd_para_list[1] << "\"." <<endl;
//            }
//            else if (__cmd_para_list[0] == "@del_position")
//            {
//                Cmd_DelPosition(__cmd_para_list[1]);
//            }
//            
////=========================================================
//            else if (__cmd_para_list[0] == "@show_msgbox")
//            {
//                Cmd_ShowMessageBox(__cmd_para_list[1],
//                    CCommon::common.INCREMENT,
////                    CCommon::common.INTERVAL,
//                    true);
//            }
//            else if (__cmd_para_list[0] == "@show_msgbox_nb")
//            {
//                Cmd_ShowMessageBox(__cmd_para_list[1],
//                    CCommon::common.INCREMENT,
////                    CCommon::common.INTERVAL,
//                    false);
//            }
//            else if (__cmd_para_list[0] == "@hide_msgbox")
//            {
//                Cmd_HideMessageBox(__cmd_para_list[1],
//                    CCommon::common.INCREMENT,
////                    CCommon::common.INTERVAL,
//                    true);
//            }
//            else if (__cmd_para_list[0] == "@hide_msgbox_nb")
//            {
//                Cmd_HideMessageBox(__cmd_para_list[1],
//                    CCommon::common.INCREMENT,
////                    CCommon::common.INTERVAL,
//                    false);
//            }
//            else if (__cmd_para_list[0] == "@del_msgbox")
//            {
//                Cmd_DelMessageBox(__cmd_para_list[1]);
//            }
//            
////=========================================================
//            else if (__cmd_para_list[0] == "@show_btn")
//            {
//                Cmd_ShowButton(__cmd_para_list[1],
//                    CCommon::common.INCREMENT,
//                    true);
//            }
//            else if (__cmd_para_list[0] == "@hide_btn")
//            {
//                Cmd_HideButton(__cmd_para_list[1],
//                    CCommon::common.INCREMENT,
//                    true);
//            }
//            else if (__cmd_para_list[0] == "@del_btn")
//            {
//                Cmd_DelButton(__cmd_para_list[1]);
//            }
//            else
//            {
//                goto flag_default;
//                //cout << "syntax error: " << cmd << "." << endl;
//            }
//        break;
//        case 3:
//            if (__cmd_para_list[0] == "@face"){
//                Cmd_SetFaceCharacterLayer(__cmd_para_list[1], __cmd_para_list[2]);
//            }
//            else if (__cmd_para_list[0] == "@hide_chara_nb")
//            {
//                Cmd_HideCharacterLayer(__cmd_para_list[1],__cmd_para_list[2].at(0),
//                    //CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
//                    20.0f,
//                    CCommon::common.INCREMENT,false);
//            }
//            else if (__cmd_para_list[0] == "@hide_chara")
//            {
//                Cmd_HideCharacterLayer(__cmd_para_list[1],__cmd_para_list[2].at(0),
//                    //CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
//                    20.0f,
//                    CCommon::common.INCREMENT,true);
//            }
//            else if (__cmd_para_list[0] == "@add_se")
//            {
//                switch(Cmd_AddSE(__cmd_para_list[1].c_str(),__cmd_para_list[2].c_str()))
//                {
//                    case -1:
//                        cout << "Cmd_AddSE(): SE \"" << __cmd_para_list[1] << "\" has existed." <<endl;
//                    break;
//                    case -2:
//                        cout << "Cmd_AddSE(): failed to add SE." <<endl;
//                    break;
//                }
//            }
//
////=========================================================
//            else if (__cmd_para_list[0] == "@add_msgbox")
//            {
//                Cmd_AddMessageBox(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str());
//            }
//            else if (__cmd_para_list[0] == "@msg")
//            {
//                Cmd_Message(__cmd_para_list[1],
//                    __cmd_para_list[2]);
//            }
//            else if (__cmd_para_list[0] == "@show_msgbox")
//            {
//                Cmd_ShowMessageBox(__cmd_para_list[1],
//                    atoi(__cmd_para_list[2].c_str()),
//                    true);
//            }
//            else if (__cmd_para_list[0] == "@show_msgbox_nb")
//            {
//                Cmd_ShowMessageBox(__cmd_para_list[1],
//                    atoi(__cmd_para_list[2].c_str()),
//                    false);
//            }
//            else if (__cmd_para_list[0] == "@hide_msgbox")
//            {
//                Cmd_HideMessageBox(__cmd_para_list[1],
//                    atoi(__cmd_para_list[2].c_str()),
//                    true);
//            }
//            else if (__cmd_para_list[0] == "@hide_msgbox_nb")
//            {
//                Cmd_HideMessageBox(__cmd_para_list[1],
//                    atoi(__cmd_para_list[2].c_str()),
//                    false);
//            }
//
////=========================================================
//            else if (__cmd_para_list[0] == "@add_btn")
//            {
//                Cmd_AddButton(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str());
//            }
//            
////=========================================================
//            else if (__cmd_para_list[0] == "@add_img")
//            {
//                Cmd_AddImg(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str());
//            }
//            else if (__cmd_para_list[0] == "@show_img_nb")
//            {
//                Cmd_ShowImg(__cmd_para_list[1].c_str(), 
//                    atoi(__cmd_para_list[2].c_str()), false);
//            }
//            else if (__cmd_para_list[0] == "@show_img")
//            {
//                Cmd_ShowImg(__cmd_para_list[1].c_str(), 
//                    atoi(__cmd_para_list[2].c_str()), true);
//            }
//            else if (__cmd_para_list[0] == "@hide_img_nb")
//            {
//                Cmd_HideImg(__cmd_para_list[1].c_str() ,
//                    atoi(__cmd_para_list[2].c_str()),false);
//            }
//            else if (__cmd_para_list[0] == "@hide_img")
//            {
//                Cmd_HideImg(__cmd_para_list[1].c_str() ,
//                    atoi(__cmd_para_list[2].c_str()),true);
//            }
////=========================================================
//            else if (__cmd_para_list[0] == "@add_bg")
//            {
//                Cmd_AddBackground(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str());
//            }
//            else if (__cmd_para_list[0] == "@show_bg_nb")
//            {
//                Cmd_ShowBackground(__cmd_para_list[1].c_str(), 
//                    atoi(__cmd_para_list[2].c_str()),  false);
//            }
//            else if (__cmd_para_list[0] == "@show_bg")
//            {
//                Cmd_ShowBackground(__cmd_para_list[1].c_str(), 
//                    atoi(__cmd_para_list[2].c_str()),  true);
//            }
//            else if (__cmd_para_list[0] == "@hide_bg_nb")
//            {
//                Cmd_HideBackground(__cmd_para_list[1].c_str() ,
//                    atoi(__cmd_para_list[2].c_str()),false);
//            }
//            else if (__cmd_para_list[0] == "@hide_bg")
//            {
//                Cmd_HideBackground(__cmd_para_list[1].c_str() ,
//                    atoi(__cmd_para_list[2].c_str()),true);
//            }
//            
////=========================================================
//            else
//            {
//                goto flag_default;
//                //cout << "syntax error: " << cmd << "." << endl;
//            }
//        break;
//        case 4:
//            if (__cmd_para_list[0] == "@add_position")
//            {
//                Cmd_AddPosition(__cmd_para_list[1],
//                    atof(__cmd_para_list[2].c_str()),
//                    atof(__cmd_para_list[3].c_str()));
//            }
//            else if (__cmd_para_list[0] == "@move_chara_nb")
//            {
//                Cmd_MoveCharacterLayer(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str(),
//                    atof(__cmd_para_list[3].c_str()),
//                    false);
//            }
//            else if (__cmd_para_list[0] == "@move_chara")
//            {
//                Cmd_MoveCharacterLayer(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str(),
//                    atof(__cmd_para_list[3].c_str()),
//                    true);
//            }
//            else
//            {
//                goto flag_default;
//                //cout << "syntax error: " << cmd << "." << endl;
//            }
//        break;
//        case 5:
//            if (__cmd_para_list[0] == "@show_chara_nb")
//            {
//                Cmd_ShowCharacterLayer(
//                    __cmd_para_list[1], 
//                    __cmd_para_list[2].c_str(),
//                    __cmd_para_list[3],
//                    __cmd_para_list[4].at(0),
//                    //CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
//                    20.0f,
//                    CCommon::common.INCREMENT,
//                    false);
//            }
//            else if (__cmd_para_list[0] == "@show_chara")
//            {
//                Cmd_ShowCharacterLayer(
//                    __cmd_para_list[1], 
//                    __cmd_para_list[2].c_str(),
//                    __cmd_para_list[3],
//                    __cmd_para_list[4].at(0),
//                    //CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
//                    20.0f,
//                    CCommon::common.INCREMENT,
//                    true);
//            }
//            else if (__cmd_para_list[0] == "@move_chara_nb")
//            {
//                Cmd_MoveCharacterLayer(__cmd_para_list[1],
//                    atof(__cmd_para_list[2].c_str()),
//                    atof(__cmd_para_list[3].c_str()),
//                    atof(__cmd_para_list[4].c_str()),
//                    false);
//            }
//            else if (__cmd_para_list[0] == "@move_chara")
//            {
//                Cmd_MoveCharacterLayer(__cmd_para_list[1],
//                    atof(__cmd_para_list[2].c_str()),
//                    atof(__cmd_para_list[3].c_str()),
//                    atof(__cmd_para_list[4].c_str()),
//                    true);
//            }
//
////=========================================================
//            else if (__cmd_para_list[0] == "@add_img")
//            {
//                Cmd_AddImg(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str(),
//                    atof(__cmd_para_list[3].c_str()),
//                    atof(__cmd_para_list[4].c_str()));
//            }
////=========================================================
//            else if (__cmd_para_list[0] == "@add_bg")
//            {
//                Cmd_AddBackground(__cmd_para_list[1],
//                    __cmd_para_list[2].c_str(),
//                    atof(__cmd_para_list[3].c_str()),
//                    atof(__cmd_para_list[4].c_str()));
//            }
////=========================================================
//            else
//            {
//                goto flag_default;
//                //cout << "syntax error: " << cmd << "." << endl;
//            }
//        break;
//        case 6:
//            if (__cmd_para_list[0] == "@show_chara_nb")
//            {
//                Cmd_ShowCharacterLayer(
//                    __cmd_para_list[1], 
//                    __cmd_para_list[2].c_str(),
//                    atof(__cmd_para_list[3].c_str()),
//                    atof(__cmd_para_list[4].c_str()),
//                    __cmd_para_list[5].at(0),
//                    //CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
//                    20.0f,
//                    CCommon::common.INCREMENT,
//                    false);
//            }
//            else if (__cmd_para_list[0] == "@show_chara")
//            {
//                Cmd_ShowCharacterLayer(
//                    __cmd_para_list[1], 
//                    __cmd_para_list[2].c_str(),
//                    atof(__cmd_para_list[3].c_str()),
//                    atof(__cmd_para_list[4].c_str()),
//                    __cmd_para_list[5].at(0),
//                    //CCommon::common.CHARACTERLAYER_MOVE_BUFFER,
//                    20.0f,
//                    CCommon::common.INCREMENT,
//                    true);
//            }
//            else
//            {
//                goto flag_default;
//                //cout << "syntax error: " << cmd << "." << endl;
//            }
//        break;
//        case 7:
//
//
//            //else
//            //{
//            //    goto flag_default;
//            //}
//        break;
//        default:
//flag_default:
//                cout << "syntax error:" << cmd << "." << endl;
//            if (__cmd_para_list.size() > 1)
//            {
//                if (__cmd_para_list[0] == "@msg")
//                {
//                    //char msg[1024] = "";
//                    //sscanf(cmd.c_str(), " @msg %[]", msg);
//                    string msg = __cmd_para_list[1];
//                    for (unsigned int i = 2; i < __cmd_para_list.size(); i++)
//                        msg += " " + __cmd_para_list[i];
//
//                    Cmd_Message("msg",msg);
//                }
////                else if (__cmd_para_list[0] == "@show_btn")
////                {
////                    for (int i = 1; i < __cmd_para_list.size(); i++)
////                    {
////                        if (!Cmd_ShowButton(__cmd_para_list[i].c_str(), false))
////                            cout << "Cmd_ShowButton(): can't find button \""<< __cmd_para_list[i] << "\"." <<endl;
////                    }
////                }
////                else if (__cmd_para_list[0] == "@pshow_btn")
////                {
////                    for (int i = 1; i < __cmd_para_list.size(); i++)
////                    {
////                        bool b = i == __cmd_para_list.size() - 1;
////                        if (!Cmd_ShowButton(__cmd_para_list[i].c_str(), b))
////                            cout << "Cmd_ShowButton(): can't find button \""<< __cmd_para_list[i] << "\"." <<endl;
////                        else
////                            Pause = true;
////                    }
////                }
////                else if (__cmd_para_list[0] == "@del_btn")
////                {
////                    for (int i = 1; i < __cmd_para_list.size(); i++)
////                    {
////                        if (!Cmd_DelButton(__cmd_para_list[i].c_str()))
////                            cout << "Cmd_AddButton(): can't find button \""<< __cmd_para_list[i] << "\"." <<endl;
////                    }
////                }
////                else if (__cmd_para_list[0] == "@hide_btn")
////                {
////                    for (int i = 1; i < __cmd_para_list.size(); i++)
////                    {
////                        if (!Cmd_HideButton(__cmd_para_list[i].c_str(), false))
////                            cout << "Cmd_HideButton(): can't find button \""<< __cmd_para_list[i] << "\"." <<endl;
////                    }
////                }
////                else if (__cmd_para_list[0] == "@phide_btn")
////                {
////                    for (int i = 1; i < __cmd_para_list.size(); i++)
////                    {
////                        bool b = i == __cmd_para_list.size() - 1;
////                        if (!Cmd_HideButton(__cmd_para_list[i].c_str(), b))
////                            cout << "Cmd_HideButton(): can't find button \""<< __cmd_para_list[i] << "\"." <<endl;
////                        else
////                            Pause = true;
////                    }
////                }
////                else if (__cmd_para_list[0] == "@if")
////                {
////                    string str = "";
////                    switch (Cmd_If(__cmd_para_list[2], __cmd_para_list[1], __cmd_para_list[3]))
////                    {
////                        case -1:
////                            cout << "syntax error: "<< cmd << " expected a statement." << endl;
////                        break;
////
////                        case 0:
////                        break;
////
////                        case 1:
////                            for (int i = 4; i < __cmd_para_list.size(); i++)
////                            {
////                                str += __cmd_para_list[i] + " ";
////                            }
////                            _CmdList.insert(_CmdList.begin(), str);
////                        break;
////                    }
////                }
////                else
////                    cout << "syntax error:" << cmd << "." << endl;
//            }
//            else
//                cout << "syntax error:" << cmd << "." << endl;
//        break;
//    }
//    __cmd_para_list.clear();
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

//int CParser::AnalysisOfParameters(string para, queue<string> &plist)
//{
//    string __tmp = "";
//
//    while (para.length() != 0)
//    {
//        if (para[0] != 0x20 && para[0] != 0x09){
//            if (para[0] == '"' && __tmp.empty()){
//                para.erase(0,1);
//
//                if(para.find("\"")!=string::npos){
//                    __tmp.insert (0,para,0,para.find("\""));
//                    plist.push(__tmp);
//                    __tmp.clear();
//                    para.erase(0,para.find("\"") + 1);
//                }
//                else{
//                    //plist.clear();
//                    return -1;
//                }
//            }
//            else{
//                __tmp += para[0];
//                para.erase(0,1);
//
//                if (para.length() == 0)
//                    plist.push(__tmp);
//            }
//        }
//        else{
//            if (!__tmp.empty()){
//                    plist.push(__tmp);
//                    __tmp.clear();
//            }
//
//            para.erase(0,1);
//        }
//    }
//
//    //for (unsigned int i = 1; i < plist.size(); i++)
//    //{
//    //    if(plist[i].at(0) == '$'){
//    //        if (CCommon::common.PlayerVariableTable.count(plist[i]) > 0){
//    //            plist[i] = CCommon::common.PlayerVariableTable[plist[i]];
//    //        }
//    //    }
//    //}
//
//    return plist.size();
//}