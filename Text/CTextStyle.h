/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CTEXTSTYLE_H_ 
    #define _CTEXTSTYLE_H_

#include <SFML/Graphics.hpp>

class CTextStyle
{
    private:
    public:
        size_t              _size;
        sf::Color           _color;
        //sf::String::   _style;

        CTextStyle();
};

#endif