/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CBox.h"

CBox::CBox()
{
	_parameterList.clear();
}

CBox::CBox(float x, float y):CImageBaseClass(x,y)
{
	_parameterList.clear();
}

//bool CBox::IsEventEnable()
//{
//	//if (CAnimationEffects_Move::GetAnimateState() != 1 && 
//	//	Surf_Show->format->alpha != 255)
//	//	return false;
//
//	return true;
//}

bool CBox::LoadBox(const char* FileName)
{	
	//char BOM[3] = {0xEF,0xBB,0xBF};
	list<string> __expressions = Cio::LoadTxtFile(FileName, "\r\n");
	//map<string, string> __valueList;
	_parameterList.clear();

	for (list<string>::iterator it=__expressions.begin();
		it!=__expressions.end(); it++){
		string __paraName = "";
		string __paraValue = "";
		if(Cio::AnalyticExpression((*it), __paraName, __paraValue))
			_parameterList[__paraName] = __paraValue;
	}

	if (!CheckList(_parameterList))
		return false;

	_Coordinate.x = atof(_parameterList["X"].c_str());
	_Coordinate.y = atof(_parameterList["Y"].c_str());

	sf::Image Surf_tileset;
	if (!CSurface::OnLoad(_parameterList["TILESET_PATH"].c_str(), Surf_tileset))
		return false;

	if (!CGuiCommon::CreateBoxBackground(
		&_image, &Surf_tileset, _parameterList["MAP_PATH"].c_str(), atoi(_parameterList["TILE_SIZE"].c_str())))
		return false;

	_sprite.SetImage(_image);

	return Sub_OnLoad();
}

bool CBox::CheckList(map<string, string> list)
{
	bool __result = true;
	__result = Sub_CheckList(list);

	if (list.count("TILESET_PATH") < 1){
		cout << "can't find value of TILESET_PATH." << endl;
		__result = false;
	}

	if (list.count("MAP_PATH") < 1){
		cout << "can't find value of MAP_PATH." << endl;
		__result = false;
	}

	if (list.count("TILE_SIZE") < 1){
		cout << "can't find value of TILE_SIZE." << endl;
		__result = false;
	}

	if (list.count("X") < 1){
		cout << "can't find value of X." << endl;
		__result = false;
	}

	if (list.count("Y") < 1){
		cout << "can't find value of Y." << endl;
		__result = false;
	}

	return __result;
}

//bool CBox::OnLoop()
//{
//	bool __result = CAdderControl::OnLoop();
//	_visible = _Alpha > 0 ? true : false;
//	if (!_visible) return false;
//
//	if (_Alpha > 255)
//		_Alpha = 255;
//	else if (_Alpha < 0)
//		_Alpha = 0;
//
//	if (_sprite.GetColor().a != _Alpha)
//		_sprite.SetColor(sf::Color(255,255,255,_Alpha));
//
//	if (_Coordinate != _sprite.GetPosition())
//		_sprite.SetPosition(_Coordinate);
//
//	if (_sprite.GetScale().x > 1.0f || _sprite.GetScale().y > 1.0f)
//		_image.SetSmooth(true);
//	else
//		_image.SetSmooth(false);
//
//	Subclass_Loop();
//	return __result;
//}
//
//void CBox::OnRender(sf::RenderWindow* Surf_Dest)
//{
//	if (!_visible) return;
//	Surf_Dest->Draw(_sprite);
//	Subclass_Render(Surf_Dest);
//}

//void CBox::Show(bool* target)
//{
//	if (_Visible)
//		return;
//
//	_Visible = true;
//}
//
//void CBox::Hide(bool* target)
//{
//	if (!_Visible)
//		return;
//}

//void CBox::SetPosition(float x, float y)
//{
//	_Coordinate.x = x;
//	_Coordinate.y = y;
//	_sprite.SetPosition(_Coordinate);
//}
