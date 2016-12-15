/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
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
        string  _scr;

        void Exec(void* data=NULL);
        bool CheckList(const Object& json);
        bool SetProperty(const Object& json, bool isLoad = true);
    public:
        static CButton* Create(const char* filename);
};

#endif