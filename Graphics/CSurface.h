/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CSURFACE_H_
    #define _CSURFACE_H_

#include "../Common/CZlib.h"
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;

//==============================================================================
class CSurface {
    private:
        static map<string, pair<sf::Texture, list<sf::Texture*> > > _textureList;
    public:
        CSurface();

    public:
        static bool GetTextureFromTextureList(string file, sf::Texture* &texture);
        static void GCForTextureList();
        static bool OnLoad(string file, sf::Texture &img);
        static bool OnLoad(string file, sf::Image &img);

        static bool OnDraw(sf::Image* surf_Dest, sf::Image* surf_Src);

        static bool OnDraw(sf::Image* surf_Dest, sf::Image* surf_Src, int X, int Y);

        static bool OnDraw(sf::Image* surf_Dest, sf::Image* surf_Src, size_t X, size_t Y, int X2, int Y2, int W, int H);

        static bool Transparent(sf::Image* surf_Dest, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A);
        
        static void FreeSurface(sf::Image* surf_Dest);
};

//==============================================================================

#endif
