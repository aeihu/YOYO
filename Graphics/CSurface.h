/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSURFACE_H_
    #define _CSURFACE_H_

#include "../Common/CZlib.h"
#include <SFML/Graphics.hpp>
//#include "CImage.h"

//==============================================================================
class CSurface {
    public:
        CSurface();

    public:
        static bool OnLoad(std::string File, sf::Texture &Img);
        static bool OnLoad(std::string File, sf::Image &Img);

        //static CImage* OnCreate(size_t W, size_t H);

        //static CImage* OnCreate(size_t W, size_t H, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A);

        static bool OnDraw(sf::Image* Surf_Dest, sf::Image* Surf_Src);

        static bool OnDraw(sf::Image* Surf_Dest, sf::Image* Surf_Src, int X, int Y);

        static bool OnDraw(sf::Image* Surf_Dest, sf::Image* Surf_Src, size_t X, size_t Y, int X2, int Y2, int W, int H);

        static bool Transparent(sf::Image* Surf_Dest, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A);
        
        static void FreeSurface(sf::Image* Surf_Dest);
};

//==============================================================================

#endif
