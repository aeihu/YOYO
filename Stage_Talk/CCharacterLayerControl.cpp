/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCharacterLayerControl.h"
#include "../Common/CAdder.h"

CCharacterLayerControl::CCharacterLayerControl()
{
    _interval = 10;
}

bool CCharacterLayerControl::IsAlreadyExists(string name)
{
    return _CharacterList.count(name) < 1 ? false : true;
}

char CCharacterLayerControl::AddCharacter(string name, const char* filename)
{
    if (_CharacterList.count(name)>0){
        return 1;
    }
    else{
        _CharacterList[name] = CCharacterLayer();
        _CharacterList[name]._Alpha = 0;
        
        if (!_CharacterList[name].LoadChara(filename)){
            _CharacterList.erase(name);
            return 2;
        }
    }
    return 0;
}

bool CCharacterLayerControl::DelCharacter(string name)
{
    if (_CharacterList.count(name) == 0)
        return false;
    else{
        _CharacterList.erase(name);
    }
    return true;
}

bool CCharacterLayerControl::Move(string name, float x, float y, float increment, bool pause)
{
    if (_CharacterList.count(name) < 1)
        return false;

    if (increment > -0.001f && increment < 0.001f)
        increment = (float)CCommon::common.INCREMENT;

    if (abs(_CharacterList[name]._Coordinate.x-x) 
        > abs(_CharacterList[name]._Coordinate.y-y)){
        float ratio = 1;
        if (abs(_CharacterList[name]._Coordinate.y-y) != 0){
            ratio = abs(_CharacterList[name]._Coordinate.y-y) / abs(_CharacterList[name]._Coordinate.x-x);
            _CharacterList[name].Insert(0, y, pause, &_CharacterList[name]._Coordinate.y, increment*ratio);
        }
        
        _CharacterList[name].Insert(0, x, pause, &_CharacterList[name]._Coordinate.x, increment);
    }
    else if (abs(_CharacterList[name]._Coordinate.x-x) 
        < abs(_CharacterList[name]._Coordinate.y-y)){
        float ratio = 1;
        if (abs(_CharacterList[name]._Coordinate.x-x) != 0){
            ratio = abs(_CharacterList[name]._Coordinate.x-x) / abs(_CharacterList[name]._Coordinate.y-y);
            _CharacterList[name].Insert(0, x, pause, &_CharacterList[name]._Coordinate.x, increment*ratio);
        }

        _CharacterList[name].Insert(0, y, pause, &_CharacterList[name]._Coordinate.y, increment);
    }
    else{
        _CharacterList[name].Insert(0, x, pause, &_CharacterList[name]._Coordinate.x, increment);
        _CharacterList[name].Insert(0, y, pause, &_CharacterList[name]._Coordinate.y, increment);
    }
    return true;
}

char CCharacterLayerControl::Show(string name, float x, float y, char type, float increment, bool pause, int alpha)
{
    if (_CharacterList.count(name) < 1)
        return -1;

    if (_CharacterList[name].GetVisible())
        return -2;

    if (increment > -0.001f && increment < 0.001f)
        increment = (float)CCommon::common.INCREMENT;

    float buf = CCommon::common.CHARACTER_LAYER_MOVE_BUFFER;
    float __x = x;
    float __y = y;
    int __inc = (int)increment;
    __inc = ((int)buf)/(__inc == 0 ? 1:__inc);//???
    __inc = __inc<=0?255:255/__inc;

    switch (type)
    {
        case 'u':
            __y += buf;
        break;
        case 'r':
            __x -= buf;
        break;
        case 'd':
            __y -= buf;
        break;
        case 'l':
            __x += buf;
        break;
        default:
            SetImageVisibility(name, alpha, __inc, pause);
            _CharacterList[name]._Coordinate.x = __x;
            _CharacterList[name]._Coordinate.y = __y;
            return 0;
        break;
    }

    _CharacterList[name]._Coordinate.x = __x;
    _CharacterList[name]._Coordinate.y = __y;
    if (Move(name, x, y, increment, pause)){
        SetImageVisibility(name, alpha, __inc, pause);
        return 0;
    }

    return -1;
}

bool CCharacterLayerControl::Hide(string name, char type, float increment, bool pause)
{
    if (_CharacterList.count(name) < 1)
        return false;

    if (increment > -0.001f && increment < 0.001f)
        increment = (float)CCommon::common.INCREMENT;

    float buf = CCommon::common.CHARACTER_LAYER_MOVE_BUFFER;
    float __x = _CharacterList[name]._Coordinate.x;
    float __y = _CharacterList[name]._Coordinate.y;
    int __inc = (int)increment;
    __inc = ((int)buf)/(__inc == 0 ? 1:__inc);//???
    __inc = __inc<=0?255:255/__inc;

    switch (type)
    {
        case 'u':
            __y -= buf;
        break;
        case 'r':
            __x += buf;
        break;
        case 'd':
            __y += buf;
        break;
        case 'l':
            __x -= buf;
        break;
        default:
            SetImageVisibility(name, 0, __inc, pause);
            //SetImageVisibility(name, 0, (int)increment, pause);
            return true;
        break;
    }

    if (Move(name, __x, __y, increment, pause)){
        int inc = 255/(((int)buf)/((int)increment));
        SetImageVisibility(name, 0, inc<=0?1:inc, pause);
        return true;
    }

    return false;
}

bool CCharacterLayerControl::SetImageVisibility(string name, int alpha, int increment, bool pause)
{
    if (_CharacterList.count(name) < 1)
        return false;

    if (increment == 0)
        increment = CCommon::common.INCREMENT;

    _CharacterList[name].Insert(0, alpha, pause, &_CharacterList[name]._Alpha, increment);
    return true;
}

void CCharacterLayerControl::OnLoop(bool &pause)
{
    for (map<string, CCharacterLayer>::iterator it=_CharacterList.begin();
        it!=_CharacterList.end();)
    {
        if (!CSoundBank::_SoundControl.IsVoiceSilence((*it).first))
            (*it).second._AnimationControl.TurnOn();
        else
            (*it).second._AnimationControl.TurnOff();

        if ((*it).second.OnLoop()) 
            pause=true;

//        if((*it).second._Alpha == 0){
//            (*it).second.Clear();
//            it=_CharacterList.erase(it);
//
//            if (it == _CharacterList.end())
//                break;
//        }

        else
            it++;
    }
}

void CCharacterLayerControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (map<std::string, CCharacterLayer>::iterator it=_CharacterList.begin(); 
        it!=_CharacterList.end(); it++ )
    {
        (*it).second.OnRender(Surf_Dest);
    }
}

CImageBaseClass* CCharacterLayerControl::GetObject(std::string name)
{
    if (_CharacterList.count(name) < 1)
        return NULL;
    
    return &_CharacterList[name];
}