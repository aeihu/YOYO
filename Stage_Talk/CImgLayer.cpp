/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CImgLayer.h"
using namespace std;

CImgLayer::CImgLayer()
{
    _baseNode = NULL;
    _flipX =
    _flipY = false;
    _texture.setSmooth(true);
    _origin = _sprite.getOrigin();
    _flag = FLAG_ALPHA | FLAG_SCALE | FLAG_ROTATION;
}

CImgLayer::CImgLayer(float x, float y):CImageBaseClass(x,y)
{
    _baseNode = NULL;
    _flipX =
    _flipY = false;
    _sprite.setPosition(x,y);
    _texture.setSmooth(true);
    _origin = _sprite.getOrigin();
    _flag = FLAG_ALPHA | FLAG_SCALE | FLAG_ROTATION;
}

void CImgLayer::Flip()
{
    _sprite.setTextureRect(
        sf::IntRect(
            _flipX ? _sprite.getLocalBounds().width : 0,
            _flipY ? _sprite.getLocalBounds().height : 0,
            _flipX ? -_sprite.getLocalBounds().width : _sprite.getLocalBounds().width,
            _flipY ? -_sprite.getLocalBounds().height : _sprite.getLocalBounds().height)
    );
}

void CImgLayer::FlipX()
{
    _flipX = !_flipX;
    Flip();
}

void CImgLayer::FlipY()
{
    _flipY = !_flipY;
    Flip();
}

void CImgLayer::SetFlag(char flag)
{
    _flag = flag;
}

char CImgLayer::GetFlag() const
{
    return _flag;
}

const sf::Vector2f& CImgLayer::GetGlobalPosition() const
{
    return _sprite.getPosition();
}

bool CImgLayer::LoadImg(const char* fileName)
{
    if (fileName == NULL)
        return false;

    if (!CSurface::OnLoad(fileName, _texture))
        return false;

    _sprite.setTexture(_texture);
    return true;
}

CImgLayer* CImgLayer::Create(const char* filename)
{
    CImgLayer* __img = new CImgLayer();
    if (__img->LoadImg(filename)){
        __img->SetClassName("image");
        __img->SetPath(filename);
        return __img;
    }
    
    delete __img;
    return NULL;
}

void CImgLayer::OnLoop()
{
    _visible = _alpha > 0 ? true : false;
    
    if (_sprite.getColor().a != _alpha ||
        _sprite.getColor().r != _red ||
        _sprite.getColor().g != _green ||
        _sprite.getColor().b != _blue)
        _sprite.setColor(sf::Color(_red, _green, _blue, _alpha));

    if (_visible){
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
        
        if (_scale != _sprite.getScale()){
            _sprite.setScale(_scale);
        }

        if (_rotation != _sprite.getRotation())
            _sprite.setRotation(_rotation);
        
        list<CImgLayer*>::iterator it;
        for ( it=_childrenList.begin(); it !=_childrenList.end(); it++ ){
            if ((*it)->GetFlag() & FLAG_ALPHA)
                (*it)->SetAlpha(_alpha);

            if ((*it)->GetFlag() & FLAG_SCALE)
                (*it)->SetScale(_scale.x, _scale.y);

            if ((*it)->GetFlag() & FLAG_ROTATION)
                (*it)->SetRotation(_rotation);

            (*it)->OnLoop();
        }
    }
}

void CImgLayer::OnSaveData(Object& json) const
{
    CImageBaseClass::OnSaveData(json);
    json << "flag" << _flag;
}

bool CImgLayer::SetBaseNode(CImgLayer* baseNode)
{
    if (baseNode){
        _baseNode = baseNode;
        return true;
    }

    return false;
}
        
bool CImgLayer::AddChildNode(CImgLayer* child)
{
    if (child){
        child->SetBaseNode(this);
        _childrenList.push_back(child);
        return true;
    }

    return false;
}

void CImgLayer::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (_visible){
        Surf_Dest->draw(_sprite);

        list<CImgLayer*>::iterator it;
        for ( it=_childrenList.begin(); it !=_childrenList.end(); it++ ){
            (*it)->OnRender(Surf_Dest);
        }
    }
}