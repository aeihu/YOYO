/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CMESSAGEBOX_H_
    #define _CMESSAGEBOX_H_

#include "../Gui/CBox.h"
#include "../Text/CTextProcessing.h"
#include <string>
#include <cstdio>
#include "../Common/CCommon.h"
#include "../Animation/CAnimation.h"

class CMessageBox : public CBox , public CTextProcessing
{        
  private:        
		int						TilesetOfCursor;
		int						SizeOfCursor;
		sf::String		_speakerName;
		bool					_isPaused;

		bool Sub_CheckList(map<string, string> list);
		bool Sub_OnLoad();
		bool Subclass_Loop();
		void Subclass_Render(sf::RenderWindow* Surf_Dest);
  public:
    CMessageBox();

		void SetText(string msg);
		void OnMouseMove(int x, int y);
		bool OnLButtonDown(int x, int y);
		bool OnLButtonUp(int x, int y);
		bool OnRButtonDown(int x, int y);
		bool OnRButtonUp(int x, int y);
		void SetSpeakerName(string name);
};
#endif