/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CMESSAGEBOX_H_
    #define _CMESSAGEBOX_H_

#include "../Gui/CBox.h"
#include "../Text/CTextProcessing.h"
#include <string>
#include <cstdio>
#include "../Common/CCommon.h"
#include "../Animation/CAnimation.h"
#include "../Graphics/CSequenceOfSprite.h"
#include "../Common/CResourceControl.h"

class CMessageBox : public CBox
{        
    private:
        class CSequenceFrames : public CSequenceOfSprite
        {
            public:
                using CSequenceOfSprite::LoadImg;
        }                   _frames;
        CText               _speakerName;
        CTextProcessing     _textProcessor;
        bool                _isFramesChanged;
        bool                _isUserWantToHideMsg;

        bool CheckList(const Object& json);
        bool SetProperty(const Object& json, bool isLoad = true);
        bool ConfirmForText();
        void SwitchForShowAndHide();
    protected:
    public:
        CMessageBox();
        
        static CMessageBox* Create(const char* filename);

        void ClearText();

        void SetText(string msg);
        void SetFont(string font);
        void SetSpeakerName(string name);

        string GetText();
        string GetSpeakerName();

        CTextProcessing::EStatus GetStatus() const;
        void OnLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);

        virtual bool OnLButtonDown(int x, int y);
        virtual bool OnRButtonUp(int x, int y);
};
#endif
