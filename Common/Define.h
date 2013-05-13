/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _DEFINE_H_
    #define _DEFINE_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

const float EXACT_BIT = 0.00001f;

template <typename X>
class CCoordinate2 : private sf::Vector2<X>
{
    public:
        explicit CCoordinate2();
        explicit CCoordinate2(X x, X y);
        ~CCoordinate2();

        using sf::Vector2<X>::x;
        using sf::Vector2<X>::y;

        CCoordinate2<X> operator= (sf::Vector2<X> ob2);
        CCoordinate2<X> operator= (CCoordinate2<X> ob2);
        CCoordinate2<X> operator+ (CCoordinate2<X> ob2);
        CCoordinate2<X> operator+= (CCoordinate2<X> ob2);
        CCoordinate2<X> operator- (CCoordinate2<X> ob2);
        CCoordinate2<X> operator-= (CCoordinate2<X> ob2);
        CCoordinate2<X> operator* (CCoordinate2<X> ob2);
        CCoordinate2<X> operator*= (CCoordinate2<X> ob2);
        CCoordinate2<X> operator/ (CCoordinate2<X> ob2);
        CCoordinate2<X> operator/= (CCoordinate2<X> ob2);
        bool operator== (CCoordinate2<X> ob2);
        bool operator!= (CCoordinate2<X> ob2);
};

typedef CCoordinate2<float> CCoordinate2f;
typedef CCoordinate2<unsigned int> CCoordinate2u;

#include "CCoordinate2.cpp"

class CIntRect : public sf::IntRect
{
    private:
    public:
        inline CIntRect operator= (sf::IntRect ob2){
            height = ob2.height;
            width = ob2.width;
            top = ob2.top;
            left = ob2.left;
            return *this;
        }

        CIntRect(){};
        ~CIntRect(){};
};

class CFloatRect : public sf::FloatRect
{
    private:
    public:
        inline CFloatRect operator= (sf::FloatRect ob2){
            height = ob2.height;
            width = ob2.width;
            top = ob2.top;
            left = ob2.left;
            return *this;
        }

        CFloatRect(){};
        ~CFloatRect(){};
};

class CColor : public sf::Color
{
    public:
        CColor(){};
        CColor(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha=255):sf::Color(red, green, blue, alpha){};
        ~CColor(){};

        inline CColor operator= (sf::Color ob2){
            a = ob2.a;
            b = ob2.b;
            r = ob2.r;
            g = ob2.g;
            return *this;
        }
};

#endif