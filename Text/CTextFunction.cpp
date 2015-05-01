/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CTextFunction.h"

void CTextFunction::SetString(sf::Text& text, std::string str)
{
    //sf::Uint32* __uft32String = new sf::Uint32[str.length()]
    int __length = StringLengthWithUTF8(str);
    sf::Uint32* __uft32String = new sf::Uint32[__length+1];
    sf::Utf8::toUtf32(str.begin(), str.end(), __uft32String);
    __uft32String[__length] = '\0';
    text.setString(__uft32String);
    delete[] __uft32String;
    __uft32String = NULL;
}

size_t CTextFunction::SizeOfCharWithUTF8(char Char)
{
    if (Char < 0){
        if((unsigned char)Char >= 0xE0){
            return 3;
        }
        else if ((unsigned char)Char >= 0xC0 && (unsigned char)Char < 0xE0){
            return 2;
        }
    }

    return 1;
}

std::string CTextFunction::GetNameInFilename(std::string filename)
{
    size_t __last_x_pos = filename.find_last_of('/');
    size_t __last_s_pos = filename.find_last_of('*');
    __last_x_pos = __last_x_pos == std::string::npos ? 0 : __last_x_pos;
    __last_s_pos = __last_s_pos == std::string::npos ? 0 : __last_s_pos;
    std::string __result = "";

    if (__last_s_pos > __last_x_pos)
        __result = filename.substr(__last_s_pos+1);
    else
        __result = filename.substr(__last_x_pos+1);
    
    size_t __last_p_pos = __result.find_last_of('.');
    if (__last_p_pos != std::string::npos)
        __result = __result.substr(0, __last_p_pos);

    return __result;
}

size_t CTextFunction::StringLengthWithUTF8(std::string str)
{
    size_t __index = 0;
    size_t __result = 0;

    while (__index < str.length()){
        __index += SizeOfCharWithUTF8(str[__index]);
        __result++;
    }
    return __result;
}