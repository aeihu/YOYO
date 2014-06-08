/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImageBaseClass.h"

CImageBaseClass::CImageBaseClass(float x, float y)
{
    _scale.x =
    _scale.y = 1.0f;
    _sprite.setPosition(x,y);
    _coordinate.x = x;
    _coordinate.y = y;
    _alpha = 0;
    _visible = false;
    _image.setSmooth(true);
    _layerOrder = 0;
    _flag = FLAG_POSITION | FLAG_ALPHA | FLAG_SCALE;
}

CImageBaseClass::~CImageBaseClass()
{}

void CImageBaseClass::SetFlag(char flag)
{
    _flag = flag;
}

char CImageBaseClass::GetFlag() const
{
    return _flag;
}

sf::Vector2f& CImageBaseClass::GetPosition() 
{
    return _coordinate;
}

void CImageBaseClass::SetPosition(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}

sf::Vector2f& CImageBaseClass::GetOffset()
{
    return _offset;
}

void CImageBaseClass::SetOffset(float x, float y)
{
    _offset.x = x;
    _offset.y = y;
}

void CImageBaseClass::SetLayerOrder(char order)
{
    _layerOrder = order;
}

void CImageBaseClass::SetAlpha(int alpha)
{
    if (alpha > 255)
        alpha = 255;
    else if (_alpha < 0)
        alpha = 0;

    _alpha = alpha;
}

void CImageBaseClass::SetScale(float x, float y)
{
    _scale.x = x;
    _scale.y = y;

    if (x > 1.0f || y > 1.0f)
        _image.setSmooth(true);
    else
        _image.setSmooth(false);
}

void CImageBaseClass::SetScaleX(float x)
{
    SetScale(x, _scale.y);
    _scale.x = x;
}

void CImageBaseClass::SetScaleY(float y)
{
    SetScale(_scale.x, y);
}
        
sf::Vector2f& CImageBaseClass::GetScale()
{
    return _scale;
}

int& CImageBaseClass::GetAlpha() 
{
    return _alpha;
}

char CImageBaseClass::GetLayerOrder() const
{
    return _layerOrder;
}

CImageBaseClass* CImageBaseClass::Create(const char* filename)
{
    CImageBaseClass* __img = new CImageBaseClass();
    if (__img->LoadImg(filename))
        return __img;
    
    delete __img;
    return NULL;
}

bool CImageBaseClass::GetVisible() const
{
    return _visible;
}

bool CImageBaseClass::IsStandby()
{
    return _visible && Count()==0;
}

bool CImageBaseClass::LoadImg(const char* fileName)
{
    if (fileName == NULL)
        return false;

    if (!CSurface::OnLoad(fileName, _image))
        return false;

    _image.setSmooth(false);
    _sprite.setTexture(_image);
    return true;
}

void CImageBaseClass::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (_visible)
        Surf_Dest->draw(_sprite);
}

bool CImageBaseClass::OnLoop()
{
    bool __result = CAdderControl::OnLoop()>0 ? true : false;
    _visible = _alpha > 0 ? true : false;

    if (_sprite.getColor().a != _alpha)
        _sprite.setColor(sf::Color(255,255,255,_alpha));

    if (_visible){
        if (_coordinate != _sprite.getPosition())
            _sprite.setPosition(_coordinate);
        
        if (_scale != _sprite.getScale())
            _sprite.setScale(_scale);
    }

    list<CImageBaseClass*>::iterator it;
    for ( it=_childrenList.begin(); it !=_childrenList.end(); it++ ){
        if ((*it)->GetFlag() | FLAG_ALPHA)
            (*it)->SetAlpha(_alpha);

        if ((*it)->GetFlag() | FLAG_POSITION)
            (*it)->SetPosition(_coordinate.x + (*it)->GetOffset().x ,
                _coordinate.y + (*it)->GetOffset().y);

        if ((*it)->GetFlag() | FLAG_SCALE)
            (*it)->SetScale(_scale.x, _scale.y);
    }

    return __result;
}
