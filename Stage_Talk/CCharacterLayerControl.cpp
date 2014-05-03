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

char CCharacterLayerControl::AddCharacter(string name, const char* filename)
{
    if (_characterList.count(name)>0){
        return 1;
    }
    else{
        _characterList[name] = CCharacterLayer();
        _characterList[name]._Alpha = 0;
        
        if (!_characterList[name].LoadChara(filename)){
            _characterList.erase(name);
            return 2;
        }
    }
    return 0;
}

bool CCharacterLayerControl::DelCharacter(string name)
{
    if (_characterList.count(name) == 0)
        return false;
    else{
        _characterList.erase(name);
    }
    return true;
}

void CCharacterLayerControl::OnLoop(bool &pause)
{
    for (map<string, CCharacterLayer>::iterator it=_characterList.begin();
        it!=_characterList.end();)
    {
        if (!CSoundBank::_SoundControl.IsVoiceSilence((*it).first))
            (*it).second._AnimationControl.TurnOn();
        else
            (*it).second._AnimationControl.TurnOff();

        if ((*it).second.OnLoop()) 
            pause=true;
        else
            it++;
    }
}

void CCharacterLayerControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (map<std::string, CCharacterLayer>::iterator it=_characterList.begin(); 
        it!=_characterList.end(); it++ )
    {
        (*it).second.OnRender(Surf_Dest);
    }
}

CObject* CCharacterLayerControl::GetObject(std::string name)
{
    if (_characterList.count(name) < 1)
        return NULL;
    
    return &_characterList[name];
}

void CCharacterLayerControl::OnCleanup()
{
    _characterList.clear();
}