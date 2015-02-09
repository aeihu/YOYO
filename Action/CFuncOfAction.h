/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CFUNCOFACTION_H_
    #define _CFUNCOFACTION_H_

#include "CActionBaseClass.h"

class CFuncOfAction : public CActionBaseClass
{
    private:
        void (*_func)();
    protected:
    public:
        CFuncOfAction(void (*func)());
        bool OnLoop(bool cleanup=true);
};

#endif
