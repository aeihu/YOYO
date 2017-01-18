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
#include "CBox.h"

class CScrollbar : public CBox
{
    public:
        class CScrollbarCallback
        {
            public:
                virtual void PositiveOverflow() = 0;
                virtual void NegativeOverflow() = 0;
                virtual void SetValue(int val) = 0;
        };
    private:
        class CArrowUpButton : public CButtonBase
        {
            private:
                void Exec(void* data=NULL);
            public:
                using  CButtonBase::SetProperty;
        }                       _btnArrowUp;

        class CArrowDownButton : public CButtonBase
        {
            private:
                void Exec(void* data = NULL);
            public:
                using  CButtonBase::SetProperty;
        }                       _btnArrowDown;

        class CBarButton : public CButtonBase
        {
            private:
                void Exec(void* data = NULL);
            public:
                using  CButtonBase::SetProperty;
        }                       _btnBar;

        bool                    _isMouseDown;
        bool                    _isMouseOver;
        int                     _maxValue;
        int                     _value;
        float                   _incr;
        CScrollbarCallback*     _obj;

        void Ref();
    public:
        CScrollbar();

        virtual bool OnMouseWheel(int delta);
        
        virtual bool CheckList(const Object& json);
        virtual bool SetProperty(const Object& json, bool isLoad = true);

        bool SetMaxValue(int value);
        int GetValue() const;

        void SetValue(int val);
        bool Positive();
        bool Negative();

        void SetObjectForCallback(CScrollbarCallback* obj);
};

#endif
