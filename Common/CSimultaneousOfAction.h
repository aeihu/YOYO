/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSIMULTANEOUSOFACTION_H_
    #define _CSIMULTANEOUSOFACTION_H_

#include "CActionSet.h"
#include <list>

using namespace std;

class CSimultaneousOfAction : public CActionSet
{
    private:
    protected:
    public:
        bool OnLoop();
};

#endif
