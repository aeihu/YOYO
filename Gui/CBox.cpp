/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CBox.h"

CBox::CBox()
{
    _width =
    _height = 100;
    _isJiugone = false;
}

CBox::~CBox()
{
}

//================================
//property:
//* PATH,
//JIUGONG
//{
//* WIDTH,
//* HEIGHT,
//* LEFT_WIDTH,
//* RIGHT_WIDTH,
//* TOP_HEIGHT,
//* BOTTOM_HEIGHT,
//}
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
bool CBox::CheckList(const Object& json)
{
    bool __result = CImgLayer::CheckList(json);
    
    if (json.has<Object>("JIUGONG")){
        Object __obj = json.get<Object>("JIUGONG");
        if (!__obj.has<Number>("WIDTH")){
            cout << "can't find value of WIDTH." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("HEIGHT")){
            cout << "can't find value of HEIGHT." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("LEFT_WIDTH")){
            cout << "can't find value of LEFT_WIDTH." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("RIGHT_WIDTH")){
            cout << "can't find value of RIGHT_WIDTH." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("TOP_HEIGHT")){
            cout << "can't find value of TOP_HEIGHT." << endl;
            __result = false;
        }

        if (!__obj.has<Number>("BOTTOM_HEIGHT")){
            cout << "can't find value of BOTTOM_HEIGHT." << endl;
            __result = false;
        }
    }

    return __result;
}

bool CBox::LoadImgForSetProperty(const Object& json, string key)
{
    if (json.has<Object>("JIUGONG")){
        sf::Image __tileset, __dest;
        if (!CSurface::GetTextureFromTextureList(json.get<String>(key).c_str(), _texture))
            return false;

        Object __obj = json.get<Object>("JIUGONG");

        _isJiugone = true;
        _jiugong.SetTexture(*_texture, __obj.get<Number>("WIDTH"), __obj.get<Number>("HEIGHT"),
            __obj.get<Number>("LEFT_WIDTH"), __obj.get<Number>("RIGHT_WIDTH"),
            __obj.get<Number>("TOP_HEIGHT"), __obj.get<Number>("BOTTOM_HEIGHT"));
    }
    else{
        if (!CSurface::GetTextureFromTextureList(json.get<String>(key).c_str(), _texture))
            return false;

        _isJiugone = false;
        _sprite.setTexture(*_texture, true);
    }

    return true;
}

void CBox::OnLoop()
{
    if (_isJiugone){
        CBaiscProperties::OnLoop();

        if (_jiugong.GetColor().a != (sf::Uint8)GetAlpha() ||
            _jiugong.GetColor().r != (sf::Uint8)GetRed() ||
            _jiugong.GetColor().g != (sf::Uint8)GetGreen() ||
            _jiugong.GetColor().b != (sf::Uint8)GetBlue())
            _jiugong.SetColor(
            sf::Color(
            (sf::Uint8)GetRed(),
            (sf::Uint8)GetGreen(),
            (sf::Uint8)GetBlue(),
            (sf::Uint8)GetAlpha()));

        Loop(&_jiugong);
    }
    else
        CImgLayer::OnLoop();
}

sf::Transform CBox::GetTransform()
{
    if (_baseNode)
        return (_isJiugone ? _jiugong.getTransform() : _sprite.getTransform()) * _baseNode->GetTransform();

    return _isJiugone ? _jiugong.getTransform() : _sprite.getTransform();
}

void CBox::OnRender(sf::RenderTarget* Surf_Dest)
{
    if (IsShowed()){
        if (_baseNode){
            if (_isJiugone)
                Surf_Dest->draw(_jiugong, _baseNode->GetTransform());
            else
                Surf_Dest->draw(_sprite, _baseNode->GetTransform());
        }
        else{
            if (_isJiugone)
                Surf_Dest->draw(_jiugong);
            else
                Surf_Dest->draw(_sprite);
        }

        list<CImageBaseClass*>::iterator it;
        for (it = _childrenList.begin(); it != _childrenList.end(); it++){
            (*it)->OnRender(Surf_Dest);
        }
    }
}

//======================================================

CBox::CJiugong::CJiugong()
{
    _pTexture = NULL;
    _vertexArray.resize(36);
    _vertexArray.setPrimitiveType(sf::Quads);
}

