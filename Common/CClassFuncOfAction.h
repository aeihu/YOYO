/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCLASSFUNCOFACTION_H_
    #define _CCLASSFUNCOFACTION_H_

#include "CActionBaseClass.h"

template<class T>
class CClassFuncOfAction : public CActionBaseClass
{
    private:
        void (T::*_func)();
        T* _obj;
    protected:
    public:
        CClassFuncOfAction(T* obj, void (T::*func)())
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
};

#endif
