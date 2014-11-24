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
    _rotation = 0.0f;
    _coordinate.x = x;
    _coordinate.y = y;
    _alpha = 0;
    _visible = false;
    _image.setSmooth(true);
    _layerOrder = 0;
    _flag = FLAG_POSITION | FLAG_ALPHA | FLAG_SCALE | FLAG_ROTATION;
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

float& CImageBaseClass::GetRotation()
{
    return _rotation;
}

void CImageBaseClass::SetRotation(float r)
{
    _rotation = r;
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

void CImageBaseClass::SetOffsetX(float x)
{
    _offset.x = x;
}

void CImageBaseClass::SetOffsetY(float y)
{
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
    if (__img->LoadImg(filename)){
        __img->SetClassName("image");
        __img->SetPath(filename);
        return __img;
    }
    
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
    if (_visible){
        Surf_Dest->draw(_sprite);
        OnSubRender(Surf_Dest);

        list<CImageBaseClass*>::iterator it;
        for ( it=_childrenList.begin(); it !=_childrenList.end(); it++ ){
            (*it)->OnRender(Surf_Dest);
        }
    }
}

bool CImageBaseClass::OnLoop()
{
    bool __result = CAdderControl::OnLoop()>0 ? true : false;
    _visible = _alpha > 0 ? true : false;

    if (_sprite.getColor().a != _alpha)
        _sprite.setColor(sf::Color(255,255,255,_alpha));

    if (_visible){
        __result = OnSubLoop() ? true : __result;
        if (_coordinate != _sprite.getPosition())
            _sprite.setPosition(_coordinate);
        
        if (_scale != _sprite.getScale())
            _sprite.setScale(_scale);

        if (_rotation != _sprite.getRotation())
            _sprite.setRotation(_rotation);
        
        list<CImageBaseClass*>::iterator it;
        for ( it=_childrenList.begin(); it !=_childrenList.end(); it++ ){
            if ((*it)->GetFlag() | FLAG_ALPHA)
                (*it)->SetAlpha(_alpha);

            if ((*it)->GetFlag() | FLAG_POSITION)
                (*it)->SetPosition(_coordinate.x + (*it)->GetOffset().x ,
                    _coordinate.y + (*it)->GetOffset().y);

            if ((*it)->GetFlag() | FLAG_SCALE)
                (*it)->SetScale(_scale.x, _scale.y);

            if ((*it)->GetFlag() | FLAG_ROTATION)
                (*it)->SetRotation(_rotation);

            __result = (*it)->OnLoop() ? true : __result;
        }
    }

    return __result;
}

void CImageBaseClass::OnSaveData(Object& json) const
{
    CObject::OnSaveData(json);
    json << "layer_order" << _layerOrder;
    json << "alpha" << _alpha;
    json << "x" << _coordinate.x;
    json << "y" << _coordinate.y;
    json << "offset_x" << _offset.x;
    json << "offset_y" << _offset.y;
    json << "scale_x" << _scale.x;
    json << "scale_y" << _scale.y;
    json << "rotation" << _rotation;
    json << "flag" << _flag;
}