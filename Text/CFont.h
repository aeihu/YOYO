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
#include "../Common/CObject.h"

using namespace std;

class CFont : public CObject
{
    private:
        char*           _memFont;
        sf::Font        _font;

        bool LoadFont(string filename);
    public:
        CFont();
        ~CFont();

        CObject* Create(const char* filename);
        sf::Font& GetFont();
        void OnCleanup();
};

#endif
