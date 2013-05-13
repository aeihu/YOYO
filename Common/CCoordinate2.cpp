/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCOORDINATE2_CPP_
    #define _CCOORDINATE2_CPP_

#include "Define.h"

template <typename X>
CCoordinate2<X>::CCoordinate2()
{}

template <typename X>
CCoordinate2<X>::CCoordinate2(X x, X y)
{
    this->x = x;
    this->y = y;
}

template <typename X>
CCoordinate2<X>::~CCoordinate2()
{}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator= (sf::Vector2<X> ob2)
{
    x = ob2.x;
    y = ob2.y;
    return *this;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator= (CCoordinate2<X> ob2)
{
    x = ob2.x;
    y = ob2.y;
    return *this;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator+ (CCoordinate2<X> ob2)
{
    CCoordinate2<X> __temp;
    __temp.x = x + ob2.x;
    __temp.y = y + ob2.y;
    return __temp;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator- (CCoordinate2<X> ob2)
{
    CCoordinate2<X> __temp;
    __temp.x = x - ob2.x;
    __temp.y = y - ob2.y;
    return __temp;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator* (CCoordinate2<X> ob2)
{
    CCoordinate2<X> __temp;
    __temp.x = x * ob2.x;
    __temp.y = y * ob2.y;
    return __temp;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator/ (CCoordinate2<X> ob2)
{
    CCoordinate2<X> __temp;
    __temp.x = x / ob2.x;
    __temp.y = y / ob2.y;
    return __temp;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator+= (CCoordinate2<X> ob2)
{
    x += ob2.x;
    y += ob2.y;
    return *this;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator-= (CCoordinate2<X> ob2)
{
    x -= ob2.x;
    y -= ob2.y;
    return *this;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator*= (CCoordinate2<X> ob2)
{
    x *= ob2.x;
    y *= ob2.y;
    return *this;
}

template <typename X>
CCoordinate2<X> CCoordinate2<X>::operator/= (CCoordinate2<X> ob2)
{
    x /= ob2.x;
    y /= ob2.y;
    return *this;
}

template <typename X>
bool CCoordinate2<X>::operator== (CCoordinate2<X> ob2)
{
    return ((x >= ob2.x+EXACT_BIT && x <= ob2.x-EXACT_BIT) && (y >= ob2.y+EXACT_BIT && y <= ob2.y-EXACT_BIT));
}

template <typename X>
bool CCoordinate2<X>::operator!= (CCoordinate2<X> ob2)
{
    return !((x >= ob2.x+EXACT_BIT && x <= ob2.x-EXACT_BIT) && (y >= ob2.y+EXACT_BIT && y <= ob2.y-EXACT_BIT));
}

#endif
