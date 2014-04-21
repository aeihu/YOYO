/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CScriptCommand.h"
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Parser/CParser.h"
#include "../Sound/CSoundBank.h"
#include "../Gui/CButton.h"
#include "../Common/CResourceManager.h"
#include <iostream>
#include <algorithm>

typedef enum{
    FLAG_NECESSITY = 1,
    FLAG_OPTIONAL,
    FLAG_NONPARAMETRIC,
}ENUM_FLAG;

bool Cmd_ArgsToKV(string funcName, list<pair<string, ENUM_FLAG> > flags, vector<string> args, map<string, string>& result)
{
    result.clear();
	list<pair<string, ENUM_FLAG> >::iterator __it;

    for(__it=flags.begin(); __it!=flags.end(); ++__it){
        switch (std::count(args.begin(), args.end(), (*__it).first)){
            case 0:
                if ((*__it).second == FLAG_NECESSITY){
                    cout << funcName << "(): flag \"" << (*__it).first << "\" must be need." << endl;
                    result.clear();
                    return false;
                }
            break;
            case 1:
                {
	                vector<string>::iterator __itOfArgs;
                    __itOfArgs = std::find (args.begin(), args.end(), (*__it).first);

                    if (__itOfArgs != args.end()){
                        if ((*__it).second == FLAG_NONPARAMETRIC){
                            result[(*__it).first] = "";
                        }
                        else{
                            ++__itOfArgs;

                            if (__itOfArgs != args.end())
                                result[(*__it).first] = *__itOfArgs;
                            else{
                                cout << funcName << "(): flag \"" << (*__it).first << "\" has no argument." << endl;
                                result.clear();
                                return false;
                            }
                        }
                    }
                }
            break;
            default:
                cout << funcName << "(): can't has same flag " << (*__it).first << "." << endl;
                result.clear();
                return false;
            break;
        }
    }

#ifdef _DEBUG
    for (map<string, string>::iterator it=result.begin();
        it!=result.end();)
    {
        cout << (*it).first << " : " << (*it).second << endl;
        it++;
    }
#endif

    return true;
}

bool Cmd_ShowInfo(vector<string> args)
{
    CResourceManager::GetInfo();
    //CResourceManager::GetInfo("ImageList", CResourceManager::_ImgLayerControl._ImgLayerList);
    //CResourceManager::GetInfo("BackgroundList", CResourceManager::_BackgroundLayerControl._ImgLayerList);
    //CResourceManager::GetInfo("CharacterList", CResourceManager::_CharacterLayerControl._CharacterList);
    //CResourceManager::GetInfo("MessageBoxList", CResourceManager::_MessageBoxControl._MessageBoxList);
    return true;
}

