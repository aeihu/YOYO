/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CENTITYBAISCPROPERTIES_H_
    #define _CENTITYBAISCPROPERTIES_H_

#include <SFML/Graphics.hpp>

class CBaiscProperties
{
    protected:
        sf::Vector2f                      _scale;
        sf::Vector2f                      _coordinate;
        sf::Vector2f                      _offset;
        float                             _rotation;
    public:
        virtual float& GetRotation();
        void SetRotation(float r);
        sf::Vector2f& GetPosition();
        virtual void SetPosition(float x, float y);
        virtual sf::Vector2f& GetOffset();
        virtual void SetOffset(float x, float y);
        virtual void SetOffsetX(float x);
        virtual void SetOffsetY(float y);

        virtual sf::Vector2f& GetScale();
        virtual void SetScale(float x, float y);
        virtual void SetScaleX(float x);
        virtual void SetScaleY(float y);
};

#endif
