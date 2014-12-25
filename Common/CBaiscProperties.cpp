/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CBaiscProperties.h"
#include "CCommon.h"

float& CBaiscProperties::GetRotation()
{
    return _rotation;
}

void CBaiscProperties::SetRotation(float r)
{
    _rotation = r;
}

sf::Vector2f& CBaiscProperties::GetPosition() 
{
    return _coordinate;
}

void CBaiscProperties::SetPosition(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}

sf::Vector2f& CBaiscProperties::GetOffset()
{
    return _offset;
}

void CBaiscProperties::SetOffset(float x, float y)
{
    _offset.x = x;
    _offset.y = y;
}

void CBaiscProperties::SetOffsetX(float x)
{
    _offset.x = x;
}

void CBaiscProperties::SetOffsetY(float y)
{
    _offset.y = y;
}

void CBaiscProperties::SetScale(float x, float y)
{
    _scale.x = x;
    _scale.y = y;
}

void CBaiscProperties::SetScaleX(float x)
{
    _scale.x = x;
}

void CBaiscProperties::SetScaleY(float y)
{
    _scale.y = y;
}
        
sf::Vector2f& CBaiscProperties::GetScale()
{
    return _scale;
}

bool CBaiscProperties::OnLoop()
{
    bool __isPause = false;
    for (list<CActionBaseClass*>::iterator it=_actList.begin();it!=_actList.end(); ){
        if ((*it)->OnLoop()){
            delete (*it);
            (*it) = NULL;
            it=_actList.erase(it);
            if (it == _actList.end())
                break;
        }
        else{
            __isPause = (*it)->IsPause() ? true : __isPause;
            ++it;
        }
    }

    //for (size_t i=_actList.size(); i>0; i--){
    //    if (_actList[i-1]->OnLoop()){
    //        delete _actList[i-1];
    //        _actList[i-1] = NULL;
    //        _actList.erase(_actList.begin()+(i-1));
    //    }
    //
    //}

    return _actList.empty() ? false : __isPause;
}

bool CBaiscProperties::AddAction(CActionBaseClass* act)
{
    if (!act)
        return false;

    _actList.push_back(act);
    return true;
}

bool CBaiscProperties::AddAction(float* val, size_t elapsed, float fin, bool pause, bool reset)
{
    if (val){
        CSequenceOfAction* __acts = new CSequenceOfAction();
        if (reset) elapsed = elapsed >> 2;
        if (elapsed == 0) elapsed = 1;
        float __tmpVal = *val;

        float __inc = (fin - *val) * ((1000.0f/(float)CCommon::_Common.MAX_FPS)/(float)elapsed);

        if (__inc < -0.000001f || __inc > 0.000001f){
            __acts->AddAction(new CAction(val, fin, __inc, pause));

            if (reset) __acts->AddAction(new CAction(val, __tmpVal, __inc, pause));

            _actList.push_back(__acts);
        }

        return true;
    }

    return false;
}

//bool CBaiscProperties::AddAction(int* val, size_t elapsed, int fin)
//{
//    if (val){
//        int __inc = (fin - *val) * ((1000/CCommon::_Common.MAX_FPS)/elapsed);
//        _actList.push_back(new CAction(val, fin, __inc));
//        return true;
//    }
//
//    return false;
//}

bool CBaiscProperties::AddActionOfRotation(size_t elapsed, float rotation, bool pause, bool reset)
{
    return AddAction(&_rotation, elapsed, rotation, pause, reset);
}

bool CBaiscProperties::AddActionOfScale(size_t elapsed, float x, float y, bool pause, bool reset)
{
    return AddAction(&_scale.x, elapsed, x, pause, reset) && 
        AddAction(&_scale.y, elapsed, y, pause, reset);
}

bool CBaiscProperties::AddActionOfScaleX(size_t elapsed, float x, bool pause, bool reset)
{
    return AddAction(&_scale.x, elapsed, x, pause, reset);
}

bool CBaiscProperties::AddActionOfScaleY(size_t elapsed, float y, bool pause, bool reset)
{
    return AddAction(&_scale.y, elapsed, y, pause, reset);
}

bool CBaiscProperties::AddActionOfMove(size_t elapsed, float x, float y, bool pause, bool reset)
{
    return AddAction(&_coordinate.x, elapsed, x, pause, reset) && 
        AddAction(&_coordinate.y, elapsed, y, pause, reset);
}


bool CBaiscProperties::AddActionOfMoveX(size_t elapsed, float x, bool pause, bool reset)
{
    return AddAction(&_coordinate.x, elapsed, x, pause, reset);
}

bool CBaiscProperties::AddActionOfMoveY(size_t elapsed, float y, bool pause, bool reset)
{
    return AddAction(&_coordinate.y, elapsed, y, pause, reset);
}

void CBaiscProperties::OnSaveData(Object& json) const
{
    CObject::OnSaveData(json);
    json << "x" << _coordinate.x;
    json << "y" << _coordinate.y;
    json << "offset_x" << _offset.x;
    json << "offset_y" << _offset.y;
    json << "scale_x" << _scale.x;
    json << "scale_y" << _scale.y;
    json << "rotation" << _rotation;
}
