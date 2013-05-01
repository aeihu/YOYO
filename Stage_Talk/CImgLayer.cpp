/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImgLayer.h"
using namespace std;

CImgLayer::CImgLayer()
{
}

CImgLayer::CImgLayer(float x, float y):CImageBaseClass(x,y)
{
}

bool CImgLayer::ShowImg(const char* filename)
{
	if (!LoadImg(filename))
		return false;

	return true;
}

