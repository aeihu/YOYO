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