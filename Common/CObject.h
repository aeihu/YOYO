/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _COBJECT_H_
    #define _COBJECT_H_

#include <string>

using namespace std;

class CObject
{
    protected:
        string      _fullFileName;
    public:
        inline CObject() {_fullFileName="";}
        inline string GetFullFileName() {return _fullFileName;}
};

#endif
