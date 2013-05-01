/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIMGLAYERCONTROL_H_
    #define _CIMGLAYERCONTROL_H_

#include "CImgLayer.h"
#include "../Common/CAdder.h"
#include <map>
#include <string>

class CImgLayerControl
{
	private:
		bool IsExisted(std::string name);
	public:
    std::map<std::string, CImgLayer>	_ImgLayerList;

		bool AddImage(std::string name, const char* filename, float x, float y);
		bool SetImageVisibility(std::string name, int alpha, int incr, int msec, bool pause);

		void OnLoop(bool &pause);
		void OnRender(sf::RenderWindow* Surf_Dest);
};

#endif
