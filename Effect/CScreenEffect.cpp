/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CScreenEffect.h"

void CScreenEffect::SetShow()
{
    _visible = true;
}
        
void CScreenEffect::SetHide()
{
    _visible = false;
}

CSimultaneousOfAction* CScreenEffect::CreateActionLouver(size_t elapsed, bool L2R, bool slide)
{
    size_t __count = _vertexData.size() >> 1;
    size_t __t = slide ? elapsed / ((__count>>1)+8) : elapsed;
    size_t __index = 0;
    float __alpha = _visible ? 0.0f : 255.0f;
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    
    if (!_visible && __count > 0)
        __result->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetShow));

    for (size_t i=0; i<__count; i++){
        __index = L2R ? i<<1 : (__count-i-1)<<1;

        CSimultaneousOfAction* __sim = new CSimultaneousOfAction();
        CSequenceOfAction* __seq = new CSequenceOfAction();
        
        if (slide){
            size_t __times = i>>1;
            if (__t*__times>0){
                __seq->AddAction(new CDeplayOfAction(__t*__times));
            }
        }

        __sim->AddAction(new CActionTo(&_vertexData[__index]._alpha, (i%2==0)?__t:__t<<3, __alpha));
        __sim->AddAction(new CActionTo(&_vertexData[__index+1]._alpha, (i%2==0)?__t:__t<<3, __alpha));
        __seq->AddAction(__sim);
        
        if (_visible && i == __count-1)
            __seq->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetHide));

        __result->AddAction(__seq);

    }
    return __result;
}

CSimultaneousOfAction* CScreenEffect::CreateActionLeftToRight(size_t elapsed, bool L2R)
{
    size_t __count = _vertexData.size() >> 1; // __count mean's how many point in line
    size_t __t = elapsed / ((__count>>1)+8); // how long each of timepoint
    size_t __index = 0;
    float __alpha = _visible ? 0.0f : 255.0f;
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    
    if (!_visible && __count > 0)
        __result->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetShow));

    for (size_t i=0; i<__count; i++){
        __index = L2R ? i<<1 : (__count-i-1)<<1;

        CSimultaneousOfAction* __sim = new CSimultaneousOfAction();
        CSequenceOfAction* __seq = new CSequenceOfAction();

        size_t __times = ((i+1)>>1);
        if ((__t)*__times > 0){
            __seq->AddAction(new CDeplayOfAction((__t)*__times));
        }
        __sim->AddAction(new CActionTo(&_vertexData[__index]._alpha, __t<<3, __alpha));
        __sim->AddAction(new CActionTo(&_vertexData[__index+1]._alpha, __t<<3, __alpha));
        __seq->AddAction(__sim);

        if (_visible && i == __count-1)
            __seq->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetHide));

        __result->AddAction(__seq);
    }
    return __result;
}

CScreenEffect::PData::PData()
{
    _alpha = _y = _x = 0.0f;
    _alpha = 255.0f;
}

void CScreenEffect::OnInit(size_t num, float distance, float height)
{
    num *= 4;

    _vertexArray.resize(num);
    _vertexData.resize(num);
    _vertexArray.setPrimitiveType(sf::Quads);
    for (size_t i=0; i<num; i++){
        _vertexData[i]._x = ((i+2)>>2)*distance;
        _vertexData[i]._y = (i>>1)%2 == i%2 ? 0:height;
        _vertexArray[i].color = sf::Color::White;
    }
}

void CScreenEffect::OnLoop()
{
    if (!_visible)
        return;

    for (size_t i=0; i<_vertexArray.getVertexCount(); i++){
        if (_vertexArray[i].position.x != _vertexData[i]._x)
            _vertexArray[i].position.x = _vertexData[i]._x;
        
        if (_vertexArray[i].position.y != _vertexData[i]._y)
            _vertexArray[i].position.y = _vertexData[i]._y;
        
        if (_vertexArray[i].color.a != (sf::Uint8)_vertexData[i]._alpha)
            _vertexArray[i].color.a = (sf::Uint8)_vertexData[i]._alpha;
    }
}

void CScreenEffect::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_visible)
        Surf_Dest->draw(_vertexArray);
}