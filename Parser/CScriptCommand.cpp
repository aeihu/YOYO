/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
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
#include "../Common/CResourceControl.h"
#include "../Common/CCommon.h"
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Effect/CParticleSystem.h"
#include "../GSM_Window/CLogBox.h"
#include <iostream>
#include <algorithm>

typedef enum{
    FLAG_NECESSITY = 1,
    FLAG_OPTIONAL,
    FLAG_NONPARAMETRIC,
}ENUM_FLAG;

bool Common_ArgsToKV(const char* funcName, list<pair<string, ENUM_FLAG> >& flags, vector<string>& args, map<string, vector<string> >& result)
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
                    __itOfArgs = std::find(args.begin(), args.end(), (*__it).first);

                    if (__itOfArgs != args.end()){
                        if ((*__it).second == FLAG_NONPARAMETRIC){
                            result[(*__it).first] = vector<string>();
                        }
                        else{
                            ++__itOfArgs;
                            while (__itOfArgs != args.end()){
                                if ((*__itOfArgs)[0] == '-' && atoi((*__itOfArgs).c_str()) == 0)
                                    break;

                                result[(*__it).first].push_back(*__itOfArgs);
                                ++__itOfArgs;
                            }

                            if (result[(*__it).first].size() < 1){
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
    for (map<string, vector<string> >::iterator it=result.begin();
        it!=result.end();)
    {
        cout << (*it).first << " : ";
        for (size_t i=0; i<(*it).second.size(); i++)
            cout << (*it).second[i] << " ";
        
        cout << endl;
        it++;
    }
#endif

    return true;
}

bool Common_FuncOfShow(string objTypeName, vector<string>& args)
{ 
    string __funcName = "Cmd_Show" + objTypeName;
    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-a", FLAG_OPTIONAL));    //alpha
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-l", FLAG_OPTIONAL));    //layer
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //position
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //pause

    map<string, vector<string> > __values;
    if (!Common_ArgsToKV(__funcName.c_str(), __flags, args, __values))
        return false;

    if (__values.count("-n") == 0)
        return false;
    
    bool __result = true;
    string __name = __values["-n"][0];
    bool __pause = __values.count("-p") == 0 ? false : true;
    bool __reset = __values.count("-r") == 0 ? false : true;
    float __alpha = __values.count("-a") == 0 ? 255.0f : atof(__values["-a"][0].c_str());
    size_t __inte = __values.count("-i") == 0 ? (float)CCommon::_Common.INTERVAL : 
        atof(__values["-i"][0].c_str());

    if (CResourceControl::_ResourceManager._DrawableObjectControl.IsExists(objTypeName+":"+__name)){
        CImageBaseClass* __obj = 
            CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+__name);

        if (__values.count("-l") > 0){
            CResourceControl::_ResourceManager._DrawableObjectControl.SetDrawableObjectLayerOrder(
                objTypeName+":"+__name, atoi(__values["-l"][0].c_str()));
        }

        float* __x = &__obj->GetPosition().x;
        float* __y = &__obj->GetPosition().y;

        *__x = __values.count("-x") == 0 ? *__x : atof(__values["-x"][0].c_str());
        *__y = __values.count("-y") == 0 ? *__y : atof(__values["-y"][0].c_str());

        if (__values.count("-s") > 1)
            if (!CResourceControl::_ResourceManager._PositionControl.GetPosition(__values["-s"][0],__x,__y))
                cout << __funcName << "(): can't find position \""<< __values["-s"][0] << "\"." <<endl;
        
        __obj->AddAction(__obj->CreateActionOfAlpha(__inte, __alpha, __reset, __pause));
        __obj->SetPosition(*__x, *__y);
        return true;
    }
    else
        cout << __funcName << "(): can't find "<< objTypeName <<" \""<< __name << "\"." <<endl;

    return false;
}

bool Common_FuncOfHide(string objTypeName, vector<string>& args)
{ 
    string __funcName = "Cmd_Hide" + objTypeName;
    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //interval
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //pause

    map<string, vector<string> > __values;
    if (!Common_ArgsToKV(__funcName.c_str(), __flags, args, __values))
        return false;

    if (__values.count("-n") == 0)
        return false;
    
    bool __pause = __values.count("-p") == 0 ? false : true;
    bool __reset = __values.count("-r") == 0 ? false : true;
    string __name = __values["-n"][0];
    size_t __inte = __values.count("-i") == 0 ? (float)CCommon::_Common.INTERVAL :
        atoi(__values["-i"][0].c_str());

    CImageBaseClass* __obj = 
        CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+__name);

    if (__obj != NULL){
        __obj->AddAction(__obj->CreateActionOfAlpha(__inte, 0, __reset, __pause));
        return true;
    }
    return false;
}
//
//bool Common_FuncOfAdd(string objTypeName, vector<string>& args)
//{
//    if (args.size() != 2){
//        cout << "Cmd_Add" << objTypeName << "(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//
//    string __name = args[0];
//    const char* __filename = args[1].c_str();
//
//    if (objTypeName == "Font"){
//        CObject* __obj = NULL;
//
//        if (objTypeName == "Font") __obj = CFont::Create(__filename);
//
//        if (__obj != NULL){
//            if (CResourceControl::_ResourceManager.AddObject(objTypeName+":"+__name, __obj))
//                return true;
//            else
//                cout << "Cmd_Add" << objTypeName <<"(): " << objTypeName << " \""<< __name << "\" has existed." <<endl;
//        }
//        else
//            cout << "Cmd_Add" << objTypeName << "(): failed to create " << objTypeName << "." <<endl;
//    }
//    else{
//        CImageBaseClass* __obj = NULL;
//
//        if (objTypeName == "Img") __obj = CImageBaseClass::Create(__filename);
//        else if (objTypeName == "Background") __obj = CImageBaseClass::Create(__filename);
//        else if (objTypeName == "Button") __obj = CButton::Create(__filename);
//        else if (objTypeName == "CharacterLayer") __obj = CCharacterLayer::Create(__filename);
//        else if (objTypeName == "LogBox") __obj = CLogBox::Create(__filename);
//        else if (objTypeName == "MessageBox") __obj = CMessageBox::Create(__filename);
//        else if (objTypeName == "ParticleSystem") __obj = CParticleSystem::Create(__filename);
//        
//        if (__obj != NULL){
//            if (CResourceControl::_ResourceManager.AddDrawableObject(objTypeName+":"+__name, __obj)){
//                
//                //__msgBox->SetFont(
//                //    static_cast<CFont*>(CResourceControl::_ResourceManager.GetObject("__main"))->GetFont());
//                return true;
//            }
//            else
//                cout << "Cmd_Add" << objTypeName <<"(): " << objTypeName << " \""<< __name << "\" has existed." <<endl;
//        }
//        else
//            cout << "Cmd_Add" << objTypeName << "(): failed to create " << objTypeName << "." <<endl;
//    }
//
//    return false;
//}
//
//bool Common_FuncOfDelete(string objTypeName, vector<string>& args)
//{ 
//    string __funcName = "Cmd_Del" + objTypeName;
//    if (args.size() < 1){
//        cout << __funcName << "(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//    
//    if (objTypeName != "Font") {
//        for (size_t i=0; i<args.size(); i++){
//            if (!CResourceControl::_ResourceManager.DelDrawableObject(objTypeName+":"+args[i]))
//                cout << __funcName << "(): can't find " << objTypeName << " \""<< args[i] << "\"." <<endl;
//        }
//    }
//    else{
//        for (size_t i=0; i<args.size(); i++){
//            if (!CResourceControl::_ResourceManager.DelObject(objTypeName+":"+args[i]))
//                cout << __funcName << "(): can't find " << objTypeName << " \""<< args[i] << "\"." <<endl;
//        }
//    }
//
//    return true;
//}

