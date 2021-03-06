/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CCLASSFUNCOFACTION_H_
    #define _CCLASSFUNCOFACTION_H_

#include "CActionBaseClass.h"

template<class Tclass, typename Tresult>
class CClassFuncOfAction : public CActionBaseClass
{
    private:
        Tresult (Tclass::*_func)();
        Tclass*  _obj;
    protected:
    public:
        CClassFuncOfAction(Tclass* obj, Tresult (Tclass::*func)())
        {
            _obj = obj;
            _func = func;
        }

        bool OnLoop()
        {
            if (_func != 0 && _obj != 0){
                (_obj->*_func)();
            }
    
            return true;
        }
        
        virtual CActionBaseClass* Copy()
        {
            return new CClassFuncOfAction<Tclass, Tresult>(_obj, _func);
        }

        virtual inline EActType GetType() { return ACTION_CLASS_FUNC;}
};

#endif
