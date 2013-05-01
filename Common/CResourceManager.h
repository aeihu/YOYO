/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CRESOURCEMANAGER_H_
    #define _CRESOURCEMANAGER_H_

#include "../Stage_Talk/CImgLayerControl.h"
#include "../Stage_Talk/CCharacterLayerControl.h"
#include "../GSM_Window/CMessageBoxControl.h"
#include "../Gui/CButtonControl.h"

class CResourceManager
{
	public:
		static CCharacterLayerControl _CharacterLayerControl;
		static CImgLayerControl	_ImgLayerControl;
		static CImgLayerControl	_BackgroundLayerControl;
		static CMessageBoxControl	_MessageBoxControl;
		static CButtonControl _ButtonControl;
};

#endif
