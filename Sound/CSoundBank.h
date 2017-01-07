/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CSOUNDBANK_H_
    #define _CSOUNDBANK_H_

#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include "../Common/CCommon.h"
#include "../Action/CActionTo.h"
#include "../Action/CActionBy.h"

using namespace std;
//==============================================================================

class CSoundBank {
    private:
        friend class        CResourceManager;

        class CVoiceStream : public sf::SoundStream
        {
            public:
                string                  _Name;

                CVoiceStream(){ _Name="", _isSilence = true; }
                void Load(const sf::SoundBuffer& buffer);
                bool IsSilence() const;
            private:
                bool                    _isSilence;
                vector<sf::Int16>       _m_samples;
                size_t                  _m_currentSample;

                virtual bool onGetData(Chunk& data);
                virtual void onSeek(sf::Time timeOffset);
        };

        class CMusicData
        {
            public:
                string          _Path;
                char*           _Data;
                unsigned long   _Size;

                CMusicData();
        };

        float                                           _musicVolume;
        list<CVoiceStream*>                             _voicePool;
        list<pair<string, sf::Sound> >                  _soundPool;
        pair<string, sf::Music*>                        _bgm;
        map<string, sf::SoundBuffer*>                   _voiceList;
        map<string, sf::SoundBuffer*>                   _seList;
        map<string, CMusicData>                         _musicList;

        int AddBuffer(map<string, sf::SoundBuffer*>& bufList, string name, string filename);
        bool DelBuffer(map<string, sf::SoundBuffer*>& bufList, string name);
    public:
        enum EVoiceFlag{
            VOICE_STOPPED = 1,
            VOICE_SILENCE,
            VOICE_PLAYING,
        };

        CSoundBank();

        bool OnInit();
        void OnLoop();
        void OnCleanup();

        int AddSE(string name, string filename) ;
        bool DeleteSE(string name);

        void PlaySE(vector<string> args);
        bool PlaySE(string name, float vol, bool loop);

        void StopSE(vector<string> args);
        void StopSE(string name);
        void StopSE();

        int AddVoice(string name, string filename);
        bool PlayVoice(string name);
        bool PlayVoice(sf::SoundBuffer* buffer);
        bool DeleteVoice(string name);
        const sf::SoundBuffer* GetVoice(string name);
        bool GetVoiceStatus();
        bool GetVoiceStatus(string name);
        char IsVoiceSilence(string name);
        void StopVoice();
        
        bool AddBgm(string name, string FileName);
        bool DelBgm(string name);
        bool OnLoadBGM(const char* FileName);
        void SetBGMLoop(bool loop);
        sf::Sound::Status GetBgmStatus();

        void PlayBgm();
        void PlayBgm(vector<string> args);
        int PlayBgm(string name, float vol, bool loop);
        void PauseBgm();
        void StopBgm();
        void OnSaveData(Object& json) const;
        void OnLoadData(Object json);

        CActionTo* CreateActionOfMusicVolTo(size_t elapsed, float vol, bool restore);
        CActionBy* CreateActionOfMusicVolBy(size_t elapsed, float vol, bool restore);
};

//==============================================================================

#endif
