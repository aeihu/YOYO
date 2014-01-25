/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CFont.h"

CFont::CFont()
{
    //_memFont = NULL;
    //_menSize = 0;
}

CFont::~CFont()
{
    //Cio::ClearFileInMem(_memFont);
}


bool CFont::LoadFont(string filename)
{
    unsigned long __menSize = 0;
    char*         __memFont = NULL;

    if (!Cio::LoadFileToMem(filename, __memFont, __menSize)){
        cout << "CFont::LoadFont(): failed to load" << filename << "." << endl;
        return false;
    }

    bool __result = _font.loadFromMemory(__memFont, __menSize);
    if (!__result)
        cout << "CFont::LoadFont(): failed to load."<< endl;

    return __result;
}

//bool CFont::SetCharset(string charset)
//{
//    if (_memFont != NULL)
//        return _Font.loadFromMemory(_memFont, _menSize);
//
//    cout << "CFont::SetCharset(): _memFont is NULL."<< endl;
//    return false;
//}
