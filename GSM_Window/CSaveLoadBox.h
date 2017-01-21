/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CSAVELOADBOX_H_
    #define _CSAVELOADBOX_H_

#include "../Gui/CScrollbar.h"
#include "../Gui/CButtonBase.h"
#include "../Gui/CBox.h"

class CSaveLoadBox : public CBox
{
    private:
        class CSaveCell : public CButtonBase
        {
            private:
                CImgLayer   _img;
            protected:
                bool CheckList(const Object& json);
                bool SetProperty(const Object& json, bool isLoad = true);
            public:
                virtual bool OnMouseMove(int x, int y);
                virtual bool OnLButtonDown(int x, int y);
                virtual bool OnLButtonUp(int x, int y);
        };

        size_t          _logMax;
        size_t          _visNum;
        sf::Vector2f    _logOffset;
        CScrollbar      _scrollbar;
    protected:
        bool CheckList(const Object& json);
        bool SetProperty(const Object& json, bool isLoad = true);
    public:
};
#endif