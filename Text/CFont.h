/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
//#include "../Graphics/CText.h"

using namespace std;

class CFont
{
    private:
        char*           _memFont;
    protected:
        sf::Font        _font;

        void SetString(sf::Text& text, string str);
    public:
        CFont();
        ~CFont();

        bool LoadFont(string filename);
};

#endif
