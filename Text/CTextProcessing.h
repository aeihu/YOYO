/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CTEXTPROCESSING_H_
    #define _CTEXTPROCESSING_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../Graphics/CSurface.h"
#include "../Gui/CText.h"
#include "../Common/CCommon.h"

class CTextProcessing : public CText
{
    public:
        enum EStatus
        {
            RUNNING,
            FINISH,
            CONFIRMED,
        };
    private:
        bool                _isSkip;
        EStatus             _status;
        string              _text;
        string              _textOfShown;
        size_t              _rowWidth;
        size_t              _index;
        size_t              _length;
        unsigned long       _oldTime;

        bool isWordOrNumber(char c);
        void Process();
    public:
        CTextProcessing();

        void SetCharacterSize(size_t size);
        void SetRowWidth(size_t width);
        void OnLoop();
        void Skip();
        void Clear();
        void Confirm();

        virtual void SetString(string str);
        string GetText();
        float GetWidth();
        float GetHeight();
        sf::Vector2f GetLastCharacterPos();
        EStatus GetStatus() const;
};

#endif
