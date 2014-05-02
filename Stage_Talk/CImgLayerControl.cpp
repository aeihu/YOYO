/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImgLayerControl.h"

bool CImgLayerControl::IsAlreadyExists(std::string name)
{
    return _imgLayerList.count(name) < 1 ? false : true;
}

bool CImgLayerControl::AddImage(std::string name, const char* filename, float x, float y)
{
    if (!IsAlreadyExists(name)){
        _imgLayerList.insert(
            std::pair<std::string,CImgLayer>(name, CImgLayer(x, y)));
    }
    else
        return false;

    if(_imgLayerList[name].LoadImg(filename)){
        _imgLayerList[name]._Alpha = 0;

        return true;
    }
    else{
        _imgLayerList.erase(name);
        return false;
    }
}

bool CImgLayerControl::DelImage(std::string name)
{
    if (IsAlreadyExists(name)){
        _imgLayerList.erase(name);
        return true;
    }
    else
        return false;
}

void CImgLayerControl::OnLoop(bool &pause)
{
    for (std::map<std::string, CImgLayer>::iterator it=_imgLayerList.begin(); 
        it !=_imgLayerList.end(); it++)
    {
        if((*it).second.OnLoop()) 
            pause=true;
    }
}

void CImgLayerControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (std::map<std::string, CImgLayer>::iterator it=_imgLayerList.begin(); 
        it!=_imgLayerList.end(); it++)
        (*it).second.OnRender(Surf_Dest);
}


CObject* CImgLayerControl::GetObject(std::string name)
{
    if (_imgLayerList.count(name) < 1)
        return NULL;

    return &_imgLayerList[name];
}

void CImgLayerControl::OnCleanup()
{
    _imgLayerList.clear();
}
