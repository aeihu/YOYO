/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _COBJECTCONTROL_H_
    #define _COBJECTCONTROL_H_

#include "CObject.h"
#include <map>

using namespace std;

class CObjectControl
{
    protected:
        map<string, CObject*>          _objectList;
    public:
        virtual bool AddObject(string name, string objTypeName, string filename);
        virtual bool DelObject(string name);
        virtual void OnCleanup();

        virtual bool IsExists(string name);
        virtual CObject* GetObject(string name);
};

#endif