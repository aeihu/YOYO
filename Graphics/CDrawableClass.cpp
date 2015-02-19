/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CDrawableClass.h"
#include "../Common/CResourceControl.h"

CDrawableClass::CDrawableClass()
{
    _layerOrder = 0;
}

unsigned char CDrawableClass::GetLayerOrder() const
{
    return _layerOrder;
}

void CDrawableClass::SetLayerOrder(char order)
{
    _layerOrder = order;
    CResourceControl::_ResourceManager._DrawableObjectControl._isNeedSort = true;
}

void CDrawableClass::SetLayerOrder(vector<string> args)
{
    if (args.size() > 0)
        SetLayerOrder((unsigned char)atoi(args[0].c_str()));
}

CActionTo* CDrawableClass::CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore, bool pause)
{
    return new CActionTo(&_alpha, elapsed, alpha, restore, pause);
}

CActionBy* CDrawableClass::CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore, bool pause)
{
    return new CActionBy(&_alpha, elapsed, alpha, restore, pause);
}

void CDrawableClass::OnSaveData(Object& json) const
{
    CBaiscProperties::OnSaveData(json);
    json << "layer_order" << _layerOrder;
    json << "alpha" << _alpha;
}
