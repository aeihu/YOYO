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

//bool CImgLayerControl::Move(string name, float x, float y, float increment, bool pause)
//{
//    if (_imgLayerList.count(name) < 1)
//        return false;
//
//    if (increment > -0.001f && increment < 0.001f)
//        increment = (float)CCommon::_Common.INCREMENT;
//
//    if (abs(_imgLayerList[name]._Coordinate.x-x) 
//        > abs(_imgLayerList[name]._Coordinate.y-y)){
//        float ratio = 1;
//        if (abs(_imgLayerList[name]._Coordinate.y-y) != 0){
//            ratio = abs(_imgLayerList[name]._Coordinate.y-y) / abs(_imgLayerList[name]._Coordinate.x-x);
//            _imgLayerList[name].Insert(0, y, pause, &_imgLayerList[name]._Coordinate.y, increment*ratio);
//        }
//        
//        _imgLayerList[name].Insert(0, x, pause, &_imgLayerList[name]._Coordinate.x, increment);
//    }
//    else if (abs(_imgLayerList[name]._Coordinate.x-x) 
//        < abs(_imgLayerList[name]._Coordinate.y-y)){
//        float ratio = 1;
//        if (abs(_imgLayerList[name]._Coordinate.x-x) != 0){
//            ratio = abs(_imgLayerList[name]._Coordinate.x-x) / abs(_imgLayerList[name]._Coordinate.y-y);
//            _imgLayerList[name].Insert(0, x, pause, &_imgLayerList[name]._Coordinate.x, increment*ratio);
//        }
//
//        _imgLayerList[name].Insert(0, y, pause, &_imgLayerList[name]._Coordinate.y, increment);
//    }
//    else{
//        _imgLayerList[name].Insert(0, x, pause, &_imgLayerList[name]._Coordinate.x, increment);
//        _imgLayerList[name].Insert(0, y, pause, &_imgLayerList[name]._Coordinate.y, increment);
//    }
//    return true;
//}

//bool CImgLayerControl::Show(string name, float x, float y, char type, float increment, bool pause, int alpha=255)
//{
//    CImgLayerControl::SetImageVisibility(name, alpha, __inc, pause);
//}

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


CImageBaseClass* CImgLayerControl::GetObject(std::string name)
{
    if (_imgLayerList.count(name) < 1)
        return NULL;

    return &_imgLayerList[name];
}

void CImgLayerControl::OnCleanup()
{
    _imgLayerList.clear();
}
