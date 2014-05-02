/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CMESSAGEBOXCONTROL_H_
    #define _CMESSAGEBOXCONTROL_H_

#include "CMessageBox.h"
#include "../Common/CControlOfImageBaseClass.h"
#include <map>
#include <string>

class CMessageBoxControl : public CControlOfImageBaseClass
{
    private:
        friend class CResourceManager;
        friend bool Cmd_Message(vector<string> args);

        map<string, CMessageBox>    _messageBoxList;

        CObject* GetObject(std::string name);
    public:
        CMessageBoxControl();

        char AddMessageBox(std::string name, const char* filename);
        bool DelMessageBox(std::string name);
        
        bool OnLButtonUp(int mX, int mY);
        bool OnLButtonDown(int mX, int mY);
        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
};

#endif
