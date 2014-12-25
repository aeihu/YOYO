/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CResourceControl.h"
#include "../Parser/CParser.h"

CResourceControl  CResourceControl::_ResourceManager;

string CResourceControl::GetNameInFilename(string filename)
{
    size_t __last_x_pos = filename.find_last_of('/');
    size_t __last_s_pos = filename.find_last_of('*');
    __last_x_pos = __last_x_pos == string::npos ? 0 : __last_x_pos;
    __last_s_pos = __last_s_pos == string::npos ? 0 : __last_s_pos;
    string __result = "";

    if (__last_s_pos > __last_x_pos)
        __result = filename.substr(__last_s_pos+1);
    else
        __result = filename.substr(__last_x_pos+1);
    
    size_t __last_p_pos = __result.find_last_of('.');
    if (__last_p_pos != string::npos)
        __result = __result.substr(0, __last_p_pos);

    return __result;
}

bool CResourceControl::CheckOut(Object& json, string colName, string objTypeName)
{
    if (!json.has<Array>(colName))
        return false;

    Array __array = json.get<Array>(colName);
    
    for (size_t i=0; i<__array.size(); i++){
        if (objTypeName == "Font"){
            _ObjectControl.DelObject(__array.get<String>(i));
        }
        else if (objTypeName == "Voice"){
            _SoundControl.DeleteVoice(__array.get<String>(i));
        }
        else if (objTypeName == "Se"){
            _SoundControl.DeleteSE(__array.get<String>(i));
        }
        else if (objTypeName == "Camera"){
            _CameraControl.DelCamera(__array.get<String>(i));
        }
        else{
            _DrawableObjectControl.DelDrawableObject(__array.get<String>(i));
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

    Array __array = json.get<Array>(colName);
    Array __arrayOfAssetName;
    string __assetName = "";
    
    for (size_t i=0; i<__array.size(); i++){
        cout << "CResourceControl::CheckIn():Loading '" << __array.get<String>(i) << "'" << endl;

        __assetName = GetNameInFilename(__array.get<String>(i));
        if (objTypeName == "Font"){
            if (!_ObjectControl.AddObject(__assetName,
                objTypeName,
                __array.get<String>(i)))
                return -2;
        }
        else if (objTypeName == "Voice"){
            if (_SoundControl.AddVoice(__assetName,
                __array.get<String>(i).c_str()) != 0)
                return -2;
        }
        else if (objTypeName == "Se"){
            if (_SoundControl.AddSE(__assetName,
                __array.get<String>(i).c_str()) != 0)
                return -2;
        }
        else if (objTypeName == "Camera"){
            if (!_CameraControl.AddCamera(__assetName,
                __array.get<String>(i).c_str()))
                return -2;
        }
        else{
            if (!_DrawableObjectControl.AddDrawableObject(
                __assetName, 
                objTypeName, 
                __array.get<String>(i)))
                return -2;
        }

        __arrayOfAssetName << objTypeName + ":" + __assetName;
    }

    json << "[" + colName + "]" << __arrayOfAssetName;
    
    if (__array.size() < 1)
        return 0;

    return 1;
}

bool CResourceControl::OnInit(string filename, sf::RenderTarget* display)
{
    if (!_CameraControl.OnInit(display))
        return false;

    if (!_SoundControl.OnInit())
        return false;

    if (!OnInit(filename))
        return false;

    return true;
}

bool CResourceControl::OnInit(string filename)
{
    if (!_gameBaiscAsset.parse(Cio::LoadTxtFile(filename)))
        return false;
    
    if (!_gameBaiscAsset.has<String>("main_script"))
        return false;
    
    if (CheckIn(_gameBaiscAsset, "font", "Font") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "se", "Se") < 0) return false;
    if (CheckIn(_gameBaiscAsset, "image_for_loading", "Img") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "image_for_effect", "Img") < 0) return false;
    if (CheckIn(_gameBaiscAsset, "messagebox", "MessageBox") < 1) return false;
    if (CheckIn(_gameBaiscAsset, "button", "Button") < 0) return false;
    if (CheckIn(_gameBaiscAsset, "camera", "Camera") < 0) return false;

    return LoadScript(_gameBaiscAsset.get<String>("main_script"));
}

void CResourceControl::LoadAsset()
{
    CParser::_Parser.Pause();
    if (!_script.empty()){
        CheckOut(_script, "[character]","CharacterLayer");
        CheckOut(_script, "[background]","Background");
        CheckOut(_script, "[cg]","Img");
        CheckOut(_script, "[button]","Button");
        CheckOut(_script, "[se]", "Se");
        CheckOut(_script, "[voice]", "Voice");
        _script.reset();
    }

    if (_script.parse(Cio::LoadTxtFile(_fileNameOfScript))){
        _script << "filename" << _fileNameOfScript;
        CheckIn(_script, "character","CharacterLayer");
        CheckIn(_script, "background","Background");
        CheckIn(_script, "cg","Img");
        CheckIn(_script, "button","Button");
        CheckIn(_script, "se", "Se");
        CheckIn(_script, "voice", "Voice");
        CheckIn(_script, "camera", "Camera");

        if (_script.has<Array>("script")){
            for (size_t i=0; i< _script.get<Array>("script").size(); i++)
                CParser::_Parser.InsertCmd(_script.get<Array>("script").get<String>(i));
        }
    }
    CParser::_Parser.Continue();
}

bool CResourceControl::LoadScript(string filename)
{
    _fileNameOfScript = filename;
    if (_gameBaiscAsset.has<Array>("[image_for_loading]")){
        Array __imgs = _gameBaiscAsset.get<Array>("[image_for_loading]");
        CImageBaseClass* __img = _DrawableObjectControl.GetDrawableObject(
            __imgs.get<String>(std::rand() % __imgs.size()));

        if (__img != NULL){
            //__img->
        }


        _DrawableObjectControl.Show(
            __imgs.get<String>(std::rand() % __imgs.size()),
            0,0,0,500,true);
    }

    _threadOfLoading.launch();

    return true;
}

void CResourceControl::OnLoop()
{
    bool __pause = false;
    _DrawableObjectControl.OnLoop(__pause);

    _SoundControl.OnLoop();

    if (__pause)
        return;
    
    CParser::_Parser.OnLoop();
}

void CResourceControl::OnRender(sf::RenderTarget* Surf_Dest)
{
    _DrawableObjectControl.OnRender(Surf_Dest);
    //unsigned long l = CCommon::_Common.GetTicks();

    //cout << "time: " << CCommon::_Common.GetTicks()-l <<endl;
}

void CResourceControl::OnCleanup()
{
    _DrawableObjectControl.OnCleanup();
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
