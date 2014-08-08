/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CGuiCommon.h"
#include <iostream>
#include <cstdio>

using namespace std;

vector<vector<size_t> > CGuiCommon::OnLoad(const char* File)
{    
//===============step.1==============================
    //char File[255] = "";
    vector<vector<size_t> > table;
    FILE* FileHandle = fopen(File, "r");
    
    if(FileHandle != NULL) {
//===============step.2==============================
        char str[255] = "";

        while(fscanf(FileHandle, " %[^\r\n] ", str) != EOF)
        {
            size_t i = 0;
            string s = "%d ";
            vector<size_t> list;
            while(sscanf(str,s.c_str(), &i) != 0){
                list.push_back(i);
                s="%*d "+s;
            }
            table.push_back(list);
        }
    }

  return table;
}

bool CGuiCommon::CreateBoxBackground(sf::Image* Surf_Dest, sf::Image* Surf_Src, const char* File, size_t Tile_Size)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        cout << "CGuiCommon::CreateBoxBackground(): failed to creat surface." << endl;
        return false;
    }

    vector<vector<size_t> > table;
    table = OnLoad(File);
    
    if (table.size() < 1){
        cout << "CGuiCommon::CreateBoxBackground(): form of table is error." << endl;
        return false;
    }

    Surf_Dest->create(table[0].size() * Tile_Size, table.size() * Tile_Size);

    size_t tileset_width = Surf_Src->getSize().x / Tile_Size;

    for (size_t i=0; i<table.size(); i++){
        for (size_t j=0; j<table[i].size(); j++){
            CSurface::OnDraw(Surf_Dest, Surf_Src, 
                j * Tile_Size, 
                i * Tile_Size, 
                (table[i][j] % tileset_width) * Tile_Size, 
                (table[i][j] / tileset_width) * Tile_Size,
                Tile_Size, Tile_Size);
        }
    }
    //Surf_Dest->loadFromImage(__img);

    return true;
}
