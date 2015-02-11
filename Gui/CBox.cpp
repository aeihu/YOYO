/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CBox.h"

CBox::CBox(float x, float y):CImgLayer(x,y)
{
}

CBox::~CBox()
{
}

bool CBox::CheckList(Object json)
{
    bool __result = true;

    if (!json.has<String>("TILESET_PATH")){
        cout << "can't find value of TILESET_PATH." << endl;
        __result = false;
    }

    if (json.has<Boolean>("TILE_ENABLE")){
        if (json.get<Boolean>("TILE_ENABLE")){
            if (!json.has<Number>("TILE_SIZE")){
                cout << "can't find value of TILE_SIZE." << endl;
                __result = false;
            }

            if (!json.has<String>("MAP_PATH")){
                cout << "can't find value of MAP_PATH." << endl;
                __result = false;
            }
        }
    }
    else{
        cout << "can't find value of TILE_ENABLE." << endl;
        __result = false;
    }

    if (!json.has<Number>("X")){
        cout << "can't find value of X." << endl;
        __result = false;
    }

    if (!json.has<Number>("Y")){
        cout << "can't find value of Y." << endl;
        __result = false;
    }

    return __result;
}

bool CBox::SetProperty(Object json)
{
    SetPosition(json.get<Number>("X"), json.get<Number>("Y"));

    sf::Image __tileset, __dest;
    if (!CSurface::OnLoad(json.get<String>("TILESET_PATH").c_str(), __tileset))
        return false;

    if (json.get<Boolean>("TILE_ENABLE")){
        if (!CGuiCommon::CreateBoxBackground(
            &__dest, &__tileset, json.get<String>("MAP_PATH").c_str(), json.get<Number>("TILE_SIZE")))
            return false;

        _image.loadFromImage(__dest);
    }
    else
        _image.loadFromImage(__tileset);

    _sprite.setTexture(_image);

    return true;
}
