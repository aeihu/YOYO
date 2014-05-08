/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSCROLLBAR_H_
    #define _CSCROLLBAR_H_

#include "CButtonBase.h"

class CScrollbar
{
    private:   
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

        bool                    _isMouseDown;
        bool                    _isMouseOver;
        int                     _maxValue;

    protected:
        int                     _value;
        float                   _height;
        sf::Vector2f            _coordinate;

        void OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        bool SetMaxValue(int value);
        int GetValue() const;
    public:
        CScrollbar();

        void OnLoop();
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();

        //virtual void RefOffset(int value)=0;
        void SetCoordinate(int x, int y);
};

#endif