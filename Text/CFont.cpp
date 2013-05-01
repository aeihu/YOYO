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
	_memFont = NULL;
	_menSize = 0;
}

CFont::~CFont()
{
	Cio::ClearFileInMem(_memFont);
}

/*--------------------------------------------------
读取字体文件
==================================================*/
bool CFont::LoadFont(string filename, unsigned int size)
{
	Cio::ClearFileInMem(_memFont);

	if (!Cio::LoadFileToMem(filename, _memFont, _menSize)){
    cout << "CFont::LoadFont(): failed to load" << filename << "." << endl;
		return false;
	}

	if (!_Font.LoadFromMemory(_memFont, _menSize, size)){
    cout << "CFont::LoadFont(): failed to load."<< endl;
		return false;
	}

  return true;
}

bool CFont::SetCharset(string charset, unsigned int size)
{
	if (_memFont != NULL)
		return _Font.LoadFromMemory(_memFont, _menSize, size, sf::Unicode::Text((const unsigned char *)charset.c_str()));

  cout << "CFont::SetCharset(): _memFont is NULL."<< endl;
	return false;
}
