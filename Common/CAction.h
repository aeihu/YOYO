/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CACTION_H_
    #define _CACTION_H_

#include "CActionBaseClass.h"
#include "CCommon.h"

class CAction : public CActionBaseClass
{
    protected:
    public:
        CAction(float* val, float fin, float inc, bool pause=false);
        bool OnLoop();
    private:
        float*      _val;
        float       _valOfFinish;
        float       _incr;
};

#endif
