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
#include "../Common/CClassFuncArgsOfAction.h"

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

bool Common_FuncOfShow(string objTypeName, vector<string>& args, CActionSet* act)
{ 
    string __funcName = "Cmd_Show" + objTypeName;

    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

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
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //reset

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
        
        act->AddAction(__obj->CreateActionOfAlphaTo(__inte, __alpha, __reset, __pause));
        __obj->SetPosition(*__x, *__y);
        return true;
    }
    else
        cout << __funcName << "(): can't find "<< objTypeName <<" \""<< __name << "\"." <<endl;

    return false;
}

bool Common_FuncOfHide(string objTypeName, vector<string>& args, CActionSet* act)
{ 
    string __funcName = "Cmd_Hide" + objTypeName;

    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
    
    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //interval
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //reset

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
        act->AddAction(__obj->CreateActionOfAlphaTo(__inte, 0, __reset, __pause));
        return true;
    }
    return false;
}

bool Common_FuncOfMove(string objTypeName, vector<string>& args, CActionSet* act)
{ 
    string __funcName = "Cmd_Move" + objTypeName;
    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-b", FLAG_NONPARAMETRIC)); 
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //reset

    map<string, vector<string> > __values;
    if (!Common_ArgsToKV(__funcName.c_str(), __flags, args, __values))
        return false;

    if (__values.count("-n") == 0)
        return false;
    
    bool __isBy = __values.count("-b") == 0 ? false : true;
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

    if (__flag == 0){
        cout << __funcName << "(): can't find x,y." <<endl;
        return false;
    }
    
    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(__name);//Camera
    }
    else{
        __obj = 
            CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+__name);
    }

    if (__obj != NULL){
        switch (__flag)
        {
            case 1:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfMoveXBy(__inte, __x, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfMoveXTo(__inte, __x, __reset, __pause));
            break;
            case 2:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfMoveYBy(__inte, __y, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfMoveYTo(__inte, __y, __reset, __pause));
            break;
            case 3:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfMoveBy(__inte, __x, __y, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfMoveTo(__inte, __x, __y, __reset, __pause));
            break;
        }
        return true;
    }

    return false;
}

bool Common_FuncOfOrigin(string objTypeName, vector<string>& args, CActionSet* act)
{ 
    string __funcName = "Cmd_Origin" + objTypeName;
    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-b", FLAG_NONPARAMETRIC)); 
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
    __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //reset

    map<string, vector<string> > __values;
    if (!Common_ArgsToKV(__funcName.c_str(), __flags, args, __values))
        return false;

    if (__values.count("-n") == 0)
        return false;
    
    bool __isBy = __values.count("-b") == 0 ? false : true;
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

    if (__flag == 0){
        cout << __funcName << "(): can't find x,y." <<endl;
        return false;
    }
    
    CImageBaseClass* __obj = NULL;

    __obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+__name);

    if (__obj != NULL){
        switch (__flag)
        {
            case 1:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfOriginXBy(__inte, __x, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfOriginXTo(__inte, __x, __reset, __pause));
            break;
            case 2:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfOriginYBy(__inte, __y, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfOriginYTo(__inte, __y, __reset, __pause));
            break;
            case 3:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfOriginBy(__inte, __x, __y, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfOriginTo(__inte, __x, __y, __reset, __pause));
            break;
        }
        return true;
    }

    return false;
}

bool Common_FuncOfRotation(string objTypeName, vector<string>& args, CActionSet* act)
{
    string __funcName = "Cmd_Rotation" + objTypeName;
    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-b", FLAG_OPTIONAL));
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause
    __flags.push_back(pair<string, ENUM_FLAG>("-v", FLAG_NECESSITY));    //Rotation
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //reset
    
    map<string, vector<string> > __values;
    if (!Common_ArgsToKV(__funcName.c_str(), __flags, args, __values))
        return false;

    if (__values.count("-n") == 0)
        return false;
    
    string __name = __values["-n"][0];
    bool __isBy = __values.count("-b") == 0 ? false : true;
    bool __pause = __values.count("-p") == 0 ? false : true;
    bool __reset = __values.count("-r") == 0 ? false : true;
    float __rotation = atof(__values["-v"][0].c_str());
    size_t __inte = __values.count("-i") == 0 ? 
        CCommon::_Common.INTERVAL : atoi(__values["-i"][0].c_str());
    
    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(objTypeName+":"+__name);//Camera
    }
    else{
        __obj = 
            CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+__name);
    }

    if (__obj != NULL){
        if (__isBy)
            act->AddAction(__obj->CreateActionOfRotationBy(__inte,__rotation,__reset,__pause));
        else
            act->AddAction(__obj->CreateActionOfRotationTo(__inte,__rotation,__reset,__pause));
        return true;
    }
    return false;
}

