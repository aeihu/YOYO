/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CDEPLAYOFACTION_H_
    #define _CDEPLAYOFACTION_H_

#include "CActionBaseClass.h"
#include "CCommon.h"

class CDeplayOfAction : public CActionBaseClass
{
    private:
        bool            _isRunning;
        unsigned long   _time;
        size_t          _delay;
    public:
        CDeplayOfAction(size_t delay);
        
        bool OnLoop(bool cleanup=true);
};

#endif
