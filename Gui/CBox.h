/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBOX_H_
    #define _CBOX_H_

#include "../Graphics/CSurface.h"
#include "../Common/CCommon.h"
#include "CGuiCommon.h"
#include "../Common/CConfigFile.h"
#include "../Stage_Talk/CImgLayer.h"

class CBox : public CImgLayer
{
    private:
    protected:
        using CImageBaseClass::_visible;

        virtual bool CheckList(Object json);
        virtual bool SetProperty(Object json);
    public:
        CBox(float x=0.0f, float y=0.0f);
        ~CBox();
};
#endif
