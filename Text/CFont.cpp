/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CFont.h"

CFont::CFont()
{
    _memFont = NULL;
}

CFont::~CFont()
{
    Cio::ClearFileInMem(_memFont);
}


bool CFont::LoadFont(string filename)
{ 
    if (filename.find("*") == string::npos){
        if (!_font.loadFromFile(filename)){
            cout << "CFont::LoadFont(): failed to load '" << filename << "'" << endl;
            return false;
        }
        else
            return true;
    }
    else {
        char* __mem = NULL;
        unsigned long __size = 0;
        CZlib::OpenFileInZip(filename, __mem, __size);

        if (__mem != NULL){
            if (_font.loadFromMemory(__mem, __size)){

                if (_memFont != NULL){
                    CZlib::CloseFileInZip(__mem);
                }
                _memFont = __mem;
                return true;
            }
            else{
                CZlib::CloseFileInZip(__mem);
                cout << "CFont::LoadFont(): failed to load '" << filename << "'" << endl;
                return false;
            }
        }
        else{
            cout << "CFont::LoadFont(): failed to load '" << filename << "'" << endl;    
            return false;
        }
    }
}

void CFont::SetString(sf::Text& text, std::string str)
{
    sf::Uint32* __uft32String = new sf::Uint32[str.length()];
    sf::Utf8::toUtf32(str.begin(), str.end(), __uft32String);
    text.setString(__uft32String);
    delete[] __uft32String;
}
