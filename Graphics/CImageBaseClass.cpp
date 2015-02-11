/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImageBaseClass.h"

CImageBaseClass::CImageBaseClass(float x, float y)
{
    _baseNode = NULL;
    _scale.x =
    _scale.y = 1.0f;
    _sprite.setPosition(x,y);
    _rotation = 0.0f;
    _coordinate.x = x;
    _coordinate.y = y;
    _alpha = 0.0f;
    _flipX =
    _flipY=
    _visible = false;
    _image.setSmooth(true);
    _layerOrder = 0;
    _origin = _sprite.getOrigin();
    _flag = FLAG_ALPHA | FLAG_SCALE | FLAG_ROTATION;
}

CImageBaseClass::~CImageBaseClass()
{}

void CImageBaseClass::Flip()
{
    _sprite.setTextureRect(
        sf::IntRect(
            _flipX ? _sprite.getLocalBounds().width : 0,
            _flipY ? _sprite.getLocalBounds().height : 0,
            _flipX ? -_sprite.getLocalBounds().width : _sprite.getLocalBounds().width,
            _flipY ? -_sprite.getLocalBounds().height : _sprite.getLocalBounds().height)
    );
}

void CImageBaseClass::FlipX()
{
    _flipX = !_flipX;
    Flip();
}

void CImageBaseClass::FlipY()
{
    _flipY = !_flipY;
    Flip();
}

const sf::Vector2f& CImageBaseClass::GetGlobalPosition() const
{
    return _sprite.getPosition();
}

bool CImageBaseClass::SetBaseNode(CImageBaseClass* baseNode)
{
    if (baseNode){
        _baseNode = baseNode;
        return true;
    }

    return false;
}
        
bool CImageBaseClass::AddChildNode(CImageBaseClass* child)
{
    if (child){
        child->SetBaseNode(this);
        _childrenList.push_back(child);
        return true;
    }

    return false;
}

void CImageBaseClass::SetFlag(char flag)
{
    _flag = flag;
}

char CImageBaseClass::GetFlag() const
{
    return _flag;
}

void CImageBaseClass::SetLayerOrder(char order)
{
    _layerOrder = order;
}

void CImageBaseClass::SetLayerOrder(vector<string> args)
{
    if (args.size() > 0)
        _layerOrder = (unsigned char)atoi(args[0].c_str());
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
}

void CImageBaseClass::SetScaleY(float y)
{
    SetScale(_scale.x, y);
}

CSimultaneousOfAction* CImageBaseClass::CreateActionOfOriginBy(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionBy(&_origin.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionBy(&_origin.y, elapsed, y, restore, pause));
    return __result;
}

CActionBy* CImageBaseClass::CreateActionOfOriginXBy(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionBy(&_origin.x, elapsed, x, restore, pause);
}

CActionBy* CImageBaseClass::CreateActionOfOriginYBy(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionBy(&_origin.y, elapsed, y, restore, pause);
}

CSimultaneousOfAction* CImageBaseClass::CreateActionOfOriginTo(size_t elapsed, float x, float y, bool restore, bool pause)
{
    CSimultaneousOfAction* __result = new CSimultaneousOfAction();
    __result->AddAction(new CActionTo(&_origin.x, elapsed, x, restore, pause));
    __result->AddAction(new CActionTo(&_origin.y, elapsed, y, restore, pause));
    return __result;
}

CActionTo* CImageBaseClass::CreateActionOfOriginXTo(size_t elapsed, float x, bool restore, bool pause)
{
    return new CActionTo(&_origin.x, elapsed, x, restore, pause);
}

CActionTo* CImageBaseClass::CreateActionOfOriginYTo(size_t elapsed, float y, bool restore, bool pause)
{
    return new CActionTo(&_origin.y, elapsed, y, restore, pause);
}
        
const sf::Vector2f& CImageBaseClass::GetScale() const
{
    return _scale;
}

const sf::Vector2f& CImageBaseClass::GetOrigin() const
{
    return _origin;
}

void CImageBaseClass::SetOrigin(float x, float y)
{
    _origin.x = x;
    _origin.y = y;
}

void CImageBaseClass::SetOriginX(float x)
{
    _origin.x = x;
}

void CImageBaseClass::SetOriginY(float y)
{
    _origin.y = y;
}

const float& CImageBaseClass::GetAlpha() const
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

void CImageBaseClass::OnRender(sf::RenderTarget* Surf_Dest)
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
    bool __result = false;//CBaiscProperties::OnLoop();//>0 ? true : false;
    _visible = _alpha > 0 ? true : false;

    if (_sprite.getColor().a != _alpha)
        _sprite.setColor(sf::Color(255,255,255,_alpha));

    if (_visible){
        __result = OnSubLoop() ? true : __result;

        if (_coordinate != 
            (_baseNode == NULL ? 
                _sprite.getPosition() : GetGlobalPosition() - _baseNode->GetPosition())){

            if (_baseNode){
                _sprite.setPosition(_baseNode->GetGlobalPosition() + _coordinate);
            }
            else
                _sprite.setPosition(_coordinate);
        }
        
        if (_origin != _sprite.getOrigin())
            _sprite.setOrigin(_origin);
        
        if (_scale != _sprite.getScale())
            _sprite.setScale(_scale);

        if (_rotation != _sprite.getRotation())
            _sprite.setRotation(_rotation);
        
        list<CImageBaseClass*>::iterator it;
        for ( it=_childrenList.begin(); it !=_childrenList.end(); it++ ){
            if ((*it)->GetFlag() & FLAG_ALPHA)
                (*it)->SetAlpha(_alpha);

            if ((*it)->GetFlag() & FLAG_SCALE)
                (*it)->SetScale(_scale.x, _scale.y);

            if ((*it)->GetFlag() & FLAG_ROTATION)
                (*it)->SetRotation(_rotation);

            __result = (*it)->OnLoop() ? true : __result;
        }
    }

    return __result;
}

CActionTo* CImageBaseClass::CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore, bool pause)
{
    return new CActionTo(&_alpha, elapsed, alpha, restore, pause);
}

CActionBy* CImageBaseClass::CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore, bool pause)
{
    return new CActionBy(&_alpha, elapsed, alpha, restore, pause);
}

void CImageBaseClass::OnSaveData(Object& json) const
{
    CBaiscProperties::OnSaveData(json);
    json << "layer_order" << _layerOrder;
    json << "alpha" << _alpha;
    json << "flag" << _flag;
    json << "flip_x" << _flipX;
    json << "flip_y" << _flipY;
    json << "origin_x" << _origin.x;
    json << "origin_y" << _origin.y;
}