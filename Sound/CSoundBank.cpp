/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CSoundBank.h"

//==============================================================================
CSoundBank::CSoundBank() {
    _bgm.second = new sf::Music();
    _voiceList.clear();
}

//------------------------------------------------------------------------------
int CSoundBank::AddBuffer(map<string, sf::SoundBuffer*>& bufList, string name, string filename)
{
    if (bufList.count(name) > 0)
        return -1;

    sf::SoundBuffer* __buffer = new sf::SoundBuffer();

    if (filename.find("*") == string::npos){
        if (!__buffer->loadFromFile(filename)){
            cout << "CSoundBank::AddBuffer(): failed to load '" << filename << "'" << endl;
            return -2;
        }
    }
    else {
        char* __buf = NULL;
        unsigned long __size = 0;
        CZlib::OpenFileInZip(filename, __buf, __size);

        if (__buf != NULL){
            if (__buffer->loadFromMemory(__buf, __size)){
                CZlib::CloseFileInZip(__buf);
            }
            else{
                CZlib::CloseFileInZip(__buf);
                cout << "CSoundBank::AddBuffer(): failed to load '" << filename << "'" << endl;
                return -2;
            }
        }
        else{
            CZlib::CloseFileInZip(__buf);
            cout << "CSoundBank::AddBuffer(): failed to load '" << filename << "'" << endl;    
            return -2;
        }
    }

    bufList[name] = __buffer;
    return 0;
}

int CSoundBank::AddSE(string name, string filename) 
{
    return AddBuffer(_seList, name, filename);
}

int CSoundBank::AddVoice(string name, string filename) {
    return AddBuffer(_voiceList, name, filename);
}

//https://github.com/LaurentGomila/SFML/wiki/Source%3A-MP3-Player
bool CSoundBank::OnLoadBGM(const char* FileName)
{
    if (!_bgm.second->openFromFile(FileName))
        return false;

    return true;
}

void CSoundBank::SetBGMLoop(bool loop)
{
    _bgm.second->setLoop(loop);
}

//------------------------------------------------------------------------------
void CSoundBank::OnCleanup()
{
    StopBgm();
    StopSE();
    StopVoice();
    delete _bgm.second;
    _bgm.second = NULL;

    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++){
        if ((*it) != NULL)
            delete (*it);
    }

    for (map<string, sf::SoundBuffer*>::iterator it=_seList.begin() ; it!=_seList.end(); it++){
        if ((*it).second != NULL){
            delete (*it).second;
            (*it).second = NULL;
        }
    }

    for (map<string, sf::SoundBuffer*>::reverse_iterator it=_voiceList.rbegin() ; it!=_voiceList.rend(); it++){
        if ((*it).second != NULL){
            delete (*it).second;
            (*it).second = NULL;
        }
    }
    
    for (map<string, CMusicData>::reverse_iterator it=_musicList.rbegin() ; it !=_musicList.rend(); it++){
        DelBgm((*it).first);
    }

    _seList.clear();
    _voiceList.clear();
    _musicList.clear();
    _voicePool.clear();
    _soundPool.clear();
}

//==============================================================================
void CSoundBank::PlaySE(vector<string> args)
{
    if (args.size() >= 2)
        PlaySE(args[0], atof(args[1].c_str()), args.size() > 2);
}

bool CSoundBank::PlaySE(string name, float vol, bool loop)
{
    if (_seList.count(name) < 1)
        return false;
    
    for (list<pair<string, sf::Sound> >::iterator it=_soundPool.begin() ; it != _soundPool.end(); it++){
        if ((*it).second.getStatus() == sf::Sound::Stopped){
            (*it).first = name;
            (*it).second.setBuffer(*_seList[name]);
            (*it).second.setLoop(loop);
            (*it).second.setVolume(vol * CCommon::_Common.SE_VOLUME);
            (*it).second.play();
            return true;
        }
    }

    _soundPool.push_back(make_pair(name, sf::Sound()));
    _soundPool.back().first = name;
    _soundPool.back().second.setBuffer(*_seList[name]);
    _soundPool.back().second.setLoop(loop);
    _soundPool.back().second.setVolume(vol * CCommon::_Common.SE_VOLUME);
    _soundPool.back().second.play();
    return true;
}

void CSoundBank::StopVoice()
{
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++){
        if ((*it)->getStatus() == sf::Sound::Playing){
            (*it)->stop();
        }
    }
}

void CSoundBank::PlayVoice(vector<string> args)
{
    if (args.size() > 0){
        StopVoice();
        PlayVoice(args[0]);
    }
}

bool CSoundBank::PlayVoice(string name)
{
    if (_voiceList.count(name) < 1)
        return false;
    
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++){
        if ((*it)->getStatus() == sf::Sound::Stopped){
            (*it)->Load(*_voiceList[name]);
            (*it)->_Name = name;
            (*it)->setVolume(CCommon::_Common.VOICE_VOLUME);
            (*it)->play();
            return true;
        }
    }

    _voicePool.push_back(new CVoiceStream());
    _voicePool.back()->Load(*_voiceList[name]);
    _voicePool.back()->_Name = name;
    _voicePool.back()->setVolume(CCommon::_Common.VOICE_VOLUME);
    _voicePool.back()->play();
    return true;
}

