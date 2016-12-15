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
        CText               _speakerName;
        CTextProcessing     _textProcessor;
        CSequenceOfSprite   _frames;
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

        CTextProcessing::EStatus GetStatus() const;
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        bool OnRButtonDown(int x, int y);
        bool OnRButtonUp(int x, int y);
        void OnLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);
};
#endif
