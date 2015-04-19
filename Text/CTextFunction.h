/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CTEXTFUNCTION_H_ 
    #define _CTEXTFUNCTION_H_

#include <SFML/Graphics.hpp>
#include <string>

class CTextFunction
{
    public:
        static void SetString(sf::Text& text, std::string str);
        static size_t SizeOfCharWithUTF8(char Char);
        static size_t StringLengthWithUTF8(std::string str);
        static std::string GetNameInFilename(std::string filename);
};

#endif
