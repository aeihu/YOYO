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

template<typename Tresult>
class CFuncOfAction : public CActionBaseClass
{
    private:
        Tresult (*_func)();
    protected:
    public:
        CFuncOfAction(Tresult (*func)())
        {
            _func = func;
        }

        bool OnLoop()
        {
            if (_func != 0){
                _func();
            }

            return true;
        }

        virtual CActionBaseClass* Copy()
        {
            return new CFuncOfAction<Tresult>(_func);
        }

        virtual inline EActType GetType() { return ACTION_FUNC;}
};

#endif
