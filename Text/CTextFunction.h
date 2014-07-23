/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CTEXTFUNCTION_H_ 
    #define _CTEXTFUNCTION_H_

#include <SFML/Graphics.hpp>
#include <string>

class CTextFunction
{
    public:
        static void SetString(sf::Text& text, std::string str);
        //static void SetString(sf::Text& text, std::string str, size_t len);
        static unsigned int SizeOfCharWithUTF8(char Char);
        static unsigned int StringLengthWithUTF8(std::string str);
};

#endif
