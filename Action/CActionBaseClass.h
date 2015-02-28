/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CACTIONBASECLASS_H_
    #define _CACTIONBASECLASS_H_

#include <string>

using namespace std;

class CActionBaseClass
{
    protected:
        bool        _pause;
        bool        _skip;
    public:
        CActionBaseClass() {_skip = _pause = false;}

        virtual string GetName() const {return "";}; 
        virtual bool OnLoop(bool cleanup=true)=0; 
        virtual void OnCleanup(){}; 
        virtual bool IsPause() const {return _pause;} 
        void Skip() {_skip = true;}
};

#endif
