/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
    _delay = 0;
    _pRunning = NULL;
    _pFunc = NULL;
}

void CParser::SetRunning(bool* running)
{
    _pRunning = running;
}

void CParser::SetDeplay(int ms)
{
    _delay =  ms + CCommon::common.GetTicks();
}

bool CParser::IsDeplaying()
{
    return (CCommon::common.GetTicks() < _delay ? true : false);
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

    if (Section != NULL){
        if (!FindSection(__commands, Section)){
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
    return CParser::LoadScript(FileName, Section, _cmdList);
}

void CParser::OnCleanup() {
    _cmdList.clear();
    _pRunning = NULL;
}

void CParser::ExecuteCmd(string cmd)
{
    vector<string> __listOfCmdPara;
    if (AnalysisOfParameters(cmd, __listOfCmdPara) > 0){

#ifdef _DEBUG
        for (unsigned int i=0; i<__listOfCmdPara.size(); i++){
            cout << i << ": " << __listOfCmdPara[i] << " ";
        }
        cout << endl;
#endif

        string __commandName = __listOfCmdPara[0];
        __listOfCmdPara.erase(__listOfCmdPara.begin());

        if (__commandName == "@show_info") _pFunc = &Cmd_ShowInfo;

        else if (__commandName == "@add_position") _pFunc = &Cmd_AddPosition;
        else if (__commandName == "@del_position") _pFunc = &Cmd_DelPosition;

        else if (__commandName == "@add_chara") _pFunc = &Cmd_AddCharacterLayer;
        else if (__commandName == "@del_chara") _pFunc = &Cmd_DelCharacterLayer;
        else if (__commandName == "@show_chara") _pFunc = &Cmd_ShowCharacterLayer;
        else if (__commandName == "@hide_chara") _pFunc = &Cmd_HideCharacterLayer;
        else if (__commandName == "@move_chara") _pFunc = &Cmd_MoveCharacterLayer;
        else if (__commandName == "@face_chara") _pFunc = &Cmd_SetFaceCharacterLayer;

        else if (__commandName == "@add_bg") _pFunc = &Cmd_AddBackground;
        else if (__commandName == "@show_bg") _pFunc = &Cmd_ShowBackground;
        else if (__commandName == "@hide_bg") _pFunc = &Cmd_HideBackground;
        else if (__commandName == "@del_bg") _pFunc = &Cmd_DelBackground;

        else if (__commandName == "@add_img") _pFunc = &Cmd_AddImg;
        else if (__commandName == "@show_img") _pFunc = &Cmd_ShowImg;
        else if (__commandName == "@hide_img") _pFunc = &Cmd_HideImg;
        else if (__commandName == "@del_img") _pFunc = &Cmd_DelImg;

        else if (__commandName == "@add_msgbox") _pFunc = &Cmd_AddMessageBox;
        else if (__commandName == "@show_msgbox") _pFunc = &Cmd_ShowMessageBox;
        else if (__commandName == "@hide_msgbox") _pFunc = &Cmd_HideMessageBox;
        else if (__commandName == "@del_msgbox") _pFunc = &Cmd_DelMessageBox;
        else if (__commandName == "@msg") _pFunc = &Cmd_Message;

        else if (__commandName == "@add_se") _pFunc = &Cmd_AddSE;
        else if (__commandName == "@del_se") _pFunc = &Cmd_DelSE;
        else if (__commandName == "@play_se") _pFunc = &Cmd_PlaySE;

        else if (__commandName == "@add_voice") _pFunc = &Cmd_AddVoice;
        else if (__commandName == "@del_voice") _pFunc = &Cmd_DelVoice;

        else if (__commandName == "@play_bgm") _pFunc = &Cmd_PlayBGM;
        else if (__commandName == "@pause_bgm") _pFunc = &Cmd_PauseBGM;
        else if (__commandName == "@resume_bgm") _pFunc = &Cmd_ResumeBGM;

        else if (__commandName == "@add_btn") _pFunc = &Cmd_AddButton;
        else if (__commandName == "@show_btn") _pFunc = &Cmd_ShowButton;
        else if (__commandName == "@hide_btn") _pFunc = &Cmd_HideButton;
        else if (__commandName == "@del_btn") _pFunc = &Cmd_DelButton;
        
        else if (__commandName == "@Deplay"){
            if (__listOfCmdPara.size() == 1)
                SetDeplay(atoi(__listOfCmdPara[0].c_str()));
            else
                cout << "Cmd_Deplay(): command invaild. can't set " << __listOfCmdPara.size()
                    << " argument(s) in the command." <<endl;

            return;
        }
        else{
            cout << "unknown command." << endl;
            return;
        }

        _pFunc(__listOfCmdPara);
    }
}

void CParser::OnLoop()
{
    try
    {
        if (_cmdList.size() > 0)
        {
            string cmd = _cmdList.front();
            _cmdList.erase(_cmdList.begin());
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
        _cmdList.erase(commands.begin());
        ExecuteCmd(cmd);
    }
}

void CParser::InsertCmdList(list<string> commands)
{
    if (commands.size() > 0)
    {
        _cmdList.insert(_cmdList.end(),commands.begin(),commands.end());
        
        //Pause = false;
    }
    commands.clear();
}

void CParser::InsertCmd(string cmd)
{
    _cmdList.push_back(cmd);
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
