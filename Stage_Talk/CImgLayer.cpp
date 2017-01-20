/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CImgLayer.h"
using namespace std;

CImgLayer::CImgLayer()
{
    _texture = NULL;
    _flipX =
    _flipY = false;
    SetOrigin(_sprite.getOrigin().x, _sprite.getOrigin().y);
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

float CImgLayer::GetWidth() const
{
    return _sprite.getGlobalBounds().width;
}

float CImgLayer::GetHeight() const
{
    return _sprite.getGlobalBounds().height;
}

sf::Transform CImgLayer::GetTransform()
{
    if (_baseNode)
        return _sprite.getTransform() * _baseNode->GetTransform();

    return _sprite.getTransform();
}

bool CImgLayer::Contains(float x, float y)
{
    sf::FloatRect __rect = _sprite.getGlobalBounds();
    __rect.left = __rect.top = 0.f;
    __rect = GetTransform().transformRect(__rect);
    return __rect.contains(sf::Vector2f(x, y));
}

bool CImgLayer::LoadImgForSetProperty(const Object& json, string key)
{
    if (!CSurface::GetTextureFromTextureList(json.get<String>(key), _texture))
        return false;

    _sprite.setTexture(*_texture, true);
    return true;
}

//================================
//property:
//* PATH,
//ORDER,
//SCALE,
//SCALE_X,
//SCALE_Y,
//ROTATION,
//ORIGIN_X,
//ORIGIN_Y,
//X,
//Y,
//RED,
//GREEN,
//BLUE,
//ALPHA,
//================================

bool CImgLayer::CheckList(const Object& json)
{
    bool __result = true;

    if (!json.has<String>("PATH")){
        cout << "can't find value of PATH." << endl;
        __result = false;
    }

    return __result;
}

bool CImgLayer::SetProperty(const Object& json, bool isLoad)
{
    if (isLoad)
        if (!LoadImgForSetProperty(json, "PATH"))
            return false;

    if (json.has<Number>("SCALE")){
        SetScale(json.get<Number>("SCALE"), json.get<Number>("SCALE"));
    }
    else{
        SetScale(
            json.has<Number>("SCALE_X") ? json.get<Number>("SCALE_X") : 1.0f,
            json.has<Number>("SCALE_Y") ? json.get<Number>("SCALE_Y") : 1.0f);
    }

    SetRotation(json.has<Number>("ROTATION") ? json.get<Number>("ROTATION") : 0.0f);
    SetOrigin(
        json.has<Number>("ORIGIN_X") ? json.get<Number>("ORIGIN_X") : 0.0f,
        json.has<Number>("ORIGIN_Y") ? json.get<Number>("ORIGIN_Y") : 0.0f);

    SetPosition(
        json.has<Number>("X") ? json.get<Number>("X") : 0.0f,
        json.has<Number>("Y") ? json.get<Number>("Y") : 0.0f);

    if (_flipX)
        FlipX();

    if (_flipY)
        FlipY();

    if (json.has<Number>("ORDER"))
        SetLayerOrder(json.get<Number>("ORDER"));

    SetRed(json.has<Number>("RED") ? json.get<Number>("RED") : 255);
    SetGreen(json.has<Number>("GREEN") ? json.get<Number>("GREEN") : 255);
    SetBlue(json.has<Number>("BLUE") ? json.get<Number>("BLUE") : 255);
    SetAlpha(json.has<Number>("ALPHA") ? json.get<Number>("ALPHA") : 255);

    return true;
}


CImgLayer* CImgLayer::Create(const char* filename)
{
    CImgLayer* __img = new CImgLayer();
    if (__img->LoadConfigFile(filename)){
        __img->SetClassName("Img");
        __img->SetPath(filename);
        return __img;
    }
    
    delete __img;
    return NULL;
}

void CImgLayer::OnLoop()
{
    CBaiscProperties::OnLoop();
    
    if (_sprite.getColor().a != (sf::Uint8)GetAlpha() ||
        _sprite.getColor().r != (sf::Uint8)GetRed() ||
        _sprite.getColor().g != (sf::Uint8)GetGreen() ||
        _sprite.getColor().b != (sf::Uint8)GetBlue())
        _sprite.setColor(
            sf::Color(
                (sf::Uint8)GetRed(), 
                (sf::Uint8)GetGreen(), 
                (sf::Uint8)GetBlue(), 
                (sf::Uint8)GetAlpha()));

    Loop(&_sprite);
}

void CImgLayer::OnSaveData(Object& json) const
{
    CImageBaseClass::OnSaveData(json);
    json << "flag" << _flag;
}
        
void CImgLayer::OnLoadData(Object json)
{
    CImageBaseClass::OnLoadData(json);
    _flag = json.get<Number>("flag");
}

void CImgLayer::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (IsShowed()){
        if (_baseNode)
            Surf_Dest->draw(_sprite, _baseNode->GetTransform());
        else
            Surf_Dest->draw(_sprite);

        list<CImageBaseClass*>::iterator it;
        for ( it=_childrenList.begin(); it !=_childrenList.end(); it++ )
            (*it)->OnRender(Surf_Dest);
    }
}

void CImgLayer::OnCleanup()
{
    CImageBaseClass::OnCleanup();
    if (_texture == NULL){
        delete _texture;
        _texture == NULL;
    }
}