bool Common_FuncOfScale(string objTypeName, vector<string>& args, CActionSet* act)
{ 
    string __funcName = "Cmd_Scale" + objTypeName;
    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    std::list<pair<string, ENUM_FLAG> > __flags;
    __flags.push_back(pair<string, ENUM_FLAG>("-b", FLAG_OPTIONAL));
    __flags.push_back(pair<string, ENUM_FLAG>("-i", FLAG_OPTIONAL));    //incr
    __flags.push_back(pair<string, ENUM_FLAG>("-n", FLAG_NECESSITY));    //name
    __flags.push_back(pair<string, ENUM_FLAG>("-p", FLAG_NONPARAMETRIC));    //pause

    if (objTypeName == "Camera"){
        __flags.push_back(pair<string, ENUM_FLAG>("-z", FLAG_NECESSITY));
    }
    else{
        __flags.push_back(pair<string, ENUM_FLAG>("-x", FLAG_OPTIONAL));    //x
        __flags.push_back(pair<string, ENUM_FLAG>("-y", FLAG_OPTIONAL));    //y
    }
    __flags.push_back(pair<string, ENUM_FLAG>("-r", FLAG_NONPARAMETRIC));    //reset

    map<string, vector<string> > __values;
    if (!Common_ArgsToKV(__funcName.c_str(), __flags, args, __values))
        return false;

    if (__values.count("-n") == 0)
        return false;
    
    bool __isBy = __values.count("-b") == 0 ? false : true;
    bool __pause = __values.count("-p") == 0 ? false : true;
    bool __reset = __values.count("-r") == 0 ? false : true;
    string __name = __values["-n"][0];
    float __x = 0;
    float __y = 0;
    char __flag = 0;
    size_t __inte = __values.count("-i") == 0 ? 
        CCommon::_Common.INTERVAL : atoi(__values["-i"][0].c_str());
    
    if (objTypeName == "Camera"){
        __x = atof(__values["-z"][0].c_str());
        __flag |= 0x1;
    }
    else{
        if (__values.count("-x") > 0){
            __x = atof(__values["-x"][0].c_str());
            __flag |= 0x1;
        }

        if (__values.count("-y") > 0){
            __y = atof(__values["-y"][0].c_str());
            __flag |= 0x2;
        }
        
        if (__flag == 0){
            cout << __funcName << "(): can't find x,y." <<endl;
            return false;
        }
    }

    CBaiscProperties* __obj = NULL;

    if (objTypeName == "Camera"){
        __obj = CResourceControl::_ResourceManager._CameraControl.GetCamera(objTypeName+":"+__name);//Camera
    }
    else{
        __obj = 
            CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+__name);
    }

    if (__obj != NULL){
        switch (__flag)
        {
            case 1:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfScaleXBy(__inte, __x, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfScaleXTo(__inte, __x, __reset, __pause));
            break;
            case 2:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfScaleYBy(__inte, __y, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfScaleYTo(__inte, __y, __reset, __pause));
            break;
            case 3:
                if (__isBy)
                    act->AddAction(__obj->CreateActionOfScaleBy(__inte, __x, __y, __reset, __pause));
                else
                    act->AddAction(__obj->CreateActionOfScaleTo(__inte, __x, __y, __reset, __pause));
            break;
        }
        return true;
    }

    return false;
}

bool Common_FuncOfLayerOrder(string objTypeName, vector<string>& args, CActionSet* act)
{ 
    string __funcName = "Cmd_SetLayerOrder" + objTypeName;
    
    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

    if (args.size() < 2){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }
   
    CImageBaseClass* __obj = NULL;
    __obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+args[0]);

    if (__obj){
        vector<string> __args;
        __args.push_back(args[1]);
        act->AddAction(new CClassFunArgscOfAction<CImageBaseClass>(__obj, &CImageBaseClass::SetLayerOrder, __args));

        return true;
    }
    else
        cout << __funcName <<"(): " << objTypeName << " \""<< args[0] << "\" has no existed." <<endl;

    return true;
}