void CBox::CJiugong::SetColor(const sf::Color& color)
{
    for (int i = 0; i < 16; i++)
        _vertexArray[0].color = color;
}

const sf::Color& CBox::CJiugong::GetColor() const
{
    return _vertexArray[0].color;
}

void CBox::CJiugong::SetVectorForVertexArray(
    sf::Vector2f* vectors,
    unsigned int width,
    unsigned int height,
    unsigned int leftWidth,
    unsigned int rightWidth,
    unsigned int topHeight,
    unsigned int bottomHeight)
{
    vectors[0] = sf::Vector2f(0, 0);
    vectors[1] = sf::Vector2f(leftWidth, 0);
    vectors[2] = sf::Vector2f(width - rightWidth, 0);
    vectors[3] = sf::Vector2f(width, 0);
    
    vectors[4] = sf::Vector2f(0, topHeight);
    vectors[5] = sf::Vector2f(leftWidth, topHeight);
    vectors[6] = sf::Vector2f(width - rightWidth, topHeight);
    vectors[7] = sf::Vector2f(width, topHeight);

    vectors[8] = sf::Vector2f(0, height - bottomHeight);
    vectors[9] = sf::Vector2f(leftWidth, height - bottomHeight);
    vectors[10] = sf::Vector2f(width - rightWidth, height - bottomHeight);
    vectors[11] = sf::Vector2f(width, height - bottomHeight);

    vectors[12] = sf::Vector2f(0, height);
    vectors[13] = sf::Vector2f(leftWidth, height);
    vectors[14] = sf::Vector2f(width - rightWidth, height);
    vectors[15] = sf::Vector2f(width, height);
}

void CBox::CJiugong::SetTexture(
    const sf::Texture& texture,
    unsigned int width,
    unsigned int height,
    unsigned int leftWidth,
    unsigned int rightWidth,
    unsigned int topHeight,
    unsigned int bottomHeight)
{
    sf::Vector2f __vec[16];
    SetVectorForVertexArray(
        __vec,
        width,
        height,
        leftWidth,
        rightWidth,
        topHeight,
        bottomHeight);

    _vertexArray[0].position = __vec[0];
    _vertexArray[1].position = __vec[1];
    _vertexArray[2].position = __vec[5];
    _vertexArray[3].position = __vec[4];

    _vertexArray[4].position = _vertexArray[1].position;
    _vertexArray[5].position = __vec[2];
    _vertexArray[6].position = __vec[6];
    _vertexArray[7].position = _vertexArray[2].position;

    _vertexArray[8].position = _vertexArray[5].position;
    _vertexArray[9].position = __vec[3];
    _vertexArray[10].position = __vec[7];
    _vertexArray[11].position = _vertexArray[6].position;

    _vertexArray[12].position = _vertexArray[3].position;
    _vertexArray[13].position = _vertexArray[2].position;
    _vertexArray[14].position = __vec[9];
    _vertexArray[15].position = __vec[8];

    _vertexArray[16].position = _vertexArray[2].position;
    _vertexArray[17].position = _vertexArray[6].position;
    _vertexArray[18].position = __vec[10];
    _vertexArray[19].position = _vertexArray[14].position;

    _vertexArray[20].position = _vertexArray[6].position;
    _vertexArray[21].position = _vertexArray[10].position;
    _vertexArray[22].position = __vec[11];
    _vertexArray[23].position = _vertexArray[18].position;

    _vertexArray[24].position = _vertexArray[15].position;
    _vertexArray[25].position = _vertexArray[14].position;
    _vertexArray[26].position = __vec[13];
    _vertexArray[27].position = __vec[12];

    _vertexArray[28].position = _vertexArray[14].position;
    _vertexArray[29].position = _vertexArray[18].position;
    _vertexArray[30].position = __vec[14];
    _vertexArray[31].position = _vertexArray[26].position;

    _vertexArray[32].position = _vertexArray[18].position;
    _vertexArray[33].position = _vertexArray[22].position;
    _vertexArray[34].position = __vec[15];
    _vertexArray[35].position = _vertexArray[30].position;

    _pTexture = &texture;
    SetVectorForVertexArray(
        __vec,
        _pTexture->getSize().x,
        _pTexture->getSize().y,
        leftWidth,
        rightWidth,
        topHeight,
        bottomHeight);

    _vertexArray[0].texCoords = __vec[0];
    _vertexArray[1].texCoords = __vec[1];
    _vertexArray[2].texCoords = __vec[5];
    _vertexArray[3].texCoords = __vec[4];

    _vertexArray[4].texCoords = _vertexArray[1].texCoords;
    _vertexArray[5].texCoords = __vec[2];
    _vertexArray[6].texCoords = __vec[6];
    _vertexArray[7].texCoords = _vertexArray[2].texCoords;

    _vertexArray[8].texCoords = _vertexArray[5].texCoords;
    _vertexArray[9].texCoords = __vec[3];
    _vertexArray[10].texCoords = __vec[7];
    _vertexArray[11].texCoords = _vertexArray[6].texCoords;

    _vertexArray[12].texCoords = _vertexArray[3].texCoords;
    _vertexArray[13].texCoords = _vertexArray[2].texCoords;
    _vertexArray[14].texCoords = __vec[9];
    _vertexArray[15].texCoords = __vec[8];

    _vertexArray[16].texCoords = _vertexArray[2].texCoords;
    _vertexArray[17].texCoords = _vertexArray[6].texCoords;
    _vertexArray[18].texCoords = __vec[10];
    _vertexArray[19].texCoords = _vertexArray[14].texCoords;

    _vertexArray[20].texCoords = _vertexArray[6].texCoords;
    _vertexArray[21].texCoords = _vertexArray[10].texCoords;
    _vertexArray[22].texCoords = __vec[11];
    _vertexArray[23].texCoords = _vertexArray[18].texCoords;

    _vertexArray[24].texCoords = _vertexArray[15].texCoords;
    _vertexArray[25].texCoords = _vertexArray[14].texCoords;
    _vertexArray[26].texCoords = __vec[13];
    _vertexArray[27].texCoords = __vec[12];

    _vertexArray[28].texCoords = _vertexArray[14].texCoords;
    _vertexArray[29].texCoords = _vertexArray[18].texCoords;
    _vertexArray[30].texCoords = __vec[14];
    _vertexArray[31].texCoords = _vertexArray[26].texCoords;

    _vertexArray[32].texCoords = _vertexArray[18].texCoords;
    _vertexArray[33].texCoords = _vertexArray[22].texCoords;
    _vertexArray[34].texCoords = __vec[15];
    _vertexArray[35].texCoords = _vertexArray[30].texCoords;
}

