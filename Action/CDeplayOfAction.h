/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CDEPLAYOFACTION_H_
    #define _CDEPLAYOFACTION_H_

#include "CActionBaseClass.h"
#include "../Common/CCommon.h"

class CDeplayOfAction : public CActionBaseClass
{
    private:
        bool            _isRunning;
        unsigned long   _time;
        size_t          _delay;
    public:
        CDeplayOfAction(size_t delay, bool pause=false);

        bool PauseRequest() const;
        bool OnLoop();
        virtual CActionBaseClass* Copy();

        virtual inline EActType GetType() { return ACTION_DEPLY;}
};

#endif
