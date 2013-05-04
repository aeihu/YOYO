/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CGUICOMMON_H_
    #define _CGUICOMMON_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Graphics/CSurface.h"

class CGuiCommon
{
    private:
        static std::vector<std::vector<unsigned int> > OnLoad(const char* File);
    public:
        static bool CreateBoxBackground(sf::Image* Surf_Dest, sf::Image* Surf_Src, const char* File, unsigned int Tile_Size);
    protected:
};

#endif
