/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CResourceControl.h"
#include "../Parser/CParser.h"
#include <ctime>

#ifdef WIN32
    #include <direct.h>
#else
#endif

CResourceControl  CResourceControl::_ResourceManager;

CResourceControl::CResourceControl():_threadOfLoading(&CResourceControl::LoadAsset, this)
{
    _script.reset();
    _fileNameOfScript = "";
    _isNeedCleanAction =
    _isLoadPlayerData =
    _loadingObjCtrlEnable = 
    _drawableObjCtrlEnable = 
    _pauseOfAction = 
    _pauseOfUser = false;
}

bool CResourceControl::CheckOut(Object& json, string colName, string objTypeName)
{
    if (!json.has<Array>(colName))
        return false;

    Array __array = json.get<Array>(colName);
    
    for (size_t i=0; i<__array.size(); i++){
        if (__array.get<Object>(i).get<bool>("isdelete")){
            if (objTypeName == "Font"){
                _ObjectControl.DelObject(__array.get<Object>(i).get<String>("name"));
            }
            else if (objTypeName == "Voice"){
                _SoundControl.DeleteVoice(__array.get<Object>(i).get<String>("name"));
            }
            else if (objTypeName == "Se"){
                _SoundControl.DeleteSE(__array.get<Object>(i).get<String>("name"));
            }
            else if (objTypeName == "Camera"){
                _CameraControl.DelCamera(__array.get<Object>(i).get<String>("name"));
            }
            else if (objTypeName == "Music"){
                _SoundControl.DelBgm(__array.get<Object>(i).get<String>("name"));
            }
            else if (objTypeName == "Text"){
                _DrawableObjectControl.DelDrawableObject(__array.get<Object>(i).get<String>("name"));
            }
            else{
                _DrawableObjectControl.DelDrawableObject(__array.get<Object>(i).get<String>("name"));
            }
        }
    }

    return true;
}

//
// result: 
//      1: normal
//      0: column is 0
//      -1: can't find column
//      -2: failed to create asset
//
char CResourceControl::CheckIn(Object& json, string colName, string objTypeName)
{
    if (!json.has<Array>(colName))
        return -1;

    Array& __array = json.get<Array>(colName);

    if (objTypeName == "Script"){
        if (!AddScript(colName, __array))
            return -2;
    }
    else{
        string __path;
        for (size_t i=0; i<__array.size(); i++){
            __path = __array.get<Object>(i).get<String>("path");
            string& __assetName = __array.get<Object>(i).get<String>("name");

            cout << "CResourceControl::CheckIn():Loading '" << __assetName << "':'" << __path << "'" << endl;

            if (objTypeName == "Font"){
                if (!_ObjectControl.AddObject(__assetName,
                    objTypeName,
                    __path))
                    continue;
            
                __assetName = objTypeName + ":" + __assetName;
            }
            else if (objTypeName == "Voice"){
                if (_SoundControl.AddVoice(__assetName,
                    __path) != 0)
                    continue;
            }
            else if (objTypeName == "Se"){
                if (_SoundControl.AddSE(__assetName,
                    __path) != 0)
                    continue;
            }
            else if (objTypeName == "Camera"){
                if (!_CameraControl.AddCamera(__assetName,
                    __path)){
                    _CameraControl.ResetCamera(__assetName);
                    continue;
                }
            }
            else if (objTypeName == "EffctImg"){
                objTypeName = "Img";
                if (!_LoadingObjectControl.AddDrawableObject(
                    __assetName, 
                    objTypeName, 
                    __path)){
                    _LoadingObjectControl.ResetDrawableObject(__assetName, objTypeName);
                    continue;
                }

                __assetName = objTypeName + ":" + __assetName;
            }
            else if (objTypeName == "Music"){
                if (!_SoundControl.AddBgm(
                    __assetName, 
                    __path))
                    continue;
            }
            else if (objTypeName == "Text"){
                if (!_DrawableObjectControl.AddDrawableObject(
                    __assetName, 
                    objTypeName, 
                    __path)){
                    _DrawableObjectControl.ResetDrawableObject(__assetName, objTypeName);
                    continue;
                }

                __assetName = objTypeName + ":" + __assetName;
            }
            else{
                if (!_DrawableObjectControl.AddDrawableObject(
                    __assetName, 
                    objTypeName, 
                    __path)){
                    _DrawableObjectControl.ResetDrawableObject(__assetName, objTypeName);
                    continue;
                }

                __assetName = objTypeName + ":" + __assetName;

                if (objTypeName == "MessageBox"){
                    CMessageBox* __msg = static_cast<CMessageBox*>(_DrawableObjectControl.GetDrawableObject(__assetName));
                    __msg->SetControl(&_pauseOfUser);
                }
            }
        }
    }

    if (__array.size() < 1)
        return 0;

    return 1;
}

