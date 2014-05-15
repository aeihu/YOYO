/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CBox.h"

CBox::CBox(float x, float y):CImageBaseClass(x,y)
{
}

CBox::~CBox()
{
}

bool CBox::CheckList(map<string, string>& list)
{
    bool __result = true;

    if (list.count("TILESET_PATH") < 1){
        cout << "can't find value of TILESET_PATH." << endl;
        __result = false;
    }

    if (list.count("TILE_ENABLE") < 1){
        cout << "can't find value of TILE_ENABLE." << endl;
        __result = false;
    }

    if (atoi(list["TILE_ENABLE"].c_str()) != 0){
        if (list.count("TILE_SIZE") < 1){
            cout << "can't find value of TILE_SIZE." << endl;
            __result = false;
        }

        if (list.count("MAP_PATH") < 1){
            cout << "can't find value of MAP_PATH." << endl;
            __result = false;
        }
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

bool CBox::SetProperty(map<string, string>& list)
{
    _Coordinate.x = atof(list["X"].c_str());
    _Coordinate.y = atof(list["Y"].c_str());

    sf::Image __tileset, __dest;
    if (!CSurface::OnLoad(list["TILESET_PATH"].c_str(), __tileset))
        return false;

    if (atoi(list["TILE_ENABLE"].c_str()) != 0){
        if (!CGuiCommon::CreateBoxBackground(
            &__dest, &__tileset, list["MAP_PATH"].c_str(), atoi(list["TILE_SIZE"].c_str())))
            return false;

        _image.loadFromImage(__dest);
    }
    else
        _image.loadFromImage(__tileset);

    _sprite.setTexture(_image);

    return true;
}
