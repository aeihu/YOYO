/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CCLASSFUNCARGSOFACTION_H_
    #define _CCLASSFUNCARGSOFACTION_H_

#include "CActionBaseClass.h"

template<class T1, typename T2>
class CClassFuncArgsOfAction : public CActionBaseClass
{
    private:
        void (T1::*_func)(vector<T2>);
        
        T1*             _obj;
        vector<T2>      _args;
    protected:
    public:
        CClassFuncArgsOfAction(T1* obj, void (T1::*func)(vector<T2>), vector<T2> args)
        {
            _obj = obj;
            _func = func;
            _args = args;
        }

        bool OnLoop()
        {
            if (_func != 0 && _obj != 0){
                (_obj->*_func)(_args);
            }
    
            return true;
        }
        
        virtual CActionBaseClass* Copy()
        {
            return new CClassFuncArgsOfAction<T1, T2>(_obj, _func, _args);
        }

        virtual inline EActType GetType() { return ACTION_CLASS_FUNC_ARGS;}
};

#endif
