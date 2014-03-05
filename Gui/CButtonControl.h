/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CButton.h"
#include "../Common/CControlBaseClass.h"

class CButtonControl : public CControlBaseClass
{
    private:
        bool IsAlreadyExists(string name);
    public:
        map<string, CButton>        _ButtonList;

        CButtonControl();

        char AddButton(string name, const char* filename);
        bool DelButton(string name);
        bool SetImageVisibility(string name, int alpha, int incr, bool pause);
    
        void OnLoop(bool &pause);
        void OnRender(sf::RenderWindow* Surf_Dest);
};
