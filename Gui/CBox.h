/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBOX_H_
    #define _CBOX_H_

#include "../Graphics/CSurface.h"
#include "../Graphics/CImageBaseClass.h"
#include "../Common/CCommon.h"
#include "CGuiCommon.h"
#include "../Common/Cio.h"

class CBox : public CImageBaseClass
{
    private:
    protected:
        using CImageBaseClass::_visible;
        map<string, string>     _parameterList;

        bool CheckList(map<string, string>& list);
        virtual bool Sub_CheckList(map<string, string> list){ return true;}
        virtual bool Sub_OnLoad(){ return true;}
    public:
        CBox(float x=0.0f, float y=0.0f);
        ~CBox();

        bool LoadBox(const char* FileName);
};
#endif
