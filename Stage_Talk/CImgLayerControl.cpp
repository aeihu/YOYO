/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImgLayerControl.h"

bool CImgLayerControl::IsAlreadyExists(std::string name)
{
    return _ImgLayerList.count(name) < 1 ? false : true;
}

bool CImgLayerControl::AddImage(std::string name, const char* filename, float x, float y)
{
    if (!IsAlreadyExists(name)){
        _ImgLayerList.insert(
            std::pair<std::string,CImgLayer>(name, CImgLayer(x, y)));
    }
    else
        return false;

    if(_ImgLayerList[name].LoadImg(filename)){
        _ImgLayerList[name]._Alpha = 0;

        return true;
    }
    else{
        _ImgLayerList.erase(name);
        return false;
    }
}

bool CImgLayerControl::DelImage(std::string name)
{
    if (IsAlreadyExists(name)){
        _ImgLayerList.erase(name);
        return true;
    }
    else
        return false;
}

bool CImgLayerControl::SetImageVisibility(std::string name, int alpha, int incr, int msec, bool pause)
{
    if (IsAlreadyExists(name)){
        _ImgLayerList[name].Insert(0,
            alpha, msec, pause,
            &_ImgLayerList[name]._Alpha,
            incr);

        return true;
    }
    return false;
}

void CImgLayerControl::OnLoop(bool &pause)
{
    for (std::map<std::string, CImgLayer>::iterator it=_ImgLayerList.begin(); 
        it !=_ImgLayerList.end(); it++)
    {
        if((*it).second.OnLoop()) 
            pause=true;
    }
}

void CImgLayerControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (std::map<std::string, CImgLayer>::iterator it=_ImgLayerList.begin(); 
        it!=_ImgLayerList.end(); it++)
        (*it).second.OnRender(Surf_Dest);
}
