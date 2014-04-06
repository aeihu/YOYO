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
int CSoundBank::AddBuffer(map<string, sf::SoundBuffer>& list, string name, const char* FileName)
{
    if(list.count(name) > 0)
        return -1;

    sf::SoundBuffer Buffer;
    if (!Buffer.loadFromFile(FileName))
        return -2;

    list[name] = Buffer;

    return 0;
}

int CSoundBank::AddSE(string name, const char* FileName) {
    return AddBuffer(_seList, name, FileName);
}

int CSoundBank::AddVoice(string name, const char* FileName) {
    return AddBuffer(_voiceList, name, FileName);
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
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++){
        if ((*it) != NULL)
            delete (*it);
    }

    _voicePool.clear();
    _soundPool.clear();
    _seList.clear();
    _voiceList.clear();
}


//==============================================================================
bool CSoundBank::PlaySE(string name)
{
    if (_seList.count(name) < 1)
        return false;
    
    for (list<sf::Sound>::iterator it=_soundPool.begin() ; it != _soundPool.end(); it++){
        if ((*it).getStatus() == sf::Sound::Stopped){
            (*it).setBuffer(_seList[name]);
            (*it).play();
            return true;
        }
    }

    _soundPool.push_back(sf::Sound());
    _soundPool.back().setBuffer(_seList[name]);
    _soundPool.back().play();
    return true;
}

bool CSoundBank::PlayVoice(string name)
{
    return true;
}

bool CSoundBank::DelBuffer(map<string, sf::SoundBuffer>& list, string name)
{
    if(list.count(name) < 1)
        return false;

    list.erase(name);
    return true;
}

bool CSoundBank::DeleteSE(string name)
{
    return DelBuffer(_seList, name);
}

bool CSoundBank::DeleteVoice(string name)
{
    return DelBuffer(_voiceList, name);
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

void CSoundBank::OnLoop()
{
    if (_soundPool.size() > CCommon::common.SOUND_POOL_NUM){
        for (list<sf::Sound>::iterator it=_soundPool.begin() ; it != _soundPool.end();){
            if ((*it).getStatus() == sf::Sound::Stopped){
                _soundPool.erase(it);

                if (_soundPool.size() <= CCommon::common.SOUND_POOL_NUM)
                    break;
            }
            else
                it++;
        }
    }

    if (_voicePool.size() > CCommon::common.VOICE_POOL_NUM){
        for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); ){
            if ((*it)->getStatus() == sf::Sound::Stopped){
                delete (*it);
                _voicePool.erase(it);

                if (_voicePool.size() <= CCommon::common.SOUND_POOL_NUM)
                    break;
            }
            else
                it++;
        }
    }

    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++){
        if ((*it)->getStatus() == sf::Sound::Stopped){
            (*it)->_VoiceName = "";
        }
    }
}



bool CSoundBank::GetVoiceStatus(string name)
{
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++)
        if ((*it)->_VoiceName == name)
            if ((*it)->getStatus() == CVoiceStream::Playing)
                return true;
            else
                return false;

    return false;
}

bool CSoundBank::OnInit()
{
    for (unsigned char i=0; i<CCommon::common.SOUND_POOL_NUM; i++){
        _soundPool.push_back(sf::Sound());
    }

    for (unsigned char i=0; i<CCommon::common.VOICE_POOL_NUM; i++){
        _voicePool.push_back(new CVoiceStream());
    }
    
    return true;
}

void CSoundBank::CVoiceStream::Load(const sf::SoundBuffer& buffer)
{
    _m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());
    _m_currentSample = 0;
    initialize(buffer.getChannelCount(), buffer.getSampleRate());
}

bool CSoundBank::CVoiceStream::onGetData(Chunk& data)
{
    const int samplesToStream = 50000;

    data.samples = &_m_samples[_m_currentSample];

    if (_m_currentSample + samplesToStream <= _m_samples.size())
    {
        data.sampleCount = samplesToStream;
        _m_currentSample += samplesToStream;
        return true;
    }
    else
    {
        data.sampleCount = _m_samples.size() - _m_currentSample;
        _m_currentSample = _m_samples.size();
        return false;
    }
}

void CSoundBank::CVoiceStream::onSeek(sf::Time timeOffset)
{
    _m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
}