bool CResourceControl::OnInit(string filename, sf::RenderWindow* Window)
{
    if (!_CameraControl.OnInit(Window))
        return false;

    if (!_SoundControl.OnInit())
        return false;
    
    _DrawableObjectControl.AddDrawableObject("screen","ScrEffect","");
    _LoadingObjectControl.AddDrawableObject("screen","ScrEffect","");

    if (!LoadJson(_gameBaiscAsset, filename))
        return false;
    
    if (CheckIn(_gameBaiscAsset, "image_for_effect", "EffctImg") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "loading_start_script", "Script") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "loading_end_script", "Script") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "font", "Font") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "text", "Text") < 0) return false;
    if (CheckIn(_gameBaiscAsset, "se", "Se") < 0) return false;
    if (CheckIn(_gameBaiscAsset, "messagebox", "MessageBox") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "button", "Button") < 0) return false;
    if (CheckIn(_gameBaiscAsset, "camera", "Camera") < 0) return false;

    return LoadScript(_gameBaiscAsset.get<String>("main_script"));
}
        
bool CResourceControl::JsonProcess(Object& src, Object& des, string colName)
{
    if (src.has<Array>(colName)){
        Array __array = src.get<Array>(colName);
        Array __arrayResult;

        if (colName == "text"){
            for (size_t i=0; i<__array.size(); i++){
                if (__array.get<Object>(i).has<String>("name")
                    &&
                    __array.get<Object>(i).has<String>("font")){

                    Object __obj;
                    __obj << "name" << __array.get<Object>(i).get<String>("name");
                    __obj << "path" << __array.get<Object>(i).get<String>("font");
                    __obj << "isdelete" << true;
                    __arrayResult << __obj;
                }
            }
        }
        else{
            for (size_t i=0; i<__array.size(); i++){
                Object __obj;
                __obj << "name" << CTextFunction::GetNameInFilename(__array.get<String>(i));
                __obj << "path" << __array.get<String>(i);
                __obj << "isdelete" << true;
                __arrayResult << __obj;
            }
        }

        des << colName << __arrayResult;
        return true;
    }

    return false;
}

bool CResourceControl::LoadJson(Object& obj, string filename)
{
    Object __json;

    if (!__json.parse(Cio::LoadTxtFile(filename))){
        cout << "sysntax error: " << filename << endl;
        return false;
    }

    JsonProcess(__json, obj, "font");
    JsonProcess(__json, obj, "se");
    JsonProcess(__json, obj, "image_for_effect");
    JsonProcess(__json, obj, "messagebox");
    JsonProcess(__json, obj, "button");
    JsonProcess(__json, obj, "camera");
    JsonProcess(__json, obj, "character");
    JsonProcess(__json, obj, "img");
    JsonProcess(__json, obj, "voice");
    JsonProcess(__json, obj, "music");
    JsonProcess(__json, obj, "text");

    if (__json.has<String>("main_script"))
        obj << "main_script" << __json.get<String>("main_script");

    if (__json.has<Array>("script"))
        obj << "script" << __json.get<Array>("script");

    if (__json.has<Array>("loading_start_script"))
        obj << "loading_start_script" << __json.get<Array>("loading_start_script");

    if (__json.has<Array>("loading_end_script"))
        obj << "loading_end_script" << __json.get<Array>("loading_end_script");
    
    return true;
}

void CResourceControl::BeginLoadProcess()
{
    _threadOfLoading.launch();
}

void CResourceControl::EndLoadProcess()
{
    _loadingObjCtrlEnable = false;
    CParser::_Parser.Continue();
}

