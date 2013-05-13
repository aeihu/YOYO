/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CMESSAGEBOXCONTROL_H_
    #define _CMESSAGEBOXCONTROL_H_

#include "CMessageBox.h"
#include "../Common/CControlBaseClass.h"
#include <map>
#include <string>

class CMessageBoxControl : public CControlBaseClass
{
    private:
        bool IsAlreadyExists(std::string name);
    public:
        CMessageBoxControl();
        map<string, CMessageBox>    _MessageBoxList;

        char AddMessageBox(std::string name, const char* filename);
        bool DelMessageBox(std::string name);
        bool SetImageVisibility(std::string name, int alpha, int incr, bool pause);
    
        void OnLoop(bool &pause);
        void OnRender(CWindow* Surf_Dest);
};

#endif
