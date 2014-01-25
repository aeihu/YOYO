/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CGuiCommon.h"
#include <iostream>
#include <cstdio>

using namespace std;

vector<vector<unsigned int> > CGuiCommon::OnLoad(const char* File)
{    
//===============step.1==============================
    //char File[255] = "";
    vector<vector<unsigned int> > table;
    FILE* FileHandle = fopen(File, "r");
    
    if(FileHandle != NULL) {
//===============step.2==============================
        char str[255] = "";

        while(fscanf(FileHandle, " %[^\r\n] ", str) != EOF)
        {
            unsigned int i = 0;
            string s = "%d ";
            vector<unsigned int> list;
            while(sscanf(str,s.c_str(), &i) != 0){
                list.push_back(i);
                s="%*d "+s;
            }
            table.push_back(list);
        }
    }

  return table;
}

bool CGuiCommon::CreateBoxBackground(CImage* Surf_Dest, sf::Image* Surf_Src, const char* File, unsigned int Tile_Size)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        cout << "CGuiCommon::CreateBoxBackground(): failed to creat surface." << endl;
        return false;
    }

    vector<vector<unsigned int> > table;
    table = OnLoad(File);
    
    if (table.size() < 1){
        cout << "CGuiCommon::CreateBoxBackground(): form of table is error." << endl;
        return false;
    }
    sf::Image __img;
    __img.create(table[0].size() * Tile_Size, table.size() * Tile_Size);
    //Surf_Dest->create(table[0].size() * Tile_Size, table.size() * Tile_Size);

    unsigned int tileset_width = Surf_Src->getSize().x / Tile_Size;

    for (int i=0; i<table.size(); i++){
        for (int j=0; j<table[i].size(); j++){
            CSurface::OnDraw(&__img, Surf_Src, 
                j * Tile_Size, 
                i * Tile_Size, 
                (table[i][j] % tileset_width) * Tile_Size, 
                (table[i][j] / tileset_width) * Tile_Size,
                Tile_Size, Tile_Size);
        }
    }
    Surf_Dest->LoadFromImage(__img);

    return true;
}
