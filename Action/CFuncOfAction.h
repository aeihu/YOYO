/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
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
        bool OnLoop();
        virtual CActionBaseClass* Copy();
        virtual inline EActType GetType() { return ACTION_FUNC;}
};

#endif
