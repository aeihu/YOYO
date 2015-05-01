/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CSCROLLBAR_H_
    #define _CSCROLLBAR_H_

#include "CButtonBase.h"

class CScrollbar : public CBox
{
    private:
        bool                    _isMouseDown;
        bool                    _isMouseOver;
        int                     _maxValue;
        int                     _value;
        float                   _height;

    protected:
        class CArrowUpButton : public CButtonBase
        {
            private:
                void Exec(void* data=NULL);
        }                       _btnArrowUp;

        class CArrowDownButton : public CButtonBase
        {
            private:
                void Exec(void* data=NULL);
        }                       _btnArrowDown;

        class CBarButton : public CButtonBase
        {
            private:
                void Exec(void* data=NULL);
        }                       _btnBar;

    public:
        CScrollbar();

        bool OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        
        virtual bool CheckList(Object json);
        virtual bool SetProperty(Object json, bool isLoad=true);
        void OnSubLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);

        bool SetMaxValue(int value);
        int GetValue() const;
        void SetValue(int val);
};

#endif
