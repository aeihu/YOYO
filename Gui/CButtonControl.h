/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBUTTONCONTROL_H_
    #define _CBUTTONCONTROL_H_

#include "CButton.h"
#include "../Common/CControlOfImageBaseClass.h"

class CButtonControl : public CControlOfImageBaseClass
{
    private:
        friend class CResourceManager;

        CObject* GetObject(std::string name);
        map<string, CButton>        _buttonList;
    public:
        CButtonControl();

        char AddButton(string name, const char* filename);
        bool DelButton(string name);

        void OnMouseMove(int mX, int mY);
        bool OnLButtonUp(int mX, int mY);
        bool OnLButtonDown(int mX, int mY);
        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
};

#endif
