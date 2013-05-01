/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CButton.h"

class CButtonControl
{
	private:
		bool IsExisted(string name);
	public:
		map<string, CButton>		_ButtonList;

		CButtonControl();

		char AddButton(string name, const char* filename);
		bool DelButton(string name);
		bool SetImageVisibility(string name, int alpha, int incr, int msec, bool pause);
	
		void OnLoop(bool &pause);
		void OnRender(sf::RenderWindow* Surf_Dest);
};
