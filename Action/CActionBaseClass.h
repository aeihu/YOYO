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
            ACTION_CLASS_FUNC,
            ACTION_CLASS_FUNC_ARGS,
        };

        bool        _pauseRequest;
        bool        _skip;
    public:
        CActionBaseClass() {_skip = _pauseRequest = false;}

        virtual string GetName() const {return "";}; 
        virtual bool OnLoop(bool cleanup=true)=0; 
        virtual void OnCleanup(){}; 
        virtual bool PauseRequest() const {return _pauseRequest;} 
        void Skip() {_skip = true;}
        virtual CActionBaseClass* Copy()=0;
        virtual inline EActType GetType() { return ACTION_BASE;}
};

#endif
