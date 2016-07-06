/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CTEXTLOG_H_
    #define _CTEXTLOG_H_

#include "CButtonBase.h"
#include "../Sound/CSoundBank.h"
#include "../Text/CTextFunction.h"

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

        bool OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        void OnLoop();
        void OnCleanup();
        void OnRender(sf::RenderTarget* Surf_Dest);
};

#endif