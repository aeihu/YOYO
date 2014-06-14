/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/
#ifndef _CSEQUENCEOFSPRITE_H_
    #define _CSEQUENCEOFSPRITE_H_

#include "CImageBaseClass.h"
#include "../Animation/CAnimation.h"

class CSequenceOfSprite : public CImageBaseClass, public CAnimation
{
    private:
        sf::IntRect        _rect;
    public:
        using CImageBaseClass::_image;
        using CImageBaseClass::_sprite;

        CSequenceOfSprite(float x=0.0f, float y=0.0f, int left=0, int top=0, int width=1, int height=1);
        void SetCurrentImageFrame(int frame);
        void SetWidth(int w);
        void SetHeight(int h);
        bool LoadImg(const char* filename);

        sf::Vector2f GetPosition();
        int GetWidth();
        int GetHeight();
        void TurnOff(int frame = 0);

        bool OnLoop();
};

#endif