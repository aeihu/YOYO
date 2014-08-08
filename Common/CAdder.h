/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CADDER_H_
    #define _CADDER_H_

#include <list>
#include <cmath>
#include "CCommon.h"

#define PI 3.14159265358979323846

class CAdder
{
    private:
    protected:
        size_t                  _interval;
        unsigned long           _oldTime;
        char                    _type;
        bool                    _pause;

        virtual bool  Check()=0;
        virtual bool  Recursion()=0;
        virtual bool  DecreaseRecursion()=0;
        virtual bool  Oscillate();
    public:
        CAdder();
        virtual ~CAdder();
        bool Exec(unsigned long time);
        bool IsPause();
};

class CfAdder : public CAdder
{
    private:
        friend class            CAdderControl;
        float*                  _pFloat;
        int*                    _pInt;
        float                   _value;
        float                   _goal;
        float                   _par1;
        float                   _par2;
        float                   _par3;
        float                   _par4;

        void SetValue(float val);
        bool Check();
        bool Recursion();
        bool DecreaseRecursion();
        bool Oscillate();
    public:
        CfAdder(char type, float goal, bool pause, float* val, float val1, float val2=0.0f, float val3=0.0f, float val4=0.0f);
        CfAdder(char type, float goal, bool pause, int* val, float val1, float val2=0.0f, float val3=0.0f, float val4=0.0f);
};


class CAdderControl
{
    private:
        std::list<CfAdder> _fAdderList;

        bool IsAlreadyExists(int* pval);
        bool IsAlreadyExists(float* pval);
        void Delete(int* pval, bool isGoFinish);
        void Delete(float* pval, bool isGoFinish);
    protected:
        int OnLoop();
        size_t Count();
    public:
        void Insert(char type, float goal, bool pause, int* val, float val1, float val2=0.0f, float val3=0.0f, float val4=0.0f, bool isGoFinish=true);
        void Insert(char type, float goal, bool pause, float* val, float val1, float val2=0.0f, float val3=0.0f, float val4=0.0f, bool isGoFinish=true);
        void Clear();
};

#endif
