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
//#include "../Graphics/CText.h"

using namespace std;

//class CFont
//{
//    private:
//        unsigned long _menSize;
//        char*         _memFont;
//    protected:
//    public:
//        sf::Font      _Font;
//
//        CFont();
//        ~CFont();
//        bool LoadFont(string filename);
//        //bool SetCharset(string charset);
//};
class CFont
{
    private:
        sf::Font _font;
//        friend void CText::SetFont(CFont& font);
    protected:
    public:
        CFont();
        ~CFont();

        bool LoadFont(string filename);
        const sf::Font GetFont();
};

#endif
