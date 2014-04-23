/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCONTROLBASECLASS_H_
    #define _CCONTROLBASECLASS_H_

#include <string>

class CControlOfImageBaseClass
{
    protected:
        friend bool Common_FuncOfShow(string funcName, CControlOfImageBaseClass* controlBase, vector<string> args);

        unsigned int _interval; // no used
        inline CControlOfImageBaseClass() {_interval = 10;} // no used
        virtual CImageBaseClass* GetObject(std::string name)=0;
    public:
        inline void SetInterval(unsigned int interval) {_interval = interval;} // no used
        virtual bool SetImageVisibility(std::string name, int alpha, int incr, bool pause)=0;
};

#endif