bool Common_FuncOfFlip(string objTypeName, vector<string>& args, CActionSet* act, bool flipx = true)
{
    string __funcName = "Cmd_Flip" + flipx ? "X" : "Y" + objTypeName;
    
    if (act == NULL){
        cout << __funcName << "(): Action Set is null." <<endl;
        return false;
    }

    if (args.size() < 1){
        cout << __funcName << "(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    CImageBaseClass* __obj = NULL;
    __obj = CResourceControl::_ResourceManager._DrawableObjectControl.GetDrawableObject(objTypeName+":"+args[0]);

    if (__obj){
        if (flipx)
            act->AddAction(new CClassFuncOfAction<CImageBaseClass>(__obj, &CImageBaseClass::FlipX));
        else
            act->AddAction(new CClassFuncOfAction<CImageBaseClass>(__obj, &CImageBaseClass::FlipY));

        return true;
    }

    return false;
}

/*==============================================================
    commad of script
===============================================================*/

//bool Cmd_AddPosition(vector<string>& args, CActionSet* act)
//{
//    if (args.size() != 3){
//        cout << "Cmd_AddPosition(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//
//    string name = args[0];
//    float x = atof(args[1].c_str());
//    float y = atof(args[2].c_str());
//    CResourceControl::_ResourceManager._PositionControl.AddPosition(name, x, y);
//    return true;
//}
//
//bool Cmd_DelPosition(vector<string>& args, CActionSet* act)
//{
//    if (args.size() < 1){
//        cout << "Cmd_DelPosition(): command invaild. can't set " << args.size()
//            << " argument(s) in the command." <<endl;
//        return false;
//    }
//
//    for (size_t i=0; i<args.size(); i++){
//        CResourceControl::_ResourceManager._PositionControl.DelPosition(args[i]);
//    }
//
//    return true;
//}

//===========================================
//
//===========================================

bool Cmd_ShowCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfShow("CharacterLayer", args, act);
}

bool Cmd_MoveCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfMove("CharacterLayer", args, act);
}

bool Cmd_ScaleCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfScale("CharacterLayer", args, act);
}

bool Cmd_RotationCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfRotation("CharacterLayer", args, act);
}

bool Cmd_HideCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfHide("CharacterLayer", args, act);
}

bool Cmd_SetFaceCharacterLayer(vector<string>& args, CActionSet* act)
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

bool Cmd_SetCharacterLayerOrder(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfLayerOrder("CharacterLayer", args, act);
}

bool Cmd_FlipXCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("CharacterLayer", args, act);
}

bool Cmd_FlipYCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("CharacterLayer", args, act, false);
}

bool Cmd_OriginCharacterLayer(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfOrigin("CharacterLayer", args, act);
}

//===========================================
//
//===========================================

bool Cmd_ShowBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfShow("Background", args, act);
}

//bool Cmd_DelBackground(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfDelete("Background", args);
//}

bool Cmd_HideBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfHide("Background", args, act);
}

bool Cmd_MoveBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfMove("Background", args, act);
}

bool Cmd_ScaleBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfScale("Background", args, act);
}

bool Cmd_RotationBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfRotation("Background", args, act);
}

bool Cmd_SetBackgroundLayerOrder(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfLayerOrder("Background", args, act);
}

bool Cmd_FlipXBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("Background", args, act);
}

bool Cmd_FlipYBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("Background", args, act, false);
}

bool Cmd_OriginBackground(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfOrigin("Background", args, act);
}
/*
    Cmd_AddImg: comand of add image.
    args[0]: set image name.
    args[1]: set image path.
    args[2]: set image postion of x.
    args[3]: set image postion of y.
*/
//bool Cmd_AddImg(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfAdd("Img", args);
//}

bool Cmd_ShowImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfShow("Img", args, act);
}

bool Cmd_HideImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfHide("Img", args, act);
}

bool Cmd_MoveImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfMove("Img", args, act);
}

bool Cmd_ScaleImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfScale("Img", args, act);
}

bool Cmd_RotationImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfRotation("Img", args, act);
}

bool Cmd_SetImgLayerOrder(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfLayerOrder("Img", args, act);
}

bool Cmd_FlipXImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("Img", args, act);
}

bool Cmd_FlipYImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("Img", args, act, false);
}

bool Cmd_OriginImg(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfOrigin("Img", args, act);
}

bool Cmd_PlayBGM(vector<string>& args, CActionSet* act)
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

bool Cmd_PauseBGM(vector<string>& args, CActionSet* act)
{
    if (CResourceControl::_ResourceManager._SoundControl.GetBgmStatus() == sf::Music::Playing)
        CResourceControl::_ResourceManager._SoundControl.PauseBgm();

    return true;
}

bool Cmd_ResumeBGM(vector<string>& args, CActionSet* act)
{
    if (CResourceControl::_ResourceManager._SoundControl.GetBgmStatus() == sf::Music::Paused)
        CResourceControl::_ResourceManager._SoundControl.PlayBgm();

    return true;
}

