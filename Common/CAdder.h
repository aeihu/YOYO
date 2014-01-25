/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
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
        unsigned int       _interval;
        unsigned long     _oldTime;
        char                  _type;
        bool                  _pause;

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


class CiAdder : public CAdder
{
    private:
        friend class     CAdderControl;
        int*                _pValue;
        int                 _goal;
        int                 _value1;
        int                 _value2;
        int                 _value3;
        int                 _value4;

        bool Check();
        bool Recursion();
        bool DecreaseRecursion();
    public:
        CiAdder(char type, int goal, bool pause, int* val, int val1, int val2=0, int val3=0, int val4=0);
};

class CfAdder : public CAdder
{
    private:
        friend class          CAdderControl;
        float*                  _pValue;
        float                   _goal;
        float                   _value1;
        float                   _value2;
        float                   _value3;
        float                   _value4;

        bool Check();
        bool Recursion();
        bool DecreaseRecursion();
        bool Oscillate();
    public:
        CfAdder(char type, float goal, bool pause, float* val, float val1, float val2=0.0f, float val3=0.0f, float val4=0.0f);
};


class CAdderControl
{
    private:
        std::list<CiAdder> _iAdderList;
        std::list<CfAdder> _fAdderList;

        bool IsAlreadyExists(int* pval);
        bool IsAlreadyExists(float* pval);
        void Delete(int* pval, bool isGoFinish);
        void Delete(float* pval, bool isGoFinish);
    protected:
        int OnLoop();
        unsigned int Count();
    public:
        void Insert(char type, int goal, bool pause, int* val, int val1, int val2=0, int val3=0, int val4=0, bool isGoFinish=true);
        void Insert(char type, float goal, bool pause, float* val, float val1, float val2=0.0f, float val3=0.0f, float val4=0.0f, bool isGoFinish=true);
        void Clear();
};

#endif
