/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CResourceControl.h"
#include "../Parser/CParser.h"

CResourceControl  CResourceControl::_ResourceManager;

CResourceControl::CResourceControl():_threadOfLoading(&CResourceControl::LoadAsset, this)
{
    _effectObjCtrlEnable = _drawableObjCtrlEnable = false;
    _script.reset();
    _fileNameOfScript = "";
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
                    return -2;
            
                __assetName = objTypeName + ":" + __assetName;
            }
            else if (objTypeName == "Voice"){
                if (_SoundControl.AddVoice(__assetName,
                    __path) != 0)
                    return -2;
            }
            else if (objTypeName == "Se"){
                if (_SoundControl.AddSE(__assetName,
                    __path) != 0)
                    return -2;
            }
            else if (objTypeName == "Camera"){
                if (!_CameraControl.AddCamera(__assetName,
                    __path))
                    return -2;
            }
            else if (objTypeName == "EffctImg"){
                objTypeName = "Img";
                if (!_EffectObjectControl.AddDrawableObject(
                    __assetName, 
                    objTypeName, 
                    __path))
                    return -2;

                __assetName = objTypeName + ":" + __assetName;
            }
            else if (objTypeName == "Music"){
                if (!_SoundControl.AddBgm(
                    __assetName, 
                    __path))
                    return -2;
            }
            else if (objTypeName == "Text"){
                if (!_DrawableObjectControl.AddDrawableObject(
                    __assetName, 
                    objTypeName, 
                    __path))
                    return -2;

                __assetName = objTypeName + ":" + __assetName;
            }
            else{
                if (!_DrawableObjectControl.AddDrawableObject(
                    __assetName, 
                    objTypeName, 
                    __path))
                    return -2;

                __assetName = objTypeName + ":" + __assetName;

                if (objTypeName == "MessageBox"){
                    CMessageBox* __msg = static_cast<CMessageBox*>(_DrawableObjectControl.GetDrawableObject(__assetName));
                    __msg->SetControl(&_pause);
                }
            }
        }
    }

    if (__array.size() < 1)
        return 0;

    return 1;
}

bool CResourceControl::OnInit(string filename)
{
    if (!_renderTextureUp.create(CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT))
        return false;

    if (!_renderTextureDown.create(CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT))
        return false;

    if (!_CameraControl.OnInit(&_renderTextureDown))
        return false;

    if (!_SoundControl.OnInit())
        return false;
    
    _DrawableObjectControl.AddDrawableObject("screen","ScrEffect","");

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

    if (!__json.parse(Cio::LoadTxtFile(filename)))
        return false;

    JsonProcess(__json, obj, "font");
    JsonProcess(__json, obj, "se");
    JsonProcess(__json, obj, "image_for_effect");
    JsonProcess(__json, obj, "messagebox");
    JsonProcess(__json, obj, "button");
    JsonProcess(__json, obj, "camera");
    JsonProcess(__json, obj, "character");
    JsonProcess(__json, obj, "background");
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
    _effectObjCtrlEnable = false;
}

void CResourceControl::Compare(Object& src, Object& des, string colName)
{
    if (src.has<Array>(colName) && des.has<Array>(colName)){
        for (size_t i=0; i < src.get<Array>(colName).size(); i++){
            for (size_t j=0; j < des.get<Array>(colName).size(); j++){
                if (src.get<Array>(colName).get<Object>(i).get<String>("name")
                    == 
                    des.get<Array>(colName).get<Object>(j).get<String>("name")){
                    
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
            Compare(__obj, _script, "background");
            Compare(__obj, _script, "img");
            Compare(__obj, _script, "button");
            Compare(__obj, _script, "se");
            Compare(__obj, _script, "voice");
            Compare(__obj, _script, "camera");
            Compare(__obj, _script, "music");
            
            CheckOut(_script, "text", "Text");
            CheckOut(_script, "character","CharacterLayer");
            CheckOut(_script, "background","Background");
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
        CheckIn(_script, "background","Background");
        CheckIn(_script, "img","Img");
        CheckIn(_script, "button","Button");
        CheckIn(_script, "se", "Se");
        CheckIn(_script, "voice", "Voice");
        CheckIn(_script, "camera", "Camera");
        CheckIn(_script, "music", "Music");

        if (_script.has<Array>("script")){
            CParser::_Parser.InsertCmd(_script.get<Array>("script"));
        }
    }

    CSequenceOfAction* __seq = new CSequenceOfAction();
    *__seq = _scriptList["loading_end_script"];
    __seq->AddAction(new CClassFuncOfAction<CResourceControl>(this, &CResourceControl::EndLoadProcess));
    _ActionControl.AddAction(__seq);
    
    _drawableObjCtrlEnable = true;
    CParser::_Parser.Continue();
}

bool CResourceControl::LoadScript(string filename)
{
    _fileNameOfScript = filename;

    CSequenceOfAction* __seq = new CSequenceOfAction();
    _effectObjCtrlEnable = true;
    *__seq = _scriptList["loading_start_script"];
    __seq->AddAction(new CClassFuncOfAction<CResourceControl>(this, &CResourceControl::BeginLoadProcess));
    _ActionControl.AddAction(__seq);

    return true;
}

void CResourceControl::OnLoop()
{
    _ActionControl.OnLoop();
    _pause = _ActionControl.IsPause();

    if (_drawableObjCtrlEnable)
        _DrawableObjectControl.OnLoop();

    if (_effectObjCtrlEnable)
        _EffectObjectControl.OnLoop();
    
    _CameraControl.OnLoop();
    _SoundControl.OnLoop();
    
    if (!_pause)
        CParser::_Parser.OnLoop();
}

void CResourceControl::OnRender(sf::RenderTarget* Surf_Dest)
{
    //sf::Clock _c;
    //_c.restart();
    _renderTextureDown.clear();
    _renderTextureUp.clear(sf::Color(0,0,0,0));

    if (_drawableObjCtrlEnable)
        _DrawableObjectControl.OnRender(&_renderTextureDown, &_renderTextureUp);
    
    if (_effectObjCtrlEnable)
        _EffectObjectControl.OnRender(&_renderTextureDown, &_renderTextureUp);
    
    _renderTextureDown.display();
    _renderTextureUp.display();

    _spriteDown.setTexture(_renderTextureDown.getTexture());
    _spriteUp.setTexture(_renderTextureUp.getTexture());

    Surf_Dest->draw(_spriteDown);
    Surf_Dest->draw(_spriteUp);
    //cout<< _c.getElapsedTime().asMicroseconds()<<endl;
}

void CResourceControl::OnCleanup()
{
    _DrawableObjectControl.OnCleanup();
    _EffectObjectControl.OnCleanup();
}

void CResourceControl::OnSaveData()
{
    //ofstream __savefile("./userdata/1.txt");
    //Object __json;
    //__json.reset();

    //if(!__savefile){
    //    cout << "error" << endl;
    //    return;
    //}

    //for (size_t i=0; i<_drawableObjectList.size(); i++){
    //    cout << "_(:3J Z)_" <<endl;
    //    __savefile << "name=" << _drawableObjectList[i].first <<endl;
    //    _drawableObjectList[i].second->OnSaveData(__json);
    //    cout << "(:3[____]" <<endl;
    //}

    //__savefile.close();
}

void CResourceControl::OnLoadData()
{

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
