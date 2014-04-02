/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
    _AnimationControl._Type = CAnimation::Oscillate;
}

bool CCharacterLayer::Subclass_Loop()
{
    if (_framesOfMouth._sprite.getColor().a != _Alpha)
        _framesOfMouth._sprite.setColor(sf::Color(255,255,255,_Alpha));

    if (_Coordinate+_offset != _framesOfMouth._sprite.getPosition())
        _framesOfMouth._sprite.setPosition(_Coordinate+_offset);

    if (_framesOfMouth._sprite.getScale() != _sprite.getScale())
        _framesOfMouth._sprite.setScale(_sprite.getScale());

    if (_framesOfMouth._sprite.getRotation() != _sprite.getRotation())
        _framesOfMouth._sprite.setRotation(_sprite.getRotation());

    if (_framesOfMouth._sprite.getScale().x > 1.0f || _framesOfMouth._sprite.getScale().y > 1.0f)
        _imageFace.setSmooth(true);
    else
        _imageFace.setSmooth(false);

    if (_isFaceEnable && _AnimationControl.GetEnable()){
        _framesOfMouth.SetCurrentImageFrame(_AnimationControl.GetCurrentFrame());
        _AnimationControl.OnAnimate(CCommon::common.GetTicks());
    }

    return false;
}

void CCharacterLayer::Subclass_Render(sf::RenderWindow* Surf_Dest)
{
    if (_isFaceEnable)
        Surf_Dest->draw(_framesOfMouth._sprite);
}

bool CCharacterLayer::LoadImage(const char* fileName, sf::Texture &image, sf::Sprite &sprite)
{
    if (fileName == NULL)
        return false;

    if (!CSurface::OnLoad(fileName, image))
        return false;

    image.setSmooth(false);
    sprite.setTexture(image);

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

    if (list.count("FACE_ENABLE") < 1){
        cout << "can't find value of FACE_ENABLE." << endl;
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

    if (list.count("FACE_WIDTH") < 1){
        cout << "can't find value of FACE_WIDTH." << endl;
        result = false;
    }
    
    if (list.count("FACE_HEIGHT") < 1){
        cout << "can't find value of FACE_HEIGHT." << endl;
        result = false;
    }
    
    if (list.count("TALK_MAX_FRAMES") < 1){
        cout << "can't find value of TALK_MAX_FRAMES." << endl;
        result = false;
    }
    
    if (list.count("TALK_FRAME_RATE") < 1){
        cout << "can't find value of TALK_FRAME_RATE." << endl;
        result = false;
    }

    return result;
}

bool CCharacterLayer::SetProperty(map<string, string> list)
{
    if (!LoadImage(list["BODY_PATH"].c_str(), _image, _sprite))
        return false;

    _faceList.clear();

    if (list["FACE_ENABLE"] != "0"){
        _isFaceEnable= true;
        _offset.x = atof(list["FACE_OFFSET_X"].c_str());
        _offset.y = atof(list["FACE_OFFSET_Y"].c_str());
        _AnimationControl._MaxFrames = atoi(list["TALK_MAX_FRAMES"].c_str());
        _AnimationControl.SetFrameRate(atoi(list["TALK_FRAME_RATE"].c_str()));

        _framesOfMouth.SetWidth(atoi(list["FACE_WIDTH"].c_str()));
        _framesOfMouth.SetHeight(atoi(list["FACE_HEIGHT"].c_str()));

        list.erase("BODY_PATH");
        list.erase("FACE_OFFSET_X");
        list.erase("FACE_OFFSET_Y");
        list.erase("TALK_MAX_FRAMES");
        list.erase("TALK_FRAME_RATE");
        list.erase("FACE_WIDTH");
        list.erase("FACE_HEIGHT");
        list.erase("FACE_ENABLE");
        _faceList.insert(list.begin(), list.end());
    }
    else
        _isFaceEnable= false;

    return true;
}

bool CCharacterLayer::SetFace(string name)
{
    bool result = false;
    if (_faceList.count(name) > 0) {
        result = LoadImage(_faceList[name].c_str(), _framesOfMouth._image, _framesOfMouth._sprite);
    }
    else{
        cout << "SetFace(): can't find face \"" << name << "\"." << endl;
    }

    return result;
}