bool Common_FuncOfLayerOrder(string objTypeName, vector<string>& args)
{ 
    string __funcName = "Cmd_SetLayerOrder" + objTypeName;

    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-l", FLAG_NECESSITY));    //layer

    map<string, vector<string> > __values;
    if (!Common_ArgsToKV(__funcName.c_str(), __flags, args, __values))
        return false;

    if (__values.count("-n") == 0 || __values.count("-l") == 0)
        return false;
   
    for (size_t i=0; i<__values["-n"].size(); i++){
        char __layer = i<__values["-l"].size() ? atoi(__values["-l"][i].c_str()) : atoi(__values["-l"][__values["-i"].size()-1].c_str());

        if (CResourceControl::_ResourceManager._DrawableObjectControl.SetDrawableObjectLayerOrder(objTypeName+":"+__values["-n"][i], __layer))
            cout << __funcName <<"(): " << objTypeName << " \""<< __values["-n"][i] << "\" has no existed." <<endl;
    }

    return true;
}

/*==============================================================
    commad of script
===============================================================*/

//bool Cmd_ShowInfo(vector<string>& args)
//{
//    CResourceManager::GetInfo();
//    //CResourceManager::GetInfo("ImageList", CResourceManager::_ImgLayerControl._imgLayerList);
//    //CResourceManager::GetInfo("BackgroundList", CResourceManager::_BackgroundLayerControl._imgLayerList);
//    //CResourceManager::GetInfo("CharacterList", CResourceManager::_CharacterLayerControl._characterList);
//    //CResourceManager::GetInfo("MessageBoxList", CResourceManager::_MessageBoxControl._messageBoxList);
//    return true;
//}

bool Cmd_AddPosition(vector<string>& args)
{
    if (args.size() != 3){
        cout << "Cmd_AddPosition(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string name = args[0];
    float x = atof(args[1].c_str());
    float y = atof(args[2].c_str());
    CResourceControl::_ResourceManager._PositionControl.AddPosition(name, x, y);
    return true;
}

bool Cmd_DelPosition(vector<string>& args)
{
    if (args.size() < 1){
        cout << "Cmd_DelPosition(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (size_t i=0; i<args.size(); i++){
        CResourceControl::_ResourceManager._PositionControl.DelPosition(args[i]);
    }

    return true;
}

//bool Cmd_AddCharacterLayer(vector<string>& args)
//{
//    return Common_FuncOfAdd("CharacterLayer", args);
//}
//
//bool Cmd_DelCharacterLayer(vector<string>& args)
//{
//    return Common_FuncOfDelete("CharacterLayer", args);
//}

bool Cmd_ShowCharacterLayer(vector<string>& args)
{
    return Common_FuncOfShow("CharacterLayer", args);
}

bool Cmd_MoveCharacterLayer(vector<string>& args)
{
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //position
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //pause

    map<string, vector<string> > __values;
    if (!Common_ArgsToKV("Cmd_MoveCharacterLayer", __flags, args, __values))
        return false;

    if (__values.count("-n") == 0)
        return false;

    bool __pause = __values.count("-p") == 0 ? false : true;
    bool __reset = __values.count("-r") == 0 ? false : true;
    string __name = __values["-n"][0];
    float __x = 0;
    float __y = 0;
    char __flag = 0;
    size_t __inte = __values.count("-i") == 0 ? 
        CCommon::_Common.INTERVAL : atoi(__values["-i"][0].c_str());

    if (__values.count("-x") > 0){
        __x = atof(__values["-x"][0].c_str());
        __flag |= 0x1;
    }

    if (__values.count("-y") > 0){
        __y = atof(__values["-y"][0].c_str());
        __flag |= 0x2;
    }

    if (__values.count("-s") > 1){
        if (!CResourceControl::_ResourceManager._PositionControl.GetPosition(__values["-s"][0], &__x, &__y)){
            cout << "Cmd_MoveCharacterLayer(): can't find position \""<< __values["-s"][0] << "\"." <<endl;
        }
        __flag = 3;
    }
        
    if (CResourceControl::_ResourceManager._DrawableObjectControl.IsExists("CharacterLayer:"+__name)){
        CImageBaseClass* __obj = 
            CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("CharacterLayer:"+__name);

        switch (__flag)
        {
            case 1:
                __obj->AddAction(__obj->CreateActionOfMoveX(__inte, __x, __reset, __pause));
            break;
            case 2:
                __obj->AddAction(__obj->CreateActionOfMoveY(__inte, __y, __reset, __pause));
            break;
            case 3:
                __obj->AddAction(__obj->CreateActionOfMove(__inte, __x, __y, __reset, __pause));
            break;
        }
        return true;
    }
    else
        cout << "Cmd_MoveCharacterLayer(): can't find character layer \""<< __name << "\"." <<endl;

    return false;
}

bool Cmd_HideCharacterLayer(vector<string>& args)
{
    return Common_FuncOfHide("CharacterLayer", args);
}

bool Cmd_SetFaceCharacterLayer(vector<string>& args)
{
    if (args.size() != 2){
        cout << "Cmd_SetFaceCharacterLayer(): command invaild. can't set " << args.size()
            << " argument(s) in the command." << endl;
        return false;
    }

    string __name = args[0];
    string __face = args[1];

    if (!CResourceControl::_ResourceManager._DrawableObjectControl.IsExists("CharacterLayer:"+__name)){
        cout << "Cmd_SetFaceCharacterLayer(): can't find character layer \""<< __name << "\"." <<endl;
        return false;
    }

    CCharacterLayer* __chara = static_cast<CCharacterLayer*>(
        CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("CharacterLayer:"+__name));
    if (__chara->SetFace(__face))
        return true;
    else{
        cout << "Cmd_SetFaceCharacterLayer(): can't find face layer \""<< __face << "\"." <<endl;
        return false;
    }
}

bool Cmd_SetCharacterLayerOrder(vector<string>& args)
{
    return Common_FuncOfLayerOrder("CharacterLayer", args);
}
//
//bool Cmd_AlphaCharacterLayer(char postion, int alpha)
//{
//    //for (int i = 0; i < CResourceManager::_CharacterLayerControl._characterList.size(); i++)
//    //{
//    //    if(CResourceManager::_CharacterLayerControl._characterList[i]->Postion == postion)
//    //    {
//    //        CResourceManager::_CharacterLayerControl._characterList[i]->Alpha = alpha;
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
//    return CParser::_Parser.LoadScript(filename, Section);
//}
//
//bool Cmd_AddBackground(vector<string>& args)
//{
//    return Common_FuncOfAdd("Background", args);
//}

bool Cmd_ShowBackground(vector<string>& args)
{
    return Common_FuncOfShow("Background", args);
}

//bool Cmd_DelBackground(vector<string>& args)
//{
//    return Common_FuncOfDelete("Background", args);
//}

bool Cmd_HideBackground(vector<string>& args)
{
    return Common_FuncOfHide("Background", args);
}

bool Cmd_SetBackgroundLayerOrder(vector<string>& args)
{
    return Common_FuncOfLayerOrder("Background", args);
}
/*
    Cmd_AddImg: comand of add image.
    args[0]: set image name.
    args[1]: set image path.
    args[2]: set image postion of x.
    args[3]: set image postion of y.
*/
//bool Cmd_AddImg(vector<string>& args)
//{
//    return Common_FuncOfAdd("Img", args);
//}

bool Cmd_ShowImg(vector<string>& args)
{
    return Common_FuncOfShow("Img", args);
}

bool Cmd_HideImg(vector<string>& args)
{
    return Common_FuncOfHide("Img", args);
}

//bool Cmd_DelImg(vector<string>& args)
//{
//    return Common_FuncOfDelete("Img", args);
//}

bool Cmd_SetImgLayerOrder(vector<string>& args)
{
    return Common_FuncOfLayerOrder("Img", args);
}

bool Cmd_PlayBGM(vector<string>& args)
{
    if (args.size() != 1){
        cout << "Cmd_PlayBGM(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    const char* filename = args[0].c_str();
    if(!CResourceControl::_ResourceManager._SoundControl.OnLoadBGM(filename))
        return false;

    CResourceControl::_ResourceManager._SoundControl.PlayBgm();
    return true;
}

bool Cmd_PauseBGM(vector<string>& args)
{
    if (CResourceControl::_ResourceManager._SoundControl.GetBgmStatus() == sf::Music::Playing)
        CResourceControl::_ResourceManager._SoundControl.PauseBgm();

    return true;
}

bool Cmd_ResumeBGM(vector<string>& args)
{
    if (CResourceControl::_ResourceManager._SoundControl.GetBgmStatus() == sf::Music::Paused)
        CResourceControl::_ResourceManager._SoundControl.PlayBgm();

    return true;
}

//bool Cmd_AddSE(vector<string>& args)
//{
//    if (args.size() != 2){
//        cout << "Cmd_AddSE(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//    
//    const char* name = args[0].c_str();
//    const char* filename = args[1].c_str();
//
//    switch(CSoundBank::_SoundControl.AddSE(name, filename))
//    {
//        case -1:
//            cout << "Cmd_AddSE(): SE \"" << name << "\" has existed." <<endl;
//            return false;
//        break;
//        case -2:
//            cout << "Cmd_AddSE(): failed to add SE." <<endl;
//            return false;
//        break;
//    }
//
//    return true;
//}
//
//bool Cmd_DelSE(vector<string>& args)
//{
//    if (args.size() < 1){
//        cout << "Cmd_DelSE(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//
//    for (size_t i=0; i<args.size(); i++){
//        if (!CSoundBank::_SoundControl.DeleteSE(args[i]))
//            cout << "Cmd_DelSE(): can't find SE \""<< args[i] << "\"." << endl;
//    }
//
//    return true;
//}

bool Cmd_PlaySE(vector<string>& args)
{
    if (args.size() != 1){
        cout << "Cmd_PlaySE(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    string name = args[0].c_str();

    if(CResourceControl::_ResourceManager._SoundControl.PlaySE(name))
        return true;

    cout << "Cmd_DelSE(): can't find SE \""<< name << "\"." << endl;
    return false;
}

//bool Cmd_AddVoice(vector<string>& args)
//{
//    if (args.size() != 2){
//        cout << "Cmd_AddVoice(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//    
//    const char* name = args[0].c_str();
//    const char* filename = args[1].c_str();
//
//    switch(CSoundBank::_SoundControl.AddVoice(name, filename))
//    {
//        case -1:
//            cout << "Cmd_AddVoice(): Voice \"" << name << "\" has existed." <<endl;
//            return false;
//        break;
//        case -2:
//            cout << "Cmd_AddVoice(): failed to add Voice." <<endl;
//            return false;
//        break;
//    }
//
//    return true;
//}
//
//bool Cmd_DelVoice(vector<string>& args)
//{
//    if (args.size() < 1){
//        cout << "Cmd_DelVoice(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//
//    for (size_t i=0; i<args.size(); i++){
//        if (!CSoundBank::_SoundControl.DeleteVoice(args[i]))
//            cout << "Cmd_DelVoice(): can't find Voice \""<< args[i] << "\"." << endl;
//    }
//
//    return true;
//}

//bool Cmd_AddButton(vector<string>& args)
//{
//    return Common_FuncOfAdd("Button", args);
//}
//
//bool Cmd_DelButton(vector<string>& args)
//{
//    return Common_FuncOfDelete("Button", args);
//}

bool Cmd_ShowButton(vector<string>& args)
{
    return Common_FuncOfShow("Button", args);
}

bool Cmd_HideButton(vector<string>& args)
{
    return Common_FuncOfHide("Button", args);
}

bool Cmd_SetButtonLayerOrder(vector<string>& args)
{
    return Common_FuncOfLayerOrder("Button", args);
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
//    CCommon::_Common.FONT_SHADOW = b;
//}
//
bool Cmd_Message(vector<string>& args)
{
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //MessageBoxName
    __flags.push_back(pair<string, ENUM_FLAG>("-c", FLAG_OPTIONAL));    //character
    __flags.push_back(pair<string, ENUM_FLAG>("-m", FLAG_NECESSITY));    //message
    __flags.push_back(pair<string, ENUM_FLAG>("-s", FLAG_OPTIONAL));    //speakername
    __flags.push_back(pair<string, ENUM_FLAG>("-v", FLAG_OPTIONAL));    //voice
    
    map<string, vector<string> > __values;
    if (!Common_ArgsToKV("Cmd_Message", __flags, args, __values))
        return false;
    
    string __msgBoxName = __values.count("-n") == 0 ? "" : __values["-n"][0];
    string __msg = __values.count("-m") == 0 ? "" : __values["-m"][0];
    string __speakerName = __values.count("-s") == 0 ? "" : __values["-s"][0];
    string __voice = __values.count("-v") == 0 ? "" : __values["-v"][0];

    CImageBaseClass* __obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("MessageBox:"+__msgBoxName);
    if(__obj == NULL){
        cout << "Cmd_Message(): MessageBox \"" << __msgBoxName << "\" has no existed." <<endl;
        return false;
    }
    
    CMessageBox* __msgbox = static_cast<CMessageBox*>(__obj);

    if (__values.count("-c") != 0){
        for (size_t i=0; i<__values["-c"].size(); i++){
            if (__values["-c"][i] != ""){
                __obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("CharacterLayer:"+__values["-c"][i]);
                if(__obj == NULL)
                    cout << "Cmd_Message(): CharacterLayer \"" << __values["-c"][i] << "\" has no existed." <<endl;
                else{
                    CCharacterLayer* __chara = static_cast<CCharacterLayer*>(__obj);
                    __chara->SetVoice(__voice);
                }
            }
        }
    }

    __msgbox->SetText(__msg);
    __msgbox->SetSpeakerName(__speakerName);

    if (__voice != ""){
        if (!CResourceControl::_ResourceManager._SoundControl.PlayVoice(__voice))
            cout << "Cmd_Message(): Voice \"" << __voice << "\" has no existed." <<endl;
    }

    //__obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("LogBox:log");
    //if(__obj == NULL){
    //    cout << "Cmd_Message(): LogBox \"" << __msgBoxName << "\" has no existed." <<endl;
    //    return false;
    //}
    //CLogBox* __logbox = static_cast<CLogBox*>(__obj);
    
    //CObject* sda = CResourceControl::_ResourceManager.GetObject("Font:__main");
    //CFont* __font = static_cast<CFont*>(sda);
    //__logbox->AddLog(__msgbox->GetText(), NULL, __font->GetFont());
    return true;
}

//bool Cmd_AddMessageBox(vector<string>& args)
//{
//    return Common_FuncOfAdd("MessageBox", args);
//}
//
//bool Cmd_DelMessageBox(vector<string>& args)
//{
//    return Common_FuncOfDelete("MessageBox", args);
//}

bool Cmd_ShowMessageBox(vector<string>& args)
{   
    return Common_FuncOfShow("MessageBox", args);
}

bool Cmd_HideMessageBox(vector<string>& args)
{
    return Common_FuncOfHide("MessageBox", args);
}

bool Cmd_SetMessageBoxLayerOrder(vector<string>& args)
{
    return Common_FuncOfLayerOrder("MessageBox", args);
}

//bool Cmd_AddLogBox(vector<string>& args)
//{
//    return Common_FuncOfAdd("LogBox", args);
//}

bool Cmd_ShowLogBox(vector<string>& args)
{
    return Common_FuncOfShow("LogBox", args);
}

bool Cmd_HideLogBox(vector<string>& args)
{
    return Common_FuncOfHide("LogBox", args);
}

//bool Cmd_DelLogBox(vector<string>& args)
//{
//    return Common_FuncOfDelete("LogBox", args);
//}

bool Cmd_SetLogBoxLayerOrder(vector<string>& args)
{
    return Common_FuncOfLayerOrder("LogBox", args);
}

//bool Cmd_AddParticleSystem(vector<string>& args)
//{
//    return Common_FuncOfAdd("ParticleSystem", args);
//}
//
//bool Cmd_DelParticleSystem(vector<string>& args)
//{
//    return Common_FuncOfDelete("ParticleSystem", args);
//}

bool Cmd_ShowParticleSystem(vector<string>& args)
{
    if (args.size() < 1){
        cout << "Cmd_ShowParticleSystem(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (size_t i=0; i<args.size(); i++){
        if (CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("ParticleSystem:"+args[i]) == NULL){
            cout << "Cmd_ShowParticleSystem(): can't find ParticleSystem \"" << args[i] << "\"." <<endl;
        }
        else{
            CParticleSystem* __par = static_cast<CParticleSystem*>(CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject("ParticleSystem:"+args[i]));
            
            if (__par->GetEnable())
                cout << "Cmd_ShowParticleSystem(): ParticleSystem \"" << args[i] << "\" has showed." << endl;
            else
                __par->SetEnable(true);
        }
    }

    return true;
}

bool Cmd_HideParticleSystem(vector<string>& args)
{
    if (args.size() < 1){
        cout << "Cmd_HideParticleSystem(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    for (size_t i=0; i<args.size(); i++){
        if (CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(args[i]) == NULL){
            cout << "Cmd_ShowParticleSystem(): can't find ParticleSystem \"" << args[i] << "\"." <<endl;
        }
        else{
            CParticleSystem* __par = static_cast<CParticleSystem*>(
                CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(args[i]));
            
            if (__par->GetEnable())
                cout << "Cmd_ShowParticleSystem(): ParticleSystem \"" << args[i] << "\" has showed." << endl;
            else
                __par->SetEnable(false);
        }
    }

    return true;
}

bool Cmd_SetParticleSystemLayerOrder(vector<string>& args)
{
    return Common_FuncOfLayerOrder("ParticleSystem", args);
}

//bool Cmd_AddFont(vector<string>& args)
//{
//    return Common_FuncOfAdd("Font", args);
//}
//
//bool Cmd_DelFont(vector<string>& args)
//{
//    return Common_FuncOfDelete("Font", args);
//}

//bool Cmd_AddVariable(string name, string val, map<string, string> &var_table)
bool Cmd_AddVariable(vector<string>& args)
{
    if (args.size() != 2){
        cout << "Cmd_AddVariable(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string __name = args[0];
    string __val = args[1];
    __name = "$" + __name;
    
    return CResourceControl::_ResourceManager.AddVariable(__name, __val);
}

bool Cmd_SetVariable(vector<string>& args)
{
    if (args.size() != 2){
        cout << "Cmd_SetVariable(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    string __name = args[0];
    string __val = args[1];
    __name = "$" + __name;
    
    return CResourceControl::_ResourceManager.SetVariable(__name, __val);
}

bool Cmd_DelVariable(vector<string>& args)
{
    if (args.size() < 1){
        cout << "Cmd_DelVariable(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    for (size_t i=0; i<args.size(); i++){
        CResourceControl::_ResourceManager.DelVariable("$"+args[i]);
    }

    return true;
}

//bool Cmd_AddCamera(vector<string>& args)
//{
//    if (args.size() < 1){
//        cout << "Cmd_AddCamera(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//
//    std::list<pair<string, ENUM_FLAG> > __flags;
//    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));   //name
//    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
//    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
//    __flags.push_back(pair<string, ENUM_FLAG>("-w", FLAG_OPTIONAL));    //width
//    __flags.push_back(pair<string, ENUM_FLAG>("-h", FLAG_OPTIONAL));    //height
//    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_OPTIONAL));    //rotation
//    __flags.push_back(pair<string, ENUM_FLAG>("-z", FLAG_OPTIONAL));    //zoom
//    
//    map<string, vector<string> > __values;
//    if (!Common_ArgsToKV("Cmd_AddCamera", __flags, args, __values))
//        return false;
//
//    
//    for (size_t i=0; i<__values["-n"].size(); i++){
//        string __name = __values["-n"][i];
//        float __x = __values.count("-x") == 0 ? 0.0f : i < __values["-x"].size() ? 
//            atof(__values["-x"][i].c_str()):atof(__values["-x"][__values["-x"].size()-1].c_str());
//        float __y = __values.count("-y") == 0 ? 0.0f : i < __values["-y"].size() ? 
//            atof(__values["-y"][i].c_str()):atof(__values["-y"][__values["-y"].size()-1].c_str());
//        float __w = __values.count("-w") == 0 ? 0.0f : i < __values["-w"].size() ? 
//            atof(__values["-w"][i].c_str()):atof(__values["-w"][__values["-w"].size()-1].c_str());
//        float __h = __values.count("-h") == 0 ? 0.0f : i < __values["-h"].size() ? 
//            atof(__values["-h"][i].c_str()):atof(__values["-h"][__values["-h"].size()-1].c_str());
//        float __r = __values.count("-r") == 0 ? 0.0f : i < __values["-r"].size() ? 
//            atof(__values["-r"][i].c_str()):atof(__values["-r"][__values["-r"].size()-1].c_str());
//        float __z = __values.count("-z") == 0 ? 1.0f : i < __values["-z"].size() ? 
//            atof(__values["-z"][i].c_str()):atof(__values["-z"][__values["-z"].size()-1].c_str());
//
//        CResourceControl::_ResourceManager._CameraControl.AddCamera(__name);
//    }
//    return true;
//}
//
//bool Cmd_DelCamera(vector<string>& args)
//{
//    if (args.size() < 1){
//        cout << "Cmd_AddCamera(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//
//    for (size_t i=0; i<args.size(); i++){
//        CResourceControl::_ResourceManager._CameraControl.DelCamera(args[i]);
//    }
//
//    return true;
//}

bool Cmd_UseCamera(vector<string>& args)
{
    if (args.size() == 0){
        CResourceControl::_ResourceManager._CameraControl.UseDefaultCamera();
    }
    else{
        return CResourceControl::_ResourceManager._CameraControl.UseCamera(args[0]);
    }
    return true;
}