bool CSoundBank::DelBuffer(map<string, sf::SoundBuffer*>& bufList, string name)
{
    if(bufList.count(name) < 1)
        return false;

    delete bufList[name];
    bufList[name] = NULL;
    bufList.erase(name);
    return true;
}

bool CSoundBank::DeleteSE(string name)
{
    return DelBuffer(_seList, name);
}

void CSoundBank::StopSE(vector<string> args)
{
    for (vector<string>::iterator it = args.begin(); it != args.end(); it++){
        StopSE(*it);
    }
}

void CSoundBank::StopSE(string name)
{
    if (name.empty())
        return;

    for (list<pair<string, sf::Sound> >::iterator it=_soundPool.begin() ; it != _soundPool.end();it++){
        if ((*it).first == name){
            (*it).second.stop();
            (*it).second.resetBuffer();
        }
    }
}

void CSoundBank::StopSE()
{
    for (list<pair<string, sf::Sound> >::iterator it=_soundPool.begin() ; it != _soundPool.end();it++){
        (*it).second.stop();
        (*it).second.resetBuffer();
    }
}

bool CSoundBank::DeleteVoice(string name)
{
    return DelBuffer(_voiceList, name);
}

//==============================================================================

bool CSoundBank::AddBgm(string name, string FileName) 
{
    if(_musicList.count(name) > 0)
        return false;

    _musicList[name] = CMusicData();
    _musicList[name]._Path = FileName;
    
    if (_musicList[name]._Path.find("*") != string::npos) {
        CZlib::OpenFileInZip(_musicList[name]._Path, 
            _musicList[name]._Data, 
            _musicList[name]._Size);

        if (_musicList[name]._Data == NULL){
            CZlib::CloseFileInZip(_musicList[name]._Data);
            cout << "CSoundBank::AddBgm(): failed to load '" << _musicList[name]._Path << "'" << endl;
            _musicList.erase(name);
            return false;
        }
    }

    return true;
}

bool CSoundBank::DelBgm(string name)
{
    if(_musicList.count(name) < 1)
        return false;

    if (_musicList[name]._Data != NULL)
        CZlib::CloseFileInZip(_musicList[name]._Data);

    _musicList.erase(name);
    return true;
}

sf::Sound::Status CSoundBank::GetBgmStatus()
{
    return _bgm.second->getStatus();
}

void CSoundBank::PauseBgm()
{
    _bgm.second->pause();
}
        
void CSoundBank::StopBgm()
{
    _bgm.second->stop();
}

void CSoundBank::PlayBgm()
{
    _bgm.second->play();
}
        
void CSoundBank::PlayBgm(vector<string> args)
{
    if (args.size() >= 2)
        PlayBgm(args[0], atof(args[1].c_str()), args.size() > 2);
}

int CSoundBank::PlayBgm(string name, float vol, bool loop)
{
    if(_musicList.count(name) < 1)
        return -1;

    if (_musicList[name]._Path.find("*") == string::npos){
        if (!_bgm.second->openFromFile(_musicList[name]._Path)){
            cout << "CSoundBank::PlayBgm(): failed to load '" << _musicList[name]._Path << "'" << endl;
            return -2;
        }
    }
    else {
        if (!_bgm.second->openFromMemory(_musicList[name]._Data, _musicList[name]._Size)){
            cout << "CSoundBank::PlayBgm(): failed to load '" << _musicList[name]._Path << "'" << endl;
            return -2;
        }
    }
    
    _musicVolume = vol;
    _bgm.first = name;
    _bgm.second->setLoop(loop);
    _bgm.second->setVolume(_musicVolume * CCommon::_Common.BGM_VOLUME);
    _bgm.second->play();
    return 0;
}

CActionTo* CSoundBank::CreateActionOfMusicVolTo(size_t elapsed, float vol, bool restore, bool pause)
{
    return new CActionTo(&_musicVolume, elapsed, vol, restore, pause);
}

CActionBy* CSoundBank::CreateActionOfMusicVolBy(size_t elapsed, float vol, bool restore, bool pause)
{
    return new CActionBy(&_musicVolume, elapsed, vol, restore, pause);
}

