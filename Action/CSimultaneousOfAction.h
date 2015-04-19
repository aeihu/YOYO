/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
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
        virtual bool IsPause() const;
        bool OnLoop(bool cleanup=true);
        virtual CActionBaseClass* Copy();
        virtual inline EActType GetType() { return ACTION_SIM;}
};

#endif
