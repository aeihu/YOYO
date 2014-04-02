/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CSoundBank.h"

//==============================================================================
CSoundBank CSoundBank::_SoundControl;

//==============================================================================
CSoundBank::CSoundBank() {
    _voiceList.clear();
}

//------------------------------------------------------------------------------
int CSoundBank::AddSE(std::string name, const char* FileName) {
    if(_seList.count(name) > 0)
        return -1;

    sf::SoundBuffer Buffer;
    if (!Buffer.loadFromFile(FileName))
        return -2;

    _seList[name].first = Buffer;
    _seList[name].second.setBuffer(_seList[name].first);

  return 0;
}
//https://github.com/LaurentGomila/SFML/wiki/Source%3A-MP3-Player
bool CSoundBank::OnLoadBGM(const char* FileName)
{
    if (!_bgm.openFromFile(FileName))
        return false;

    return true;
}

//------------------------------------------------------------------------------
void CSoundBank::OnCleanup()
{
    _seList.clear();
    _voiceList.clear();
}


//==============================================================================
bool CSoundBank::PlaySE(string name)
{
    if (_seList.count(name) < 1)
        return false;

    _seList[name].second.play();
    return true;
}

bool CSoundBank::DeleteSE(string name)
{
    if(_seList.count(name) < 1)
        return false;

    _seList.erase(name);
    return true;
}

//==============================================================================

sf::Sound::Status CSoundBank::GetBgmStatus()
{
    return _bgm.getStatus();
}

void CSoundBank::PauseBgm()
{
    _bgm.pause();
}

void CSoundBank::PlayBgm()
{
    _bgm.play();
}

bool CSoundBank::Say(const char* FileName)
{    
    sf::SoundBuffer Buffer;
    if (!Buffer.loadFromFile(FileName))
        return false;

    char name = 0;
    while (_voiceList.count(name) > 0){
        name++;
    }

    _voiceList[name].first = Buffer;
    _voiceList[name].second.setBuffer(_voiceList[name].first);
    _voiceList[name].second.play();

  return true;
}

void CSoundBank::OnLoop()
{
    if (_voiceList.size() < 1)
        return;

    for (map<char, pair<sf::SoundBuffer,sf::Sound> >::iterator 
        it=_voiceList.begin(); it!=_voiceList.end();  )
    {
        if ((*it).second.second.getStatus() == sf::Sound::Stopped){
            _voiceList.erase(it);
            if (it==_voiceList.end())
                break;
        }
        else
            it++;
    }
}

unsigned int CSoundBank::GetSEPitch(string name)
{
    return *(_seList[name].second.getBuffer()->getSamples());
}