/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CLOGBOX_H_
    #define _CLOGBOX_H_

#include <SFML/Audio.hpp>
#include "../Gui/CBox.h"
#include "../Gui/CButtonBase.h"
#include "../Gui/CText.h"
#include "../Gui/CScrollbar.h"
#include <deque>

using namespace std;

class CLogBox : public CBox, public CScrollbar::CScrollbarCallback
{
    private:
        class CVoiceButton : public CButtonBase
        {
            protected:
                virtual void Exec(void* data = NULL);

            public:
                using  CButtonBase::SetProperty;
                sf::SoundBuffer*    _voice;

                CVoiceButton();
        };

        class CTextLog : public CText
        {
            private:                
                CVoiceButton    _btnVoice;
            public:
                CTextLog();

                void SetTextLog(string text, sf::SoundBuffer* voice);
                bool SetVoiceButton(const Object& json);

                virtual bool OnMouseMove(int x, int y);
                virtual bool OnLButtonDown(int x, int y);
                virtual bool OnLButtonUp(int x, int y);
                void OnCleanup();

                void Clean();
        };

        size_t                                  _logMax;
        size_t                                  _visNum;
        sf::Vector2f                            _logOffset;
        deque<pair<string, sf::SoundBuffer*> >  _logList;
        vector<CTextLog*>                       _textLogs;
        CScrollbar                              _scrollbar;
    protected:
        bool CheckList(const Object& json);
        bool SetProperty(const Object& json, bool isLoad = true);
    public:
        CLogBox();
        
        static CLogBox* Create(const char* filename);
        virtual bool OnRButtonDown(int x, int y);
        void OnCleanup();

        void AddLog(string text, const sf::SoundBuffer* voice);
        void SetValue(int val);
        void Show();
        void Hide();
        void CleanLogList();

        void PositiveOverflow();
        void NegativeOverflow();
};

#endif
