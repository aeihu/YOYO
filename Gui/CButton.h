/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CBUTTON_H_
    #define _CBUTTON_H_

#include "CButtonBase.h"

using namespace std;

class CButton : public CButtonBase
{
    private:
        void Exec(void* data=NULL);
        bool CheckList(Object json);
        bool SetProperty(Object json, bool isLoad=true);
    public:
        list<string>    _cmdList;
        
        static CButton* Create(const char* filename);
};

#endif