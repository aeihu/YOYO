/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CACTIONBASECLASS_H_
    #define _CACTIONBASECLASS_H_

#include <string>

using namespace std;

class CActionBaseClass
{
    protected:
        enum EActType{
            ACTION_BASE,
            ACTION_BY,
            ACTION_TO,
            ACTION_SET,
            ACTION_SEQ,
            ACTION_SIM,
            ACTION_REP,
            ACTION_DEPLY,
            ACTION_FUNC,
            ACTION_FUNC_ARGS,
            ACTION_CLASS_FUNC,
            ACTION_CLASS_FUNC_ARGS,
        };

        bool        _skip;
        string      _name;
    public:
        CActionBaseClass();
        ~CActionBaseClass();
        
        virtual string GetName() const;
        void SetName(string name);
        virtual bool OnLoop()=0; 
        virtual void OnCleanup(){}; 
        void Skip();
        virtual CActionBaseClass* Copy()=0;
        virtual inline EActType GetType() { return ACTION_BASE; }
};

#endif
