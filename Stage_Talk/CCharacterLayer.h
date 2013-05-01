/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCHARACTERLAYER_H_
    #define _CCHARACTERLAYER_H_

#include "../Graphics/CImageBaseClass.h"
#include "../Common/CCommon.h"
#include <map>
#include <string>

using namespace std;

class CCharacterLayer : public CImageBaseClass
{
  private:
		sf::Vector2f								_offset;
		sf::Image										_imageFace;
		sf::Sprite									_spriteFace;
		map<string, string>					_faceList;
		bool												_isFaceEnable;

		bool CheckList(map<string, string> list);
		bool SetProperty(map<string, string> list);
		bool LoadImage(const char* FileName, sf::Image &image, sf::Sprite &sprite);
  public:
		//static map<string, CCharacterLayer>		CharacterLayerList;
		
		CCharacterLayer();
		CCharacterLayer(float x, float y);

		bool LoadChara(const char* FileName);
		bool SetFace(string name);

		bool Subclass_Loop();
		void Subclass_Render(sf::RenderWindow* Surf_Dest);
};
#endif