void CResourceControl::Compare(Object& src, Object& des, string colName)
{
    if (src.has<Array>(colName) && des.has<Array>(colName)){
        for (size_t i=0; i < src.get<Array>(colName).size(); i++){
            for (size_t j=0; j < des.get<Array>(colName).size(); j++){
                if (src.get<Array>(colName).get<Object>(i).get<String>("path")
                    == 
                    des.get<Array>(colName).get<Object>(j).get<String>("path")){
                    
                    bool& __isDelete = des.get<Array>(colName).get<Object>(j).get<bool>("isdelete");
                    __isDelete = false;
                }
            }
        }
    }
}

void CResourceControl::LoadAsset()
{
    CParser::_Parser.Pause();
    _drawableObjCtrlEnable = false;

    Object __obj;
    if (LoadJson(__obj, _fileNameOfScript)){
        if (!_script.empty()){
            Compare(__obj, _script, "character");
            Compare(__obj, _script, "img");
            Compare(__obj, _script, "button");
            Compare(__obj, _script, "se");
            Compare(__obj, _script, "voice");
            Compare(__obj, _script, "camera");
            Compare(__obj, _script, "music");
            
            CheckOut(_script, "text", "Text");
            CheckOut(_script, "character","CharacterLayer");
            CheckOut(_script, "img","Img");
            CheckOut(_script, "button","Button");
            CheckOut(_script, "se", "Se");
            CheckOut(_script, "voice", "Voice");
            CheckOut(_script, "camera", "Camera");
            CheckOut(_script, "music", "Music");
            _script.reset();
        }
        
        _script = __obj;
        _script << "filename" << _fileNameOfScript;

        CheckIn(_script, "text", "Text");
        CheckIn(_script, "character","CharacterLayer");
        CheckIn(_script, "img","Img");
        CheckIn(_script, "button","Button");
        CheckIn(_script, "se", "Se");
        CheckIn(_script, "voice", "Voice");
        CheckIn(_script, "camera", "Camera");
        CheckIn(_script, "music", "Music");
        
         Array& __array = _gameBaiscAsset.get<Array>("messagebox");
         for (size_t i=0; i<__array.size(); i++){
             CMessageBox* __msgbox = static_cast<CMessageBox*>(_DrawableObjectControl.GetDrawableObject(__array.get<Object>(i).get<String>("name")));
             if (__msgbox){
                 __msgbox->ClearText();
             }
         }

        if (_script.has<Array>("script")){
            CParser::_Parser.Reset();
            CParser::_Parser.InsertCmd(_script.get<Array>("script"));
        }
    }

    CSequenceOfAction* __seq = new CSequenceOfAction();

    if (_isLoadPlayerData){
        _isLoadPlayerData = false;
        LoadPlayerDataProcess();
    }
    
    _drawableObjCtrlEnable = true;
    __seq->AddAction(static_cast<CSequenceOfAction*>(_scriptList["loading_end_script"]->Copy()));
    __seq->AddAction(new CClassFuncOfAction<CResourceControl>(this, &CResourceControl::EndLoadProcess));
    _ActionControl.AddAction(__seq);
}
        
void CResourceControl::LoadScript(vector<string> args)
{
    if (args.size() > 0){
        _fileNameOfScript = args[0];
        _isNeedCleanAction = true;
    }
}

bool CResourceControl::LoadScript(string filename)
{
    _fileNameOfScript = filename;

    CSequenceOfAction* __seq = NULL;
    _loadingObjCtrlEnable = true;
    __seq = static_cast<CSequenceOfAction*>(_scriptList["loading_start_script"]->Copy());

    if (__seq){
        _SoundControl.StopBgm();
        _SoundControl.StopSE();
        _SoundControl.StopVoice();
        _ActionControl.OnCleanup();
        __seq->AddAction(new CClassFuncOfAction<CResourceControl>(this, &CResourceControl::BeginLoadProcess));
        _ActionControl.AddAction(__seq);

        return true;
    }
    else
        return false;
}

void CResourceControl::OnLoop()
{
    _ActionControl.OnLoop();
    if (_isNeedCleanAction) {
        _isNeedCleanAction = false;
        LoadScript(_fileNameOfScript);
    }
    _pauseOfAction = _ActionControl.IsPause();
    
    _CameraControl.OnLoop();
    _SoundControl.OnLoop();

    if (_drawableObjCtrlEnable)
        _DrawableObjectControl.OnLoop();

    if (_loadingObjCtrlEnable){
        _LoadingObjectControl.OnLoop();
        return;
    }
    
    if (_pauseOfAction || _pauseOfUser)
        return;

    CParser::_Parser.OnLoop();
}

void CResourceControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (_drawableObjCtrlEnable)
        _DrawableObjectControl.OnRender(Surf_Dest);
    
    if (_loadingObjCtrlEnable)
        _LoadingObjectControl.OnRender(Surf_Dest);
}

void CResourceControl::OnCleanup()
{
    CScript::OnCleanup();
    _SoundControl.OnCleanup();
    _DrawableObjectControl.OnCleanup();
    _LoadingObjectControl.OnCleanup();
    _ObjectControl.OnCleanup();
    _CameraControl.OnCleanup();
    _ActionControl.OnCleanup();
}

bool CResourceControl::OnSaveData(int index) const
{
    cout << "CResourceControl::OnSaveData(): saving..." <<endl;
    Object __json;
    __json << "script" << _fileNameOfScript;

    {
        char __strTime[20];
        time_t __time = time(NULL);
        strftime(__strTime, sizeof(__strTime),"%y-%m-%d %H:%M", localtime(&__time));
        __json << "date_time" << __strTime;
    }

    {
        Object __usrVar;
        for (map<string, string>::const_iterator it=_userVariableList.begin();it!=_userVariableList.end();it++)
            __usrVar << (*it).first << (*it).second;
        
        __json << "user_variable" << __usrVar;
    }

    _DrawableObjectControl.OnSaveData(__json);
    _SoundControl.OnSaveData(__json);
    _CameraControl.OnSaveData(__json);
    CParser::_Parser.OnSaveData(__json);

    char __path[260];
    sprintf(__path, "./savedata/%d.sav", index);
    ofstream __savefile(__path, ofstream::binary|ofstream::out);

    if(!__savefile.is_open()){
#ifdef WIN32
        if (mkdir("./savedata") == 0){
            __savefile.open(__path, ofstream::binary|ofstream::out);
            if(!__savefile.is_open())
                cout << "CResourceControl::OnSaveData(): failed to save." <<endl;
                return false;
        }
        else{
            cout << "CResourceControl::OnSaveData(): failed to create directory 'savedata'." <<endl;
            return false;
        }
#else
    
#endif
    }

    __savefile << __json.json();
    __savefile.close();
    cout << "CResourceControl::OnSaveData(): saved." <<endl;
    return true;
}

void CResourceControl::LoadPlayerDataProcess()
{
    _CameraControl.OnLoadData(_playerData);
    _DrawableObjectControl.OnLoadData(_playerData);
    _SoundControl.OnLoadData(_playerData);
    CParser::_Parser.OnLoadData(_playerData);

    {
        map<std::string, Value*> __usrvar = _playerData.get<Object>("user_variable").kv_map();
        _userVariableList.clear();
        for (map<std::string, Value*>::const_iterator it=__usrvar.begin();it!=__usrvar.end();it++){
            _userVariableList[(*it).first] = (*it).second->is<String>();
        }
    }

    cout << "CResourceControl::OnLoadData(): loaded." <<endl;
}

bool CResourceControl::OnLoadData(int index)
{
    cout << "CResourceControl::OnLoadData(): loading..." <<endl;
    char __path[260];
    sprintf(__path, "./savedata/%d.sav", index);

    _playerData.reset();
    if (_playerData.parse(Cio::LoadTxtFile(__path))){
        if (!_playerData.has<String>("script"))
            return false;
        
        _isLoadPlayerData = true;
        LoadScript(_playerData.get<String>("script"));
        return true;
    }
        
    cout << "CResourceControl::OnLoadData(): failed to load." <<endl;
    return false;
}

bool CResourceControl::AddVariable(string name, string val)
{
    if(_userVariableList.count("$"+name) > 0)
        return false;

    _userVariableList["$"+name] = val;
    return true;
}

bool CResourceControl::SetVariable(string name, string val)
{
    if(_userVariableList.count("$"+name) > 0){
        _userVariableList["$"+name] = val;
        return true;
    }

    return false;
}

string CResourceControl::GetVariable(string name)
{
    if(_userVariableList.count(name) > 0){
        return _userVariableList[name];
    }

    return name;
}

bool CResourceControl::DelVariable(string name)
{
    if(_userVariableList.count("$"+name) > 0){
        _userVariableList.erase("$"+name);
        return true;
    }

    return false;
}

void CResourceControl::PauseForUserConfrim()
{
    _pauseOfUser = true;
}