//bool Cmd_AddSE(vector<string>& args, CActionSet* act)
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
//bool Cmd_DelSE(vector<string>& args, CActionSet* act)
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

bool Cmd_PlaySE(vector<string>& args, CActionSet* act)
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

//bool Cmd_AddVoice(vector<string>& args, CActionSet* act)
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
//bool Cmd_DelVoice(vector<string>& args, CActionSet* act)
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

//bool Cmd_AddButton(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfAdd("Button", args);
//}
//
//bool Cmd_DelButton(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfDelete("Button", args);
//}

bool Cmd_ShowButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfShow("Button", args, act);
}

bool Cmd_HideButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfHide("Button", args, act);
}

bool Cmd_MoveButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfMove("Button", args, act);
}

bool Cmd_ScaleButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfScale("Button", args, act);
}

bool Cmd_RotationButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfRotation("Button", args, act);
}

bool Cmd_SetButtonLayerOrder(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfLayerOrder("Button", args, act);
}

bool Cmd_FlipXButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("Button", args, act);
}

bool Cmd_FlipYButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfFlip("Button", args, act, false);
}

bool Cmd_OriginButton(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfOrigin("Button", args, act);
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
bool Cmd_Message(vector<string>& args, CActionSet* act)
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

//bool Cmd_AddMessageBox(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfAdd("MessageBox", args);
//}
//
//bool Cmd_DelMessageBox(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfDelete("MessageBox", args);
//}

bool Cmd_ShowMessageBox(vector<string>& args, CActionSet* act)
{   
    return Common_FuncOfShow("MessageBox", args, act);
}

bool Cmd_HideMessageBox(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfHide("MessageBox", args, act);
}

bool Cmd_SetMessageBoxLayerOrder(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfLayerOrder("MessageBox", args, act);
}

//bool Cmd_AddLogBox(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfAdd("LogBox", args);
//}

bool Cmd_ShowLogBox(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfShow("LogBox", args, act);
}

bool Cmd_HideLogBox(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfHide("LogBox", args, act);
}

//bool Cmd_DelLogBox(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfDelete("LogBox", args);
//}

bool Cmd_SetLogBoxLayerOrder(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfLayerOrder("LogBox", args, act);
}

//bool Cmd_AddParticleSystem(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfAdd("ParticleSystem", args);
//}
//
//bool Cmd_DelParticleSystem(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfDelete("ParticleSystem", args);
//}

bool Cmd_ShowParticleSystem(vector<string>& args, CActionSet* act)
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

bool Cmd_HideParticleSystem(vector<string>& args, CActionSet* act)
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

bool Cmd_SetParticleSystemLayerOrder(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfLayerOrder("ParticleSystem", args, act);
}

//bool Cmd_AddFont(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfAdd("Font", args);
//}
//
//bool Cmd_DelFont(vector<string>& args, CActionSet* act)
//{
//    return Common_FuncOfDelete("Font", args);
//}

//bool Cmd_AddVariable(string name, string val, map<string, string> &var_table)
bool Cmd_AddVariable(vector<string>& args, CActionSet* act)
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

bool Cmd_SetVariable(vector<string>& args, CActionSet* act)
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

bool Cmd_DelVariable(vector<string>& args, CActionSet* act)
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

bool Cmd_DelAction(vector<string>& args, CActionSet* act)
{
    if (args.size() < 1){
        cout << "Cmd_DelVariable(): command invaild. can't set " << args.size()
            << " argument(s) in the command." <<endl;
        return false;
    }

    if (act == NULL){
        cout << "Cmd_DelAction(): Action Set is null." <<endl;
        return false;
    }
    
    for (size_t i=0; i<args.size(); i++){
        act->DeleteAct(args[i]);
    }

    return true;
}

//bool Cmd_AddCamera(vector<string>& args, CActionSet* act)
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
//bool Cmd_DelCamera(vector<string>& args, CActionSet* act)
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

bool Cmd_UseCamera(vector<string>& args, CActionSet* act)
{
    if (args.size() == 0){
        CResourceControl::_ResourceManager._CameraControl.UseDefaultCamera();
    }
    else{
        return CResourceControl::_ResourceManager._CameraControl.UseCamera(args[0]);
    }
    return true;
}

bool Cmd_MoveCamera(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfMove("Camera", args, act);
}

bool Cmd_ScaleCamera(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfScale("Camera", args, act);
}

bool Cmd_RotationCamera(vector<string>& args, CActionSet* act)
{
    return Common_FuncOfRotation("Camera", args, act);
}
