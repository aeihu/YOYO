/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CTEXTLOG_H_
    #define _CTEXTLOG_H_

#include "CButtonBase.h"
#include "../Sound/CSoundBank.h"

class CTextLog
{
    private: 
        class CVoiceButton : public CButtonBase
        {
            void Exec(void* data=NULL);
        }                   _btnVoice;

        sf::Text            _text;
        sf::SoundBuffer*    _voice;
        int                 _alpha;
        sf::Vector2f        _coordinate;
    public:
        CTextLog();

        void SetTextLog(string text, sf::SoundBuffer* voice, sf::Font& font);
        void SetTextLog(string text, sf::SoundBuffer* voice);
        void SetAlpha(int alpha);
        void SetPosition(float x, float y);

        void OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        void OnLoop();
        void OnCleanup();
        void OnRender(sf::RenderWindow* Surf_Dest);
};

#endif