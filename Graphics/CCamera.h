/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCAMERA_H_
    #define _CCAMERA_H_ 

#include <SFML/Graphics.hpp>
#include "../Common/CBaiscProperties.h"

class CCamera : public CBaiscProperties
{
private:
    static sf::View         _camera;
    static sf::Vector2f     _offset;
protected:
public:
    static void Reset(float x, float y, float w, float h);
    static void SetViewport(float x, float y, float w, float h);
    static void SetCenter(float x, float y);
    static void SetSize(float w, float h);
    static void SetZoom(float zoom);
    static void SetRotation(float angle);
    static void Bind(sf::RenderWindow* window);
    static sf::Vector2f GetCenter();
    static sf::Vector2f GetPosition();
};


#endif