//void Cmd_AddPosition(string name, float x, float y)
bool Cmd_AddPosition(vector<string> args)
{
    if (args.size() != 3){
        cout << "Cmd_AddPosition(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string name = args[0];
    float x = atof(args[1].c_str());
    float y = atof(args[2].c_str());
    CResourceManager::_PositionControl.AddPosition(name, x, y);
    return true;
}

//void Cmd_DelPosition(string name)
bool Cmd_DelPosition(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelPosition(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        CResourceManager::_PositionControl.DelPosition(args[i]);
    }

    return true;
}

bool Cmd_AddCharacterLayer(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_AddCharacterLayer(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string name = args[0];
    const char* filename = args[1].c_str();

    switch (CResourceManager::_CharacterLayerControl.AddCharacter(name, filename)){
        case 0:
            return true;
        break;
        case 1:
            cout << "Cmd_AddCharacterLayer(): character layer \""<< name << "\" has existed." <<endl;
        break;
        case 2:
            cout << "Cmd_AddCharacterLayer(): failed to create character layer." <<endl;
        break;
    }

    return false;
}

bool Cmd_DelCharacterLayer(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelCharacterLayer(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        if (!CResourceManager::_CharacterLayerControl.DelCharacter(args[i]))
            cout << "Cmd_DelCharacterLayer(): can't find character layer \""<< args[i] << "\"." <<endl;
    }

    return true;
}

//bool Cmd_ShowCharacterLayer(string name, const char* filename, float x, float y, char type, float buf, float incr, bool pause)
bool Cmd_ShowCharacterLayer(vector<string> args)
{
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-a", FLAG_OPTIONAL));    //alpha
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //position
    __flags.push_back(pair<string, ENUM_FLAG>("-t", FLAG_OPTIONAL));    //type
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y

    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_ShowCharacterLayer", __flags, args, __values))
        return false;

    float x = 0.0f;
    float y = 0.0f;

    if (__values.count("-s") > 1){
        if (!CResourceManager::_PositionControl.GetPosition(__values["-s"],&x,&y)){
            cout << "Cmd_ShowCharacterLayer(): can't find position \""<< __values["-s"] << "\"." <<endl;
            return false;
        }
    }

    int alpha = __values.count("-a") == 0 ? 255 : atoi(__values["-a"].c_str());
    float incr = __values.count("-i") == 0 ? (float)CCommon::common.INCREMENT : atof(__values["-i"].c_str());
    string name = __values.count("-n") == 0 ? "" : __values["-n"];
    char type = __values.count("-t") == 0 ? 'c' : atoi(__values["-t"].c_str());
    bool pause = __values.count("-p") == 0 ? false : true;
    x = __values.count("-x") == 0 ? x : atof(__values["-x"].c_str());
    y = __values.count("-y") == 0 ? y : atof(__values["-y"].c_str());

    if (CResourceManager::_CharacterLayerControl.IsAlreadyExists(name)){
        switch (CResourceManager::_CharacterLayerControl.Show(name, x, y, type, incr, pause, alpha)){
            case -1:
                cout << "Cmd_ShowCharacterLayer(): can't find character layer \""<< name << "\"." <<endl;
            break;
            case -2:
                cout << "Cmd_ShowCharacterLayer(): character layer \""<< name << "\" has showed." <<endl;
            break;
            case 0:
                return true;
            break;
        }
    }

    return false;
}

//bool Cmd_MoveCharacterLayer(string name, float x, float y, float incr, bool pause)
bool Cmd_MoveCharacterLayer(vector<string> args)
{
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //position
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y

    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_MoveCharacterLayer", __flags, args, __values))
        return false;

    string __name = __values.count("-n") == 0 ? "" : __values["-n"];
    float __x = 0;
    float __y = 0;

    if (__values.count("-s") > 1){
        if (!CResourceManager::_PositionControl.GetPosition(__values["-s"],&__x,&__y)){
            cout << "Cmd_MoveCharacterLayer(): can't find position \""<< __values["-s"] << "\"." <<endl;
            return false;
        }
    }

    __x = __values.count("-x") == 0 ? __x : atof(__values["-x"].c_str());
    __y = __values.count("-y") == 0 ? __y : atof(__values["-y"].c_str());

    float __incr = __values.count("-i") == 0 ? (float)CCommon::common.INCREMENT : atof(__values["-i"].c_str());
    bool __pause = __values.count("-p") == 0 ? false : true;

    if(!CResourceManager::_CharacterLayerControl.Move(__name, __x, __y, __incr, __pause)){
        cout << "Cmd_MoveCharacterLayer(): can't find character layer \""<< __name << "\"." <<endl;
        return false;
    }
    return true;
}

//bool Cmd_HideCharacterLayer(string name, char type, float buf, float incr, bool pause)
bool Cmd_HideCharacterLayer(vector<string> args)
{
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-t", FLAG_OPTIONAL));    //type

    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_HideCharacterLayer", __flags, args, __values))
        return false;

    float __incr = __values.count("-i") == 0 ? (float)CCommon::common.INCREMENT : atof(__values["-i"].c_str());
    string __name = __values.count("-n") == 0 ? "" : __values["-n"];
    bool __pause = __values.count("-p") == 0 ? false : true;
    char __type = __values.count("-t") == 0 ? 'c' : atoi(__values["-t"].c_str());

    if (!CResourceManager::_CharacterLayerControl.IsAlreadyExists(__name)){
        cout << "Cmd_HideCharacterLayer(): can't find character layer \""<< __name << "\"." << endl;
        return false;
    }

    CResourceManager::_CharacterLayerControl.Hide(__name, __type, __incr, __pause);
    return true;
}

//void Cmd_SetFaceCharacterLayer(string name, string face)
bool Cmd_SetFaceCharacterLayer(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_SetFaceCharacterLayer(): command invaild. can't set " << args.size()
            << " argument(s) in the command." << endl;
        return false;
    }

    string __name = args[0];
    string __face = args[1];

    if (CResourceManager::_CharacterLayerControl._CharacterList[__name].SetFace(__face))
        return true;
    else{
        cout << "Cmd_SetFaceCharacterLayer(): can't find face layer \""<< __face << "\"." <<endl;
        return false;
    }
}
//
//bool Cmd_AlphaCharacterLayer(char postion, int alpha)
//{
//    //for (int i = 0; i < CResourceManager::_CharacterLayerControl._CharacterList.size(); i++)
//    //{
//    //    if(CResourceManager::_CharacterLayerControl._CharacterList[i]->Postion == postion)
//    //    {
//    //        CResourceManager::_CharacterLayerControl._CharacterList[i]->Alpha = alpha;
//    //        return true;
//    //    }
//    //}
//    return false;
//}
//
//bool Cmd_LoadMap(const char* filename)
//{
//    return CArea::AreaControl.OnLoad(filename);
//}
//
//bool Cmd_LoadScript(const char* filename, const char* Section)
//{
//    return CParser::parser.LoadScript(filename, Section);
//}
//
//bool Cmd_AddBackground(string name, const char* filename, float x, float y)
bool Cmd_AddBackground(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_AddBackground(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string __name = args[0];
    const char* __filename = args[1].c_str();

    if (CResourceManager::_BackgroundLayerControl.AddImage(__name, __filename)){
        return true;
    }
    else{
        cout << "Cmd_AddBackground(): failed to load image." <<endl;
        return false;
    }
}

//bool Cmd_ShowBackground(string name, int inrc, bool pause)
bool Cmd_ShowBackground(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_ShowBackground(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-a", FLAG_OPTIONAL));    //alpha
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //Name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //position
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    
    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_ShowBackground", __flags, args, __values))
        return false;
    
    int __alpha = __values.count("-a") == 0 ? 255 : atoi(__values["-a"].c_str());
    int __inrc = __values.count("-i") == 0 ? 0 : atoi(__values["-i"].c_str());
    string __name = __values.count("-n") == 0 ? "" : __values["-n"];
    bool __pause = __values.count("-p") == 0 ? false : true;

    if (CResourceManager::_BackgroundLayerControl.SetImageVisibility(__name, __alpha, __inrc, __pause)){
        float* __x = &CResourceManager::_BackgroundLayerControl._ImgLayerList[__name]._Coordinate.x;
        float* __y = &CResourceManager::_BackgroundLayerControl._ImgLayerList[__name]._Coordinate.y;

        if (__values.count("-s") > 1)
            if (!CResourceManager::_PositionControl.GetPosition(__values["-s"],__x,__y))
                cout << "Cmd_ShowBackground(): can't find position \""<< __values["-s"] << "\"." <<endl;

        *__x = __values.count("-x") == 0 ? *__x : atof(__values["-x"].c_str());
        *__y = __values.count("-y") == 0 ? *__y : atof(__values["-y"].c_str());

        return true;
    }

    cout << "Cmd_ShowBackground(): can't find image \""<< __name << "\"." << endl;
    return false;
}

//bool Cmd_DelBackground(string name)
bool Cmd_DelBackground(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelBackground(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        if (!CResourceManager::_BackgroundLayerControl.DelImage(args[i]))
            cout << "Cmd_DelBackground(): Image \"" << args[i] << "\" has no existed." <<endl;
    }

    return true;
}

//bool Cmd_HideBackground(string name, int inrc, bool pause)
bool Cmd_HideBackground(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_HideBackground(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //Name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause

    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_HideBackground", __flags, args, __values))
        return false;

    int __inrc = __values.count("-i") == 0 ? 0 : atoi(__values["-i"].c_str());
    string __name = __values.count("-n") == 0 ? "" : __values["-n"];
    bool __pause = __values.count("-p") == 0 ? false : true;

    if (CResourceManager::_BackgroundLayerControl.SetImageVisibility(__name, 0, __inrc, __pause))
        return true;

    cout << "Cmd_HideBackground(): can't find image \""<< __name << "\"." << endl;
    return false;
}

/*
    Cmd_AddImg: comand of add image.
    args[0]: set image name.
    args[1]: set image path.
    args[2]: set image postion of x.
    args[3]: set image postion of y.
*/
bool Cmd_AddImg(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_AddImg(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string __name = args[0];
    const char* __filename = args[1].c_str();

    if (CResourceManager::_ImgLayerControl.AddImage(__name, __filename)){
        return true;
    }
    else{
        cout << "Cmd_AddImg(): failed to load image." <<endl;
        return false;
    }
}

//bool Cmd_ShowImg(string name, int inrc, bool pause)
bool Cmd_ShowImg(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_ShowImg(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-a", FLAG_OPTIONAL));    //alpha
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //Name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //position
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    
    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_ShowImg", __flags, args, __values))
        return false;
    
    int __alpha = __values.count("-a") == 0 ? 255 : atoi(__values["-a"].c_str());
    int __inrc = __values.count("-i") == 0 ? 0 : atoi(__values["-i"].c_str());
    string __name = __values.count("-n") == 0 ? "" : __values["-n"];
    bool __pause = __values.count("-p") == 0 ? false : true;

    if (CResourceManager::_ImgLayerControl.SetImageVisibility(__name, __alpha, __inrc, __pause)){
        float* __x = &CResourceManager::_ImgLayerControl._ImgLayerList[__name]._Coordinate.x;
        float* __y = &CResourceManager::_ImgLayerControl._ImgLayerList[__name]._Coordinate.y;

        if (__values.count("-s") > 1)
            if (!CResourceManager::_PositionControl.GetPosition(__values["-s"],__x,__y))
                cout << "Cmd_ShowImg(): can't find position \""<< __values["-s"] << "\"." <<endl;

        *__x = __values.count("-x") == 0 ? *__x : atof(__values["-x"].c_str());
        *__y = __values.count("-y") == 0 ? *__y : atof(__values["-y"].c_str());

        return true;
    }

    cout << "Cmd_ShowImg(): can't find image \""<< __name << "\"." << endl;
    return false;
}

//bool Cmd_HideImg(string name, int inrc, bool pause)
bool Cmd_HideImg(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_HideImg(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //Name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause

    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_HideImg", __flags, args, __values))
        return false;

    int __inrc = __values.count("-i") == 0 ? 0 : atoi(__values["-i"].c_str());
    string __name = __values.count("-n") == 0 ? "" : __values["-n"];
    bool __pause = __values.count("-p") == 0 ? false : true;


    if (CResourceManager::_ImgLayerControl.SetImageVisibility(__name, 0, __inrc, __pause))
        return true;

    cout << "Cmd_HideImg(): can't find image \""<< __name << "\"." << endl;
    return false;
}

//bool Cmd_DelImg(string name)
bool Cmd_DelImg(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelImg(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        if (!CResourceManager::_ImgLayerControl.DelImage(args[i]))
            cout << "Cmd_DelImg(): Image \"" << args[i] << "\" has no existed." <<endl;
    }

    return true;
}

//
//void Cmd_WhiteScreen(int msec)
//{
//    if (CImgLayer::ImgLayerList.count("WHITESCREEN") < 1)
//    {
//        CImgLayer::ImgLayerList["WHITESCREEN"] = new CImgLayer(0,0);
//    }
//    
//    CImgLayer::ImgLayerList["WHITESCREEN"]->SetColor(255,255,255,0);
//    CImgLayer::ImgLayerList["WHITESCREEN"]->SetAlpha(255, &CParser::parser.Pause);
//    CImgLayer::ImgLayerList["WHITESCREEN"]->SetInterval(msec);
//}
//
//void Cmd_BlackScreen(int msec)
//{
//    if (CImgLayer::ImgLayerList.count("BLACKSCREEN") < 1)
//    {
//        CImgLayer::ImgLayerList["BLACKSCREEN"] = new CImgLayer(0,0);
//    }
//    
//    CImgLayer::ImgLayerList["BLACKSCREEN"]->SetColor(0,0,0,0);
//    CImgLayer::ImgLayerList["BLACKSCREEN"]->SetAlpha(255, &CParser::parser.Pause);
//    CImgLayer::ImgLayerList["BLACKSCREEN"]->SetInterval(msec);
//}
//
//bool Cmd_Say(const char* filename)
//{
//    return CSoundBank::_SoundControl.Say(filename);
//}

//bool Cmd_PlayBGM(const char* filename)
bool Cmd_PlayBGM(vector<string> args)
{
    if (args.size() != 1){
        cout << "Cmd_PlayBGM(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    const char* filename = args[0].c_str();
    if(!CSoundBank::_SoundControl.OnLoadBGM(filename))
        return false;

    CSoundBank::_SoundControl.PlayBgm();
    return true;
}

bool Cmd_PauseBGM(vector<string> args)
{
    if (CSoundBank::_SoundControl.GetBgmStatus() == sf::Music::Playing)
        CSoundBank::_SoundControl.PauseBgm();

    return true;
}

bool Cmd_ResumeBGM(vector<string> args)
{
    if (CSoundBank::_SoundControl.GetBgmStatus() == sf::Music::Paused)
        CSoundBank::_SoundControl.PlayBgm();

    return true;
}

//int Cmd_AddSE(const char* name, const char* filename)
bool Cmd_AddSE(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_AddSE(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    const char* name = args[0].c_str();
    const char* filename = args[1].c_str();

    switch(CSoundBank::_SoundControl.AddSE(name, filename))
    {
        case -1:
            cout << "Cmd_AddSE(): SE \"" << name << "\" has existed." <<endl;
            return false;
        break;
        case -2:
            cout << "Cmd_AddSE(): failed to add SE." <<endl;
            return false;
        break;
    }

    return true;
}

//bool Cmd_DelSE(string name)
bool Cmd_DelSE(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelSE(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        if (!CSoundBank::_SoundControl.DeleteSE(args[i]))
            cout << "Cmd_DelSE(): can't find SE \""<< args[i] << "\"." << endl;
    }

    return true;
}

//bool Cmd_PlaySE(const char* name)
bool Cmd_PlaySE(vector<string> args)
{
    if (args.size() != 1){
        cout << "Cmd_PlaySE(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    string name = args[0].c_str();

    if(CSoundBank::_SoundControl.PlaySE(name))
        return true;

    cout << "Cmd_DelSE(): can't find SE \""<< name << "\"." << endl;
    return false;
}

bool Cmd_AddVoice(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_AddVoice(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    const char* name = args[0].c_str();
    const char* filename = args[1].c_str();

    switch(CSoundBank::_SoundControl.AddVoice(name, filename))
    {
        case -1:
            cout << "Cmd_AddVoice(): Voice \"" << name << "\" has existed." <<endl;
            return false;
        break;
        case -2:
            cout << "Cmd_AddVoice(): failed to add Voice." <<endl;
            return false;
        break;
    }

    return true;
}

bool Cmd_DelVoice(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelVoice(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        if (!CSoundBank::_SoundControl.DeleteVoice(args[i]))
            cout << "Cmd_DelVoice(): can't find Voice \""<< args[i] << "\"." << endl;
    }

    return true;
}

//bool Cmd_AddButton(string name, const char* filename)
bool Cmd_AddButton(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_AddButton(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string name = args[0];
    const char* filename = args[1].c_str();

    switch (CResourceManager::_ButtonControl.AddButton(name, filename))
    {
        case 0:
            return true;
        break;
        case -1:
            cout << "Cmd_AddButton(): Button \"" << name << "\" has existed." <<endl;
        break;
        case -2:
            cout << "Cmd_AddButton(): failed to add Button." << endl;
        break;
    }

    return false;
}
//
//bool Cmd_DelButton(string name)
bool Cmd_DelButton(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelVoice(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        if (!CResourceManager::_ButtonControl.DelButton(args[i]))
            cout << "Cmd_DelButton(): can't find Button \""<< args[i] << "\"." <<endl;
    }

    return true;
}

//bool Cmd_ShowButton(string name, int incr, bool pause)
bool Cmd_ShowButton(vector<string> args)
{
    //if (!CResourceManager::_ButtonControl.SetImageVisibility(name, 255, incr, pause)){
    //    cout << "Cmd_ShowButton(): can't find Button \""<< name << "\"." <<endl;
    //    return false;
    //}

    return true;
}

//bool Cmd_HideButton(string name, int incr, bool pause)
bool Cmd_HideButton(vector<string> args)
{
    //if (!CResourceManager::_ButtonControl.SetImageVisibility(name, 0, incr, pause)){
    //    cout << "Cmd_HideButton(): can't find Button \""<< name << "\"." <<endl;
    //    return false;
    //}

    return true;
}
//
//
//void  Cmd_FullScreen()
//{
//    SDL_Event e;
//    e.key.type = SDL_KEYDOWN;
//    e.key.state = SDL_PRESSED;
//    e.key.keysym.sym = SDLK_F4;
//    SDL_PushEvent(&e);
//}
//
//void  Cmd_Window()
//{
//    SDL_Event e;
//    e.key.type = SDL_KEYDOWN;
//    e.key.state = SDL_PRESSED;
//    e.key.keysym.sym = SDLK_F5;
//    SDL_PushEvent(&e);
//}
//
//void Cmd_SetFontShadow(bool b)
//{
//    CCommon::common.FONT_SHADOW = b;
//}
//
//bool Cmd_Message(string name, string msg)
bool Cmd_Message(vector<string> args)
{
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //MessageBoxName
    __flags.push_back(pair<string, ENUM_FLAG>("-c", FLAG_OPTIONAL));    //character
    __flags.push_back(pair<string, ENUM_FLAG>("-m", FLAG_NECESSITY));    //message
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //speakername
    __flags.push_back(pair<string, ENUM_FLAG>("-v", FLAG_OPTIONAL));    //voice
    
    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_Message", __flags, args, __values))
        return false;
    
    string __msgBoxName = __values.count("-n") == 0 ? "" : __values["-n"];
    string __character = __values.count("-c") == 0 ? "" : __values["-c"];
    string __msg = __values.count("-m") == 0 ? "" : __values["-m"];
    string __speakerName = __values.count("-s") == 0 ? "" : __values["-s"];
    string __voice = __values.count("-v") == 0 ? "" : __values["-v"];

    if(CResourceManager::_MessageBoxControl._MessageBoxList.count(__msgBoxName) < 1){
        cout << "Cmd_Message(): MessageBox \"" << __msgBoxName << "\" has no existed." <<endl;
        return false;
    }

    if (__character != "")
        if(CResourceManager::_CharacterLayerControl._CharacterList.count(__character) < 1)
            cout << "Cmd_Message(): Character \"" << __character << "\" has no existed." <<endl;

    CResourceManager::_MessageBoxControl._MessageBoxList[__msgBoxName].SetText(__msg);
    CResourceManager::_MessageBoxControl._MessageBoxList[__msgBoxName].SetSpeakerName(__speakerName);

    if (__voice != ""){
        if (!CSoundBank::_SoundControl.PlayVoice(__character, __voice))
            cout << "Cmd_Message(): Voice \"" << __voice << "\" has no existed." <<endl;
    }

    return true;
}

//bool Cmd_AddMessageBox(string name, const char* filename)
bool Cmd_AddMessageBox(vector<string> args)
{
    if (args.size() != 2){
        cout << "Cmd_AddMessageBox(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string name = args[0];
    const char* filename = args[1].c_str();

    switch (CResourceManager::_MessageBoxControl.AddMessageBox(name, filename))
    {
        case 0:
            return true;
        break;
        case -1:
            cout << "Cmd_AddMessageBox(): MessageBox \"" << name << "\" has existed." <<endl;
        break;
        case -2:
            cout << "Cmd_AddMessageBox(): failed to add MessageBox." << endl;
        break;
    }

    return false;
}

//bool Cmd_DelMessageBox(string name)
bool Cmd_DelMessageBox(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_DelMessageBox(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (unsigned int i=0; i<args.size(); i++){
        if (CResourceManager::_MessageBoxControl.DelMessageBox(args[i]))
            cout << "Cmd_DelMessageBox(): can't find MessageBox \""<< args[i] << "\"." <<endl;
    }

    return true;
}

//bool Cmd_ShowMessageBox(string name, int incr, bool pause)
bool Cmd_ShowMessageBox(vector<string> args)
{
    if (args.size() < 1){
        cout << "Cmd_ShowMessageBox(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-a", FLAG_OPTIONAL));    //alpha
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //MessageBoxName
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause

    map<string,string> __values;
    if (!Cmd_ArgsToKV("Cmd_ShowCharacterLayer", __flags, args, __values))
        return false;

    int alpha = __values.count("-a") == 0 ? 255 : atoi(__values["-a"].c_str());
    string name = __values.count("-n") == 0 ? "" : __values["-n"];
    int incr = __values.count("-i") == 0 ? CCommon::common.INCREMENT : atoi(__values["-i"].c_str());
    bool pause = __values.count("-p") == 0 ? false : true;

    if (!CResourceManager::_MessageBoxControl.SetImageVisibility(name, alpha, incr, pause)){
        cout << "Cmd_ShowMessageBox(): can't find MessageBox \""<< name << "\"." <<endl;
        return false;
    }

    return true;
}

bool Cmd_HideMessageBox(vector<string> args)
{
    if (args.size() != 3){
        cout << "Cmd_HideMessageBox(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string name = args[0];
    int incr = atoi(args[1].c_str()); 
    bool pause = args[2] == "T" ? true : false;

    if (!CResourceManager::_MessageBoxControl.SetImageVisibility(name, 0, incr, pause)){
        cout << "Cmd_HideMessageBox(): can't find MessageBox \""<< name << "\"." <<endl;
        return false;
    }

    return true;
}
//
//
//bool Cmd_MenuBoxAddBtn(string name, const char* filename, const char* section)
//{
//    return CMenuBox::menubox.AddBtn(name, filename, section);
//}
//
//bool Cmd_MenuBoxDelBtn(string name)
//{
//    return CMenuBox::menubox.DelBtn(name);
//}
//
//int Cmd_ShowMenuBox(const char* filename, const char* section, bool pause)
//{
//    if (CMenuBox::menubox.Visible)
//        return 0;
//
//    if(!CParser::parser.ExecuteAllCmd(filename, section))
//        return -1;
//
//    CMenuBox::menubox.Refresh();
//    if (pause)
//        CMenuBox::menubox.Show(&CParser::parser.Pause);
//    else
//        CMenuBox::menubox.Show(NULL);
//
//    return 1;
//}
//
//bool Cmd_HideMenuBox(bool pause)
//{
//    if (!CMenuBox::menubox.Visible)
//        return false;
//
//    CMenuBox::menubox.ClearBtn();
//    if (pause)
//        CMenuBox::menubox.Hide(&CParser::parser.Pause);
//    else
//        CMenuBox::menubox.Hide(NULL);
//
//    return true;
//}
//
//bool Cmd_ShowInfoBox(bool pause)
//{
//    if (CObjectInfoBox::objectinfobox.Visible)
//        return false;
//
//    if (pause)
//        CObjectInfoBox::objectinfobox.Show(&CParser::parser.Pause);
//    else
//        CObjectInfoBox::objectinfobox.Show(NULL);
//    
//    return true;
//}
//
//bool Cmd_HideInfoBox(bool pause)
//{
//    if (!CObjectInfoBox::objectinfobox.Visible)
//        return false;
//
//    if (pause)
//        CObjectInfoBox::objectinfobox.Hide(&CParser::parser.Pause);
//    else
//        CObjectInfoBox::objectinfobox.Hide(NULL);
//    
//    return true;
//}
//
//bool Cmd_ShowLogBox(bool pause)
//{
//    if (CLogBox::logbox.Visible)
//        return false;
//
//    if (pause)
//        CLogBox::logbox.Show(&CParser::parser.Pause);
//    else
//        CLogBox::logbox.Show(NULL);
//    
//    return true;
//}
//
//bool Cmd_HideLogBox(bool pause)
//{
//    if (!CLogBox::logbox.Visible)
//        return false;
//
//    if (pause)
//        CLogBox::logbox.Hide(&CParser::parser.Pause);
//    else
//        CLogBox::logbox.Hide(NULL);
//    
//    return true;
//}
//
//void Cmd_PrintInfoBox(const char* type, string id)
//{
//    if (strcmp(type, "Equip") == 0)
//    {
//        //CObjectListBox::objectlistbox.List.type = TYPE_EQUIP;
//        //CObjectListBox::objectlistbox.List.ptr.equip_list = NULL;
//        //CObjectListBox::objectlistbox.List.ptr.equip_list = &CPlayerDataControl::playerdatacontrol.EquipList;
//    }
//    else if (strcmp(type, "Item") == 0)
//    {
//        //CObjectListBox::objectlistbox.List.type = TYPE_ITEM;
//        //CObjectListBox::objectlistbox.List.ptr.item_list = NULL;
//        //CObjectListBox::objectlistbox.List.ptr.item_list = &CPlayerDataControl::playerdatacontrol.ItemList;
//    }
//}
//
//bool Cmd_AddVariable(string name, string val, map<string, string> &var_table)
//{
//    name = "$" + name;
//    if(var_table.count(name) > 0)
//        return false;
//
//    var_table[name] = val;
//    return true;
//}
//
//bool Cmd_SetVariable(string name, string val, map<string, string> &var_table)
//{
//    name = "$" + name;
//    if(var_table.count(name) < 1)
//        return false;
//    
//    var_table[name] = val;
//    return true;
//}
//
//bool Cmd_DelVariable(string name, map<string, string> &var_table)
//{
//    name = "$" + name;
//    if(var_table.count(name) < 1)
//        return false;
//
//    var_table.erase(name);
//    return true;
//}
//
//bool Cmd_EditEquipList(string id, int num)
//{
//    if (!CLoadObject::loadobject.IsAlreadyExists("Equip", id.c_str()))
//        return -1;
//
//    for (int i = 0; i < CPlayerDataControl::playerdatacontrol.EquipList.size(); i++)
//    {
//        if (CPlayerDataControl::playerdatacontrol.EquipList[i].first.Name == id)
//        {
//            CPlayerDataControl::playerdatacontrol.EquipList[i].second += num;
//            if (CPlayerDataControl::playerdatacontrol.EquipList[i].second <= 0)
//            {
//                CPlayerDataControl::playerdatacontrol.EquipList.erase(
//                    CPlayerDataControl::playerdatacontrol.EquipList.begin() + i);
//            }
//
//            return 1;
//        }
//    }
//
//    if (num < 1)
//        return 0;
//
//    Equip equip;
//    if(CLoadObject::loadobject.GetEquip(id.c_str(),equip))
//    {
//        CPlayerDataControl::playerdatacontrol.EquipList.push_back(make_pair(equip, num));
//        return 1;
//    }
//    else
//        return -2;
//}
//
//bool Cmd_EditItemList(string id, int num)
//{
//    if (!CLoadObject::loadobject.IsAlreadyExists("Item", id.c_str()))
//        return -1;
//    
//    for (int i = 0; i < CPlayerDataControl::playerdatacontrol.ItemList.size(); i++)
//    {
//        if (CPlayerDataControl::playerdatacontrol.ItemList[i].first.Name == id)
//        {
//            CPlayerDataControl::playerdatacontrol.ItemList[i].second += num;
//            if (CPlayerDataControl::playerdatacontrol.ItemList[i].second <= 0)
//            {
//                CPlayerDataControl::playerdatacontrol.ItemList.erase(
//                    CPlayerDataControl::playerdatacontrol.ItemList.begin() + i);
//            }
//
//            return 1;
//        }
//    }
//
//    if (num < 1)
//        return 0;
//
//    Item item;
//    if(CLoadObject::loadobject.GetItem(id.c_str(), item))
//    {
//        CPlayerDataControl::playerdatacontrol.ItemList.push_back(make_pair(item, num));
//        return 1;
//    }
//    else
//        return -2;
//}
//
//void Cmd_EditMoney(int num)
//{
//    CPlayerDataControl::playerdatacontrol.Money += num;
//}
//
////void Cmd_SetMoney(int num)
////{
////    CPlayerDataControl::playerdatacontrol.Money = num;
////}
//
//void Cmd_DelCommand(vector<string> &cmdlist, int num)
//{
//    if (num > 0)
//    {
//        if (cmdlist.size() > 0)
//        {
//            if (cmdlist.size() > num)
//                cmdlist.erase(cmdlist.begin(), cmdlist.begin() + num);
//            else
//                cmdlist.clear();
//        }
//    }
//}
//
//bool Cmd_DelCommand(vector<string> &cmdlist, string flag)
//{
//    flag = "#" + flag;
//    for(int i = 0; i < cmdlist.size() ; i++)
//    {
//        if (cmdlist[i] == flag)
//        {
//            Cmd_DelCommand(cmdlist, i + 1);
//            return true;
//        }
//    }
//    return false;
//}
//
//bool Cmd_AddMapEvent(string name, const char* filename, const char* section)
//{
//    if(CMapEventControl::MapEventControl.MapEventList.count(name) < 1)
//        return false;
//
//    vector<string> cmdlist;
//
//    if(CParser::parser.LoadScript(filename, section, cmdlist))
//    {
//        CMapEventControl::MapEventControl.MapEventList[name] = cmdlist;
//        cmdlist.clear();
//        return true;
//    }
//    else
//    {
//        cmdlist.clear();
//        return false;
//    }
//}
//
//bool Cmd_AddMapEventPoint(string name, int x, int y)
//{
//    for (int i = CMapEventControl::MapEventControl.EventPoint.size() - 1; i >= 0 ; i--)
//    {
//        if (CMapEventControl::MapEventControl.EventPoint[i].first == name &&
//            CMapEventControl::MapEventControl.EventPoint[i].second.first == x &&
//            CMapEventControl::MapEventControl.EventPoint[i].second.second == y)
//            return false;
//    }
//
//    CMapEventControl::MapEventControl.EventPoint.push_back(make_pair(name, make_pair(x, y)));
//    return true;
//}
//
//bool Cmd_DelMapEvent(string name)
//{
//    if(CMapEventControl::MapEventControl.MapEventList.count(name) < 1)
//        return false;
//
//    CMapEventControl::MapEventControl.MapEventList[name].clear();
//    CMapEventControl::MapEventControl.MapEventList.erase(name);
//
//    for (int i = CMapEventControl::MapEventControl.EventPoint.size() - 1; i >= 0 ; i--)
//    {
//        if (CMapEventControl::MapEventControl.EventPoint[i].first == name)
//            CMapEventControl::MapEventControl.EventPoint.erase(
//                CMapEventControl::MapEventControl.EventPoint.begin() + i);
//    }
//
//    return true;
//}
//
//void Cmd_ClearMapEvent()
//{
//    CMapEventControl::MapEventControl.OnCleanup();
//}
//
//bool Cmd_PlayAnimation(string name, int x, int y)
//{
//    return CAnimationBank::animationbank.PlayAnime(name, x, y);
//}
//
//int Cmd_ToNextAnimationData(string name)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(name) < 1)
//        return -1;
//
//    if (!CAnimationBank::animationbank.AnimationList[name].Running)
//        return -2;
//        
//    CAnimationBank::animationbank.AnimationList[name].Next();
//    return 0;
//}
//
//int Cmd_StopAnimation(string name)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(name) < 1)
//        return -1;
//
//    if (!CAnimationBank::animationbank.AnimationList[name].Running)
//        return -2;
//
//    CAnimationBank::animationbank.AnimationList[name].Stop();
//    return 0;
//}
//
//int Cmd_AddAnimationScript(string name, int framerate)
//{
//    if (framerate < 1)
//        return -1;
//    
//    if(CAnimationBank::animationbank.AnimationList.count(name) > 0)
//        return -2;
//
//    CAnimationBank::animationbank.AnimationList[name] = CAnimationScript(framerate);
//
//    return 0;
//}
//
//int Cmd_DelAnimationScript(string name)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(name) < 1)
//        return -1;
//
//    if (CAnimationBank::animationbank.AnimationList[name].Running)
//        return 0;
//
//    CAnimationBank::animationbank.AnimationList.erase(name);
//    return 1;
//}
//
//int Cmd_AddAnimationData(string scrname ,string dataname, string filename, 
//    int startindex, int maxframes, bool loop, int size, string se)
//{
//    if (maxframes < 1)
//        return -1;
//    
//    if(CAnimationBank::animationbank.AnimationList.count(scrname) < 1)
//        return -2;
//
//    CAnimationBank::animationbank.AnimationList[scrname].Script.push_back(
//        new CAnimationData(dataname, filename, startindex, maxframes, loop, size, se));
//
//    return 0;
//}
//
//int Cmd_DelAnimationData(string scrname, string dataname)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(scrname) < 1)
//        return -1;
//    
//    if (CAnimationBank::animationbank.AnimationList[scrname].Running)
//        return -2;
//
//    int count = 0;
//    for (int i = CAnimationBank::animationbank.AnimationList[scrname].Script.size() - 1; i >= 0; i--)
//    {
//        if (CAnimationBank::animationbank.AnimationList[scrname].Script[i]->Name == dataname)
//        {
//            delete CAnimationBank::animationbank.AnimationList[scrname].Script[i];
//            CAnimationBank::animationbank.AnimationList[scrname].Script.erase(
//                CAnimationBank::animationbank.AnimationList[scrname].Script.begin() + i);
//            count++;
//        }
//    }
//    return count;
//}
//
//int Cmd_If(string op, string val1, string val2)
//{
//    bool b = true;
//
//    if (op == "<")
//    {
//        b = atoi(val1.c_str()) < atoi(val2.c_str());
//    }
//    else if (op == ">")
//    {
//        b = atoi(val1.c_str()) > atoi(val2.c_str());
//    }
//    else if (op == ">=")
//    {
//        b = atoi(val1.c_str()) >= atoi(val2.c_str());
//    }
//    else if (op == "<=")
//    {
//        b = atoi(val1.c_str()) <= atoi(val2.c_str());
//    }
//    else if (op == "==")
//    {
//        b = val1 == val2;
//    }
//    else if (op == "!=")
//    {
//        b = val1 != val2;
//    }
//    else
//    {
//        return -1;
//    }
//
//    if (b)
//        return 1;
//    else
//        return 0;
//}
