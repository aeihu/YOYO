/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include "CButtonBase.h"

using namespace std;

class CButton : public CButtonBase
{
    private:
        void Exec(void* data=NULL);
        bool Subclass_CheckList(map<string, string>& list);
        bool Subclass_SetProperty(map<string, string>& list);
    public:
        list<string>    _cmdList;
};

#endif