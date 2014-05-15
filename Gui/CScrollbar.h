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
        bool                    _isMouseDown;
        bool                    _isMouseOver;
        int                     _maxValue;

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

        int                     _value;
        int                     _alpha;
        float                   _height;
        sf::Vector2f            _coordinate;

        void OnMouseMove(int x, int y);
        bool OnLButtonDown(int x, int y);
        bool OnLButtonUp(int x, int y);
        bool SetMaxValue(int value);
        int GetValue() const;
        
        virtual bool CheckList(map<string, string>& list);
        virtual bool SetProperty(map<string, string>& list);
    public:
        CScrollbar();

        void OnLoop();
        void OnRender(sf::RenderWindow* Surf_Dest);
        void SetPosition(float x, float y);
};

#endif