/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CFUNCARGSOFACTION_H_
    #define _CFUNCARGSOFACTION_H_

#include "CActionBaseClass.h"

template<typename Targ, typename Tresult>
class CFuncArgsOfAction : public CActionBaseClass
{
    private:
        Tresult(*_func)(Targ);
        Targ _args;
    protected:
    public:
        CFuncArgsOfAction(Tresult (*func)(Targ), Targ args)
        {
            _func = func;
            _args = args;
        }

        bool OnLoop()
        {
            if (_func != 0){
                _func(_args);
            }

            return true;
        }

        virtual CActionBaseClass* Copy()
        {
            return new CFuncArgsOfAction<Targ, Tresult>(_func, _args);
        }

        virtual inline EActType GetType() { return ACTION_FUNC_ARGS; }
};

#endif
