/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/


#ifndef _CSEQUENCEOFACTION_H_
    #define _CSEQUENCEOFACTION_H_

#include "CActionTo.h"
#include <list>
#include "CActionSet.h"

using namespace std;

class CSequenceOfAction : public CActionSet
{
    protected:
    public:
        bool PauseRequest() const;
        bool OnLoop(bool cleanup=true);
        virtual CActionBaseClass* Copy();
        virtual inline EActType GetType() { return ACTION_SEQ;}
};

#endif
