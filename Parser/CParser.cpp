/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CParser.h"

CParser CParser::_Parser;

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
    _delay =  ms + CCommon::_Common.GetTicks();
}

bool CParser::IsDeplaying()
{
    return (CCommon::_Common.GetTicks() < _delay ? true : false);
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
    list<string> __commands = Cio::LoadTxtFile(FileName, ";]");

    if (Section != NULL){
        if (!FindSection(__commands, Section)){
            cout << "LoadScript(): can't find section [" << Section << "]"<<endl;
            return false;
        }
    }
    
    for (list<string>::iterator it=__commands.begin();it!=__commands.end(); it++){
        if ((*it).find("@end") != string::npos){
            __commands.erase(it, __commands.end());
            break;
        }

        //if ((*it).find_last_of(";") != string::npos)
        //    (*it).erase((*it).find_last_of(";"),1);

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
        else if (__commandName == "@order_chara") _pFunc = &Cmd_SetCharacterLayerOrder;

        else if (__commandName == "@add_bg") _pFunc = &Cmd_AddBackground;
        else if (__commandName == "@show_bg") _pFunc = &Cmd_ShowBackground;
        else if (__commandName == "@hide_bg") _pFunc = &Cmd_HideBackground;
        else if (__commandName == "@del_bg") _pFunc = &Cmd_DelBackground;
        else if (__commandName == "@order_bg") _pFunc = &Cmd_SetBackgroundLayerOrder;

        else if (__commandName == "@add_img") _pFunc = &Cmd_AddImg;
        else if (__commandName == "@show_img") _pFunc = &Cmd_ShowImg;
        else if (__commandName == "@hide_img") _pFunc = &Cmd_HideImg;
        else if (__commandName == "@del_img") _pFunc = &Cmd_DelImg;
        else if (__commandName == "@order_img") _pFunc = &Cmd_SetImgLayerOrder;

        else if (__commandName == "@add_msgbox") _pFunc = &Cmd_AddMessageBox;
        else if (__commandName == "@show_msgbox") _pFunc = &Cmd_ShowMessageBox;
        else if (__commandName == "@hide_msgbox") _pFunc = &Cmd_HideMessageBox;
        else if (__commandName == "@del_msgbox") _pFunc = &Cmd_DelMessageBox;
        else if (__commandName == "@order_msgbox") _pFunc = &Cmd_SetMessageBoxLayerOrder;
        else if (__commandName == "@msg") _pFunc = &Cmd_Message;

        else if (__commandName == "@add_logbox") _pFunc = &Cmd_AddLogBox;
        else if (__commandName == "@show_logbox") _pFunc = &Cmd_ShowLogBox;
        else if (__commandName == "@hide_logbox") _pFunc = &Cmd_HideLogBox;
        else if (__commandName == "@del_logbox") _pFunc = &Cmd_DelLogBox;
        else if (__commandName == "@order_logbox") _pFunc = &Cmd_SetLogBoxLayerOrder;

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
        else if (__commandName == "@order_btn") _pFunc = &Cmd_SetButtonLayerOrder;
        
        else if (__commandName == "@add_var") _pFunc = &Cmd_AddVariable;
        else if (__commandName == "@set_var") _pFunc = &Cmd_SetVariable;
        else if (__commandName == "@del_var") _pFunc = &Cmd_DelVariable;

        else if (__commandName == "@add_font") _pFunc = &Cmd_AddFont;
        else if (__commandName == "@del_font") _pFunc = &Cmd_DelFont;

        else if (__commandName == "@add_particle") _pFunc = &Cmd_AddParticleSystem;
        else if (__commandName == "@del_particle") _pFunc = &Cmd_DelParticleSystem;
        else if (__commandName == "@show_particle") _pFunc = &Cmd_ShowParticleSystem;
        else if (__commandName == "@hide_particle") _pFunc = &Cmd_HideParticleSystem;
        else if (__commandName == "@order_particle") _pFunc = &Cmd_SetParticleSystemLayerOrder;

        else if (__commandName == "@deplay"){
            if (__listOfCmdPara.size() == 1)
                SetDeplay(atoi(__listOfCmdPara[0].c_str()));
            else
                cout << "Cmd_Deplay(): command invaild. can't set " << __listOfCmdPara.size()
                    << " argument(s) in the command." <<endl;
        }
        else if (__commandName == "@reload"){
            
        }
        else if (__commandName == "@exit"){
            if (_pRunning != NULL)
                *_pRunning = false;
        }
        else{
            cout << "unknown command." << endl;
            return;
        }

        if (_pFunc != NULL){
            _pFunc(__listOfCmdPara);
            _pFunc = NULL;
        }
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
    size_t __index = 0;

    while (para.length() != 0)
    {
        if (para[0] != 0x20 && para[0] != 0x09){
            if (para[0] == '"' && __tmp.empty()){
                para.erase(0,1);
                
                __index = 0;
                do{
                     __index = para.find("\"", __index == 0 ? 0 : __index+1);
                    if (__index != string::npos && __index > 0){
                        if (para[__index-1] != '\\'){
                            __tmp.insert (0, para, 0, __index);
                            plist.push_back(__tmp);
                            __tmp.clear();
                            para.erase(0, __index + 1);
                            break;
                        }
                    }
                    else{
                        plist.clear();
                        return -1;
                    }
                }while (true);
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
            //if (CCommon::_Common._PlayerVariableTable.count(plist[i]) > 0){
                //plist[i] = CCommon::_Common._PlayerVariableTable[plist[i]];
            //}
            plist[i] = CResourceControl::_ResourceManager.GetVariable(plist[i]);
        }
    }

    return plist.size();
}
