/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSPRITE_H_
    #define _CSPRITE_H_

#include "../Common/Define.h"
#include "../Common/CWindow.h"

class CImage;

class CSprite
{
    private:
        sf::Sprite _sprite;
        friend void CWindow::Draw(const CSprite sp, const sf::RenderStates &states);
    public:
        CSprite();
        ~CSprite();

        void SetTexture(const CImage &image, bool resetRect=false);
        void SetTextureRect(const CIntRect &rectangle);
        void SetPosition(float x, float y);
        void SetPosition(CCoordinate2f pos);
        void SetScale(float factorX, float factorY);
        void SetScale(CCoordinate2f factors);
        void SetRotation(float angle);
        void SetColor(CColor color);

        CCoordinate2f GetPosition() const;
        CColor GetColor() const;
        CCoordinate2f GetScale() const;
        float GetRotation() const;
        CFloatRect GetLocalBounds() const;
        CFloatRect GetGlobalBounds() const; 
};

#endif