void CSoundBank::OnLoop()
{
    if (_musicVolume * CCommon::_Common.BGM_VOLUME != _bgm.second->getVolume())
        _bgm.second->setVolume(_musicVolume * CCommon::_Common.BGM_VOLUME);

    for (list<pair<string, sf::Sound> >::iterator it=_soundPool.begin() ; it != _soundPool.end();){
        if ((*it).second.getStatus() == sf::Sound::Stopped){
            (*it).second.resetBuffer();
            if (_soundPool.size() > CCommon::_Common.SOUND_POOL_NUM){
                it=_soundPool.erase(it);
                continue;
            }
            else{
                (*it).first = "";
            }
        }
        ++it;
    }
    
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); ){
        if ((*it)->getStatus() == sf::Sound::Stopped){
            if (_voicePool.size() > CCommon::_Common.VOICE_POOL_NUM){
                delete (*it);
                it=_voicePool.erase(it);

                if (it == _voicePool.end())
                    break;
            }
            else{
                (*it)->_Name = "";
                it++;
            }
        }
        else
            it++;
    }
}

char CSoundBank::IsVoiceSilence(string name)
{
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++){
        if ((*it)->_Name == name){
            if ((*it)->getStatus() == CVoiceStream::Playing){
                if ((*it)->IsSilence())
                    return VOICE_SILENCE;
                else
                    return VOICE_PLAYING;
            }
            else
                return VOICE_STOPPED;   
        }
    }

    return VOICE_STOPPED;   
}

bool CSoundBank::GetVoiceStatus()
{
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++)
        if ((*it)->getStatus() == CVoiceStream::Playing)
            return true;
            
    return false;
}

bool CSoundBank::GetVoiceStatus(string name)
{
    for (list<CVoiceStream*>::iterator it=_voicePool.begin() ; it != _voicePool.end(); it++)
        if ((*it)->_Name == name){
            if ((*it)->getStatus() == CVoiceStream::Playing)
                return true;
            else
                return false;
        }

    return false;
}

bool CSoundBank::OnInit()
{
    for (unsigned char i=0; i<CCommon::_Common.SOUND_POOL_NUM; i++){
        _soundPool.push_back(make_pair("", sf::Sound()));
    }

    for (unsigned char i=0; i<CCommon::_Common.VOICE_POOL_NUM; i++){
        _voicePool.push_back(new CVoiceStream());
    }
    
    return true;
}
        
void CSoundBank::OnSaveData(Object& json) const
{
    if (_bgm.second->getStatus() != sf::Music::Stopped){
        if (!_bgm.first.empty()){
            Object _obj;
            _obj << "name" << _bgm.first;
            _obj << "vol" << _musicVolume;
            _obj << "loop" << _bgm.second->getLoop();
            _obj << "status" << (_bgm.second->getStatus() == sf::Music::Playing ? true : false);
            json << "bgm" << _obj;
        }
    }

    Array _array;
    for (list<pair<string, sf::Sound> >::const_iterator it=_soundPool.begin(); it!= _soundPool.end();++it){
        if ((*it).second.getStatus() != sf::Sound::Stopped){
            if (!(*it).first.empty()){
                Object _obj;
                _obj << "name" << (*it).first;
                _obj << "vol" << (*it).second.getVolume() / CCommon::_Common.SE_VOLUME;
                _obj << "loop" << (*it).second.getLoop();
                _array << _obj;
            }
        }
    }
    json << "se" << _array;
}

void CSoundBank::OnLoadData(Object json)
{
    if (json.has<Object>("bgm")){
        Object& __bgm = json.get<Object>("bgm");
        PlayBgm(__bgm.get<String>("name"), __bgm.get<Number>("vol"), __bgm.get<Boolean>("loop"));

        if (!__bgm.get<Boolean>("status"))
            PauseBgm();
    }
    
    if (json.has<Array>("se")){
        Array& __seList = json.get<Array>("se");
        for (size_t i=0; i<__seList.size(); i++){
            Object& __se = __seList.get<Object>(i);
            PlaySE(__se.get<String>("name"), __se.get<Number>("vol"), __se.get<Boolean>("loop"));
        }
    }
}

void CSoundBank::CVoiceStream::Load(const sf::SoundBuffer& buffer)
{
    _m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());
    _m_currentSample = 0;
    initialize(buffer.getChannelCount(), buffer.getSampleRate());
}

bool CSoundBank::CVoiceStream::onGetData(Chunk& data)
{
    const int samplesToStream = 5000;
    _isSilence = true;

    data.samples = &_m_samples[_m_currentSample];

    if (_m_currentSample + samplesToStream <= _m_samples.size())
    {
        data.sampleCount = samplesToStream;
        _m_currentSample += samplesToStream;

        if (data.samples != NULL)
            if (*(data.samples) < -100 || *(data.samples) > 100)
                _isSilence = false;

        return true;
    }
    else
    {
        data.sampleCount = _m_samples.size() - _m_currentSample;
        _m_currentSample = _m_samples.size();

        if (data.samples != NULL)
            if (*(data.samples) < -100 || *(data.samples) > 100)
                _isSilence = false;

        return false;
    }
}

void CSoundBank::CVoiceStream::onSeek(sf::Time timeOffset)
{
    _m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
}

bool CSoundBank::CVoiceStream::IsSilence() const
{
    return _isSilence;
}

CSoundBank::CMusicData::CMusicData()
{
    _Path = "";
    _Data = NULL;
    _Size = 0;
}