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

//bool sort_cmp(pair<string,CImageBaseClass*> obj1, pair<string,CImageBaseClass*> obj2)
//{
//    return obj1.second->GetLayerOrder() < obj2.second->GetLayerOrder();
//}

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

bool CResourceControl::AddCamera(string name)
{
    if(_cameraList.count(name) > 0)
        return false;
    
    _cameraList[name] = CCamera::Create();
    _cameraList[name]->Reset(0.0f, 0.0f,
        CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT);
    return true;
}

bool CResourceControl::DelCamera(string name)
{
    if(_cameraList.count(name) > 0){
        delete _cameraList[name];
        _cameraList.erase(name);
        return true;
    }

    return false;
}

CCamera* CResourceControl::GetCamera(string name)
{
    if(_cameraList.count(name) > 0){
        return _cameraList[name];
    }
    return NULL;
}

string CResourceControl::GetVariable(string name)
{
    if(_userVariableList.count(name) > 0){
        return _userVariableList[name];
    }

    return "";
}

bool CResourceControl::DelVariable(string name)
{
    if(_userVariableList.count("$"+name) > 0){
        _userVariableList.erase("$"+name);
        return true;
    }

    return false;
}


//bool CResourceControl::AddDrawableObject(string name, CImageBaseClass* obj)
//{
//    if (obj == NULL)
//        return false;
//
//    if (IsExists(name)){
//        delete obj;
//        return false;
//    }
//
//    _drawableObjectList.push_back(make_pair(name, obj));
//    _isNeedSort = true;
//    return true;
//}

bool CResourceControl::CheckIn(Object& json, string name, string objTypeName)
{
    
    if (!json.has<Array>(name))
        return false;

    Array __array = json.get<Array>(name);
    //if (__array.size() < 1)
    //    return false;
    
    for (size_t i=0; i<__array.size(); i++)
        _DrawableObjectControl.AddDrawableObject(
            GetNameInFilename(__array.get<String>(i)), 
            objTypeName, 
            __array.get<String>(i));

    return true;
}

bool CResourceControl::OnInit(string filename)
{
    Object json;
    if (!json.parse(Cio::LoadTxtFile(filename)))
        return false;
    
    if (!json.has<String>("main_script"))
        return false;

    if (!CheckIn(json, "image_for_loading", "Img")) return false;
    if (!CheckIn(json, "image_for_effect", "Img")) return false;
    if (!CheckIn(json, "messagebox", "MessageBox")) return false;

    return LoadScript(json.get<String>("main_script"));
}

bool CResourceControl::LoadScript(string filename)
{
    //Object json;
    string __ObjectTypeName = "";
    if (!_script.empty())
    {

    }

    if (!_script.parse(Cio::LoadTxtFile(filename)))
        return false;

    //    if (objTypeName == "Img") __obj = CImageBaseClass::Create(filename.c_str());
    //else if (objTypeName == "Background") __obj = CImageBaseClass::Create(filename.c_str());
    //else if (objTypeName == "Button") __obj = CButton::Create(filename.c_str());
    //else if (objTypeName == "CharacterLayer") __obj = CCharacterLayer::Create(filename.c_str());
    //else if (objTypeName == "LogBox") __obj = CLogBox::Create(filename.c_str());
    //else if (objTypeName == "MessageBox") __obj = CMessageBox::Create(filename.c_str());
    //else if (objTypeName == "ParticleSystem") __obj = CParticleSystem::Create(filename.c_str());

    CheckIn(_script, "character","CharacterLayer");
    CheckIn(_script, "background","Background");
    CheckIn(_script, "cg","Img");
    CheckIn(_script, "button","Button");
    _script << "filename" << filename;

    if (_script.has<Array>("script")){
        for (size_t i=0; i< _script.get<Array>("script").size(); i++)
            CParser::_Parser.InsertCmd(_script.get<Array>("script").get<String>(i));
    }
    //CheckIn(_script, "ParticleSystem"," ParticleSystem");

    return true;
}


void CResourceControl::OnLoop(bool &pause)
{
    _DrawableObjectControl.OnLoop(pause);
}

void CResourceControl::OnRender(sf::RenderWindow* Surf_Dest)
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
