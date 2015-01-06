/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIMGLAYER_H_
    #define _CIMGLAYER_H_

#include "../Graphics/CImageBaseClass.h"

class CImgLayer : public CImageBaseClass
{
    public:
        CImgLayer();
        ~CImgLayer(){};
        CImgLayer(float x, float y);

        bool ShowImg(const char* filename);
};

#endif
