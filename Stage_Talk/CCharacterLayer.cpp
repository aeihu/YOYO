/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCharacterLayer.h"
#include "../Common/CZlib.h"
#include "../Common/Cio.h"

CCharacterLayer::CCharacterLayer(float x, float y):CImageBaseClass(x,y)
{
    _offset.x = 
    _offset.y = 0;
    _isFaceEnable = false;
}

bool CCharacterLayer::Subclass_Loop()
{
    if (_spriteFace.GetColor().a != _Alpha)
        _spriteFace.SetColor(CColor(255,255,255,_Alpha));

    if (_Coordinate+_offset != _spriteFace.GetPosition())
        _spriteFace.SetPosition(_Coordinate+_offset);

    if (_spriteFace.GetScale() != _sprite.GetScale())
        _spriteFace.SetScale(_sprite.GetScale());

    if (_spriteFace.GetRotation() != _sprite.GetRotation())
        _spriteFace.SetRotation(_sprite.GetRotation());

    if (_spriteFace.GetScale().x > 1.0f || _spriteFace.GetScale().y > 1.0f)
        _imageFace.SetSmooth(true);
    else
        _imageFace.SetSmooth(false);

    return false;
}

void CCharacterLayer::Subclass_Render(CWindow* Surf_Dest)
{
    if (_isFaceEnable)
        Surf_Dest->Draw(_spriteFace);
}

bool CCharacterLayer::LoadImage(const char* fileName, CImage &image, CSprite &sprite)
{
    if (fileName == NULL)
        return false;

    if (!CSurface::OnLoad(fileName, image))
        return false;

    image.SetSmooth(false);
    sprite.SetTexture(image);

    return true;
}

bool CCharacterLayer::LoadChara(const char* FileName)
{
    //char BOM[3] = {0xEF,0xBB,0xBF};
    list<string> __expressions = Cio::LoadTxtFile(FileName, "\r\n");
    map<string, string> __valueList;

    for (list<string>::iterator it=__expressions.begin();
        it!=__expressions.end(); it++){
        string __paraName = "";
        string __paraValue = "";
        if(Cio::AnalyticExpression((*it), __paraName, __paraValue))
            __valueList[__paraName] = __paraValue;
    }

    if (!CheckList(__valueList))
        return false;

    if (!SetProperty(__valueList))
        return false;

    return true;
}

bool CCharacterLayer::CheckList(map<string, string> list) 
{
    bool result = true;
    if (list.count("BODY_PATH") < 1){
        cout << "can't find value of BODY_PATH." << endl;
        result = false;
    }

    if (list.count("FACE_OFFSET_X") < 1){
        cout << "can't find value of FACE_OFFSET_X." << endl;
        result = false;
    }
    
    if (list.count("FACE_OFFSET_Y") < 1){
        cout << "can't find value of FACE_OFFSET_Y." << endl;
        result = false;
    }

    return result;
}

bool CCharacterLayer::SetProperty(map<string, string> list)
{
    if (!LoadImage(list["BODY_PATH"].c_str(), _image, _sprite))
        return false;

    _offset.x = atof(list["FACE_OFFSET_X"].c_str());
    _offset.y = atof(list["FACE_OFFSET_Y"].c_str());

    list.erase("BODY_PATH");
    list.erase("FACE_OFFSET_X");
    list.erase("FACE_OFFSET_Y");

    _faceList.clear();
    _faceList.insert(list.begin(), list.end());

    return true;
}

bool CCharacterLayer::SetFace(string name)
{
    _isFaceEnable = false;
    if (_faceList.count(name) > 0) 
        _isFaceEnable = LoadImage(_faceList[name].c_str(), _imageFace, _spriteFace);

    return _isFaceEnable;
}
