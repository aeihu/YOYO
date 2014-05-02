/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCONTROLBASECLASS_H_
    #define _CCONTROLBASECLASS_H_

#include "CObject.h"

class CControlBaseClass
{
    protected:
        virtual CObject* GetObject(std::string name)=0;
    public:
        bool IsExists(string name);
};

#endif