void CBox::CJiugong::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); 
    states.texture = _pTexture;
    target.draw(_vertexArray, states);
}

void CBox::CJiugong::SetWidth(float width)
{
    float offset = width - _vertexArray[9].position.x;

    _vertexArray[5].position.x += offset;
    _vertexArray[8].position.x += offset;
    _vertexArray[9].position.x += offset;
    _vertexArray[6].position.x += offset;
    _vertexArray[11].position.x += offset;
    _vertexArray[17].position.x += offset;
    _vertexArray[20].position.x += offset;
    _vertexArray[10].position.x += offset;
    _vertexArray[21].position.x += offset;
    _vertexArray[18].position.x += offset;
    _vertexArray[23].position.x += offset;
    _vertexArray[29].position.x += offset;
    _vertexArray[32].position.x += offset;
    _vertexArray[22].position.x += offset;
    _vertexArray[33].position.x += offset;
    _vertexArray[30].position.x += offset;
    _vertexArray[35].position.x += offset;
    _vertexArray[34].position.x += offset;
}

void CBox::CJiugong::SetHeight(float height)
{
    float offset = height - _vertexArray[27].position.y;

    _vertexArray[15].position.y += offset;
    _vertexArray[24].position.y += offset;
    _vertexArray[14].position.y += offset;
    _vertexArray[19].position.y += offset;
    _vertexArray[25].position.y += offset;
    _vertexArray[28].position.y += offset;
    _vertexArray[18].position.y += offset;
    _vertexArray[23].position.y += offset;
    _vertexArray[29].position.y += offset;
    _vertexArray[32].position.y += offset;
    _vertexArray[22].position.y += offset;
    _vertexArray[33].position.y += offset;
    _vertexArray[27].position.y += offset;
    _vertexArray[26].position.y += offset;
    _vertexArray[31].position.y += offset;
    _vertexArray[30].position.y += offset;
    _vertexArray[35].position.y += offset;
    _vertexArray[34].position.y += offset;
}
