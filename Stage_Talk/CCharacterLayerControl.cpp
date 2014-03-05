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

char CCharacterLayerControl::AddCharacter(string name, const char* filename, float x, float y)
{
    if (_CharacterList.count(name)>0){
        return 1;
    }
    else{
        _CharacterList[name] = CCharacterLayer();
        _CharacterList[name]._Alpha = 1;
        
        if (!_CharacterList[name].LoadChara(filename)){
            _CharacterList.erase(name);
            return 2;
        }
    }
    return 0;
}

bool CCharacterLayerControl::Move(string name, string position, float increment, bool pause)
{
    if (_positions.count(name) < 1)
        return false;
    
    return Move(name, _positions[position].x, _positions[position].y, increment, pause);
}

bool CCharacterLayerControl::Move(string name, float x, float y, float increment, bool pause)
{
    if (_CharacterList.count(name) < 1)
        return false;

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

bool CCharacterLayerControl::Show(string name, float x, float y, char type, float increment, bool pause)
{
    if (_CharacterList.count(name) < 1)
        return false;

    if (_CharacterList[name]._Alpha == 255)
        return false;

    float buf = CCommon::common.CHARACTER_LAYER_MOVE_BUFFER;
    float __x = x;
    float __y = y;
    int __inc = ((int)buf)/((int)increment);
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
            SetVisibility(name, 255, __inc, pause);
            return true;
        break;
    }

    _CharacterList[name]._Coordinate.x = __x;
    _CharacterList[name]._Coordinate.y = __y;
    if (Move(name, x, y, increment, pause)){
        SetVisibility(name, 255, __inc, pause);
        return true;
    }

    return false;
}

bool CCharacterLayerControl::Show(string name, string position, char type, float increment, bool pause)
{
    if (_positions.count(position) < 1)
        return false;

    return Show(name, _positions[position].x, _positions[position].y, type, increment, pause);
}

bool CCharacterLayerControl::Hide(string name, char type, float increment, bool pause)
{
    if (_CharacterList.count(name) < 1)
        return false;

    float buf = CCommon::common.CHARACTER_LAYER_MOVE_BUFFER;
    float __x = _CharacterList[name]._Coordinate.x;
    float __y = _CharacterList[name]._Coordinate.y;

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
            SetVisibility(name, 0, (int)increment, pause);
            return true;
        break;
    }

    if (Move(name, __x, __y, increment, pause)){
        int inc = 255/(((int)buf)/((int)increment));
        SetVisibility(name, 0, inc<=0?1:inc, pause);
        return true;
    }

    return false;
}

bool CCharacterLayerControl::SetVisibility(string name, int alpha, int increment, bool pause)
{
    if (_CharacterList.count(name) < 1)
        return false;

    _CharacterList[name].Insert(0, alpha, pause, &_CharacterList[name]._Alpha, increment);
    return true;
}

void CCharacterLayerControl::AddPosition(string name, float x, float y)
{
    _positions[name].x = x;
    _positions[name].y = y;
}

void CCharacterLayerControl::DelPosition(string name)
{
    if (_positions.count(name)>0)
        _positions.erase(name);
}

bool CCharacterLayerControl::GetPosition(string name, float* x, float* y)
{
    if (_positions.count(name)<1)
        return false;

    if (x != NULL) *x=_positions[name].x;
    if (y != NULL) *y=_positions[name].y;
    return true;
}

void CCharacterLayerControl::OnLoop(bool &pause)
{
    for (map<string, CCharacterLayer>::iterator it=_CharacterList.begin();
        it!=_CharacterList.end();)
    {
        if((*it).second.OnLoop()) 
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
