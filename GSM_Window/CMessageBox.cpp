/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CMessageBox.h"

using namespace std;

CMessageBox::CMessageBox()
{
//	_speakerName("");
	TilesetOfCursor = 
	SizeOfCursor = 0;
	_isPaused = false;
}

bool CMessageBox::Sub_OnLoad()
{
	if (!CTextProcessing::OnInit(
		_sprite.GetSize().x - atof(_parameterList["MSG_OFFSET_X"].c_str()) * 2))
		return false;
	return true;
}

bool CMessageBox::Sub_CheckList(map<string, string> list)
{
	bool result = true;

	if (list.count("MSG_OFFSET_X") < 1){
		cout << "can't find value of MSG_OFFSET_X." << endl;
		result = false;
	}

	if (list.count("MSG_OFFSET_Y") < 1){
		cout << "can't find value of MSG_OFFSET_X." << endl;
		result = false;
	}

	if (list.count("MSG_APPEND") < 1){
		cout << "can't find value of MSG_APPEND." << endl;
		result = false;
	}

	return result;
}

bool CMessageBox::Subclass_Loop()
{
	_speakerName.SetPosition(CCommon::common.MSGBOX_SPEAKER_OFFSET_X, CCommon::common.MSGBOX_SPEAKER_OFFSET_Y);
	CTextProcessing::SetPosition(
		_Coordinate.x + atof(_parameterList["MSG_OFFSET_X"].c_str()), 
		_Coordinate.y + atof(_parameterList["MSG_OFFSET_Y"].c_str()));

	CTextProcessing::OnLoop();
	return _isPaused || !IsTextAllShown();
}

void CMessageBox::Subclass_Render(sf::RenderWindow* Surf_Dest)
{
	Surf_Dest->Draw(_speakerName);
	CTextProcessing::OnRender(Surf_Dest);
}

void CMessageBox::SetSpeakerName(string name)
{
	_speakerName.SetText(name.c_str());
}

void CMessageBox::SetText(string msg)
{
	_isPaused = true;
	CTextProcessing::SetText(msg, atoi(_parameterList["MSG_APPEND"].c_str()));
}

bool CMessageBox::OnLButtonDown(int x, int y)
{
	if (IsTextAllShown())
		_isPaused = false;
	else
		Skip();

	return true;
}

bool CMessageBox::OnLButtonUp(int x, int y)
{
	return true;
}

bool CMessageBox::OnRButtonDown(int x, int y)
{
	return true;
}

bool CMessageBox::OnRButtonUp(int x, int y)
{
	return true;
}
