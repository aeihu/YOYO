/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CLOGBOXCONTROL_H_
    #define _CLOGBOXCONTROL_H_

#include "CLogBox.h"
#include "CControlOfImageBaseClass.h"

class CLogBoxControl : public CControlOfImageBaseClass
{
    private:
        friend class CResourceManager;

        map<string, CLogBox>    _logBoxList;

        CObject* GetObject(std::string name);
    public:
};

#endif
