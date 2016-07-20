/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CScreenEffect.h"

CScreenEffect::CScreenEffect()
{
    _red = _green = _blue = 0.0f;
}

bool CScreenEffect::GetVisible() const
{
    return _isShowed;
}

void CScreenEffect::SetShow()
{
    _isShowed = true;
}
        
void CScreenEffect::SetHide()
{
    _isShowed = false;
}

void CScreenEffect::SetColor(vector<string> args)
{
    if (args.size() > 2){
        int __r = atoi(args[0].c_str());
        int __g = atoi(args[1].c_str());
        int __b = atoi(args[2].c_str());

        if (__r > 255) __r = 255;
        if (__g > 255) __r = 255;
        if (__b > 255) __r = 255;

        for (size_t i=0; i<_vertexArray.getVertexCount(); i++){
            if (__r >=0 ) _vertexArray[i].color.r = __r;
            if (__g >=0 ) _vertexArray[i].color.g = __g;
            if (__b >=0 ) _vertexArray[i].color.b = __b;
        }
    }
}

CSimultaneousOfAction* CScreenEffect::CreateActionShowOrHide(size_t elapsed, bool isShow)
{
    float __alpha = isShow ? 255.0f : 0.0f;
    CSimultaneousOfAction* __result = new CSimultaneousOfAction("");
    
    if (isShow && _vertexArray.getVertexCount() > 0)
        __result->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetShow));

    for (size_t i=0; i<_vertexArray.getVertexCount(); i++){
        if (!isShow && i == _vertexArray.getVertexCount()-1){
            CSequenceOfAction* __seq = new CSequenceOfAction();
            __seq->AddAction(new CActionTo(&_vertexData[i]._alpha, elapsed, __alpha));
            __seq->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetHide));
            __result->AddAction(__seq);
        }
        else
            __result->AddAction(new CActionTo(&_vertexData[i]._alpha, elapsed, __alpha));
    }
    return __result;
}

CSimultaneousOfAction* CScreenEffect::CreateActionLouver(size_t elapsed, bool isShow, bool L2R, bool slide)
{
    size_t __count = _vertexData.size() >> 1;
    size_t __t = slide ? elapsed / ((__count>>1)+8) : elapsed;
    size_t __index = 0;
    size_t __incr = 0;
    float __alpha = isShow ? 255.0f : 0.0f;
    CSimultaneousOfAction* __result = new CSimultaneousOfAction("");
    
    if (isShow && __count > 0)
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

        __incr = slide ? ((i%2==0)?__t:__t<<3) : ((i%2==0)?__t>>3:__t);
        __sim->AddAction(new CActionTo(&_vertexData[__index]._alpha, __incr, __alpha));
        __sim->AddAction(new CActionTo(&_vertexData[__index+1]._alpha, __incr, __alpha));
        __seq->AddAction(__sim);
        
        if (!isShow && i == __count-1)
            __seq->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetHide));

        __result->AddAction(__seq);

    }
    return __result;
}

CSimultaneousOfAction* CScreenEffect::CreateActionGradient(size_t elapsed, bool isShow, bool L2R)
{
    size_t __count = _vertexData.size() >> 1; // __count mean's how many point in line
    size_t __t = elapsed / ((__count>>1)+8); // how long each of timepoint
    size_t __index = 0;
    float __alpha = isShow ? 255.0f : 0.0f;
    CSimultaneousOfAction* __result = new CSimultaneousOfAction("");
    
    if (isShow && __count > 0)
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

        if (!isShow && i == __count-1)
            __seq->AddAction(new CClassFuncOfAction<CScreenEffect>(this, &CScreenEffect::SetHide));

        __result->AddAction(__seq);
    }
    return __result;
}

void CScreenEffect::CreateActionShowOrHideForSelf(size_t elapsed, bool isShow)
{
    _actionList.AddAction(CreateActionShowOrHide(elapsed, isShow));
}

void CScreenEffect::CreateActionGradientForSelf(size_t elapsed, bool isShow, bool L2R)
{
    _actionList.AddAction(CreateActionGradient(elapsed, isShow, L2R));
}

void CScreenEffect::CreateActionLouverForSelf(size_t elapsed, bool isShow, bool L2R, bool slide)
{
    _actionList.AddAction(CreateActionLouver(elapsed, isShow, L2R, slide));
}

CScreenEffect::PData::PData()
{
    _alpha = _y = _x = 0.0f;
    _alpha = 255.0f;
}

CScreenEffect* CScreenEffect::Create(size_t num, float width, float height)
{
    if (num==0)
        return NULL;
    
    CScreenEffect* __result = new CScreenEffect();
    __result->SetClassName("ScrEffect");
    float distance = width / (float)num;
    num *= 4;
    __result->_vertexArray.resize(num);
    __result->_vertexData.resize(num);
    __result->_vertexArray.setPrimitiveType(sf::Quads);
    __result->SetLayerOrder(100);
    for (size_t i=0; i<num; i++){
        __result->_vertexData[i]._x = ((i+2)>>2)*distance;
        __result->_vertexData[i]._y = (i>>1)%2 == i%2 ? 0:height;
        __result->_vertexData[i]._alpha = 0.0f;
        __result->_vertexArray[i].color = sf::Color(0,0,0);
    }

    return __result;
}

void CScreenEffect::OnLoop()
{
    CBaiscProperties::OnLoop();
    if (!_isShowed)
        return;

    for (size_t i=0; i<_vertexArray.getVertexCount(); i++){
        if (_vertexArray[i].position.x != _vertexData[i]._x)
            _vertexArray[i].position.x = _vertexData[i]._x;
        
        if (_vertexArray[i].position.y != _vertexData[i]._y)
            _vertexArray[i].position.y = _vertexData[i]._y;
        
        if (_vertexArray[i].color.a != (sf::Uint8)_vertexData[i]._alpha)
            _vertexArray[i].color.a = (sf::Uint8)_vertexData[i]._alpha;
        
        if (_vertexArray[i].color.r != (sf::Uint8)_red)
            _vertexArray[i].color.r = (sf::Uint8)_red;

        if (_vertexArray[i].color.g != (sf::Uint8)_green)
            _vertexArray[i].color.g = (sf::Uint8)_green;

        if (_vertexArray[i].color.b != (sf::Uint8)_blue)
            _vertexArray[i].color.b = (sf::Uint8)_blue;
    }
}

void CScreenEffect::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_isShowed)
        Surf_Dest->draw(_vertexArray);
}

void CScreenEffect::OnSaveData(Object& json) const
{
    CDrawableClass::OnSaveData(json);
    json << "showed" << _isShowed;
}

void CScreenEffect::OnLoadData(Object json)
{
    CDrawableClass::OnLoadData(json);
    _isShowed = json.get<Boolean>("showed");

    float __alpha = _isShowed ? 255.0f : 0.0f;
    
    for (size_t i=0; i<_vertexArray.getVertexCount(); i++)
        _vertexData[i]._alpha = __alpha;
}