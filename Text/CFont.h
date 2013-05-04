/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CFONT_H_
    #define _CFONT_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "../Common/Cio.h"

using namespace std;

class CFont
{
    private:
        unsigned long _menSize;
        char*         _memFont;
    protected:
    public:
        sf::Font      _Font;

        CFont();
        ~CFont();
        bool LoadFont(string filename, unsigned int size=25);
        bool SetCharset(string charset, unsigned int size=25);
};

#endif
