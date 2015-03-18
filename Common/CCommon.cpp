/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCommon.h"

CCommon CCommon::_Common;

CCommon::CCommon()
{
    //Surf_IconTileset = NULL;
    //GameState = MAP_FOCUS;
    CONFIG_PATH = "./game.config";
    GAME_PATH = "./game/main";
    GAME_NAME = "Game Scenario Maker";
    GAME_ICON = "./icon.ico";
    GAME_SYSDATA = "./sys.dat";

    MAX_FPS = 60;

    //INCREMENT = 500;
    INTERVAL = 15;

    //<config>
    TILE_SIZE    = 32;
    WWIDTH = 800;
    WHEIGHT    =    600;
    FONT_SIZE =  16;
    CHAR_COLOR_RED = 254;
    CHAR_COLOR_GREEN = 254;
    CHAR_COLOR_BLUE = 254;
    CHAR_COLOR_ALPHA = 255;
    //FONT_SHADOW = 1;
    CHAR_SHADOW_COLOR_RED = 10;
    CHAR_SHADOW_COLOR_GREEN = 10;
    CHAR_SHADOW_COLOR_BLUE = 10;
    CHAR_SHADOW_COLOR_ALPHA = 120;
    SOUND_POOL_NUM = 5;
    VOICE_POOL_NUM = 3;
        
    SCREEN_PIECE_NUM = 20;//   16
    //FONT_PATH =  "C://WINDOWS//Fonts//MSGOTHIC.TTC";
    //</config>

    //<option>
    TEXT_FRAMERATE = 10;

    VOICE_VOLUME =
    BGM_VOLUME = 
    SE_VOLUME = 100.0f;
    //</option>

    MOUSEOVER_SE = "MOUSEOVER";
    MOUSEDOWN_SE = "MOUSEDOWN";
    BOXCLOSED_SE = "BOXCLOSED";

    //CHARACTER_LAYER_MOVE_BUFFER = 300.0f;
}

bool CCommon::OnInit()
{
    char BOM[3] = {0xEF,0xBB,0xBF};

    FILE* File = fopen("STARTUP", "r");
    if (File == NULL)
    {
        cout << "CCommon::OnInit(): can't open \"STARTUP\" file." <<endl;
        return false;
    }
    fscanf(File, BOM);
    {
        char c[255];
        fscanf(File, "%[^\r\n]", c);
        CONFIG_PATH = c;
    }
    fclose(File);
//===========================================================================
    
    Object json;
    if (!json.parse(Cio::LoadTxtFile(CONFIG_PATH)))
        return false;
        
    SetValue(json);
    
    return true;
}

void CCommon::SetValue(Object json)
{
    if (json.has<String>("GAME_PATH")) GAME_PATH = json.get<String>("GAME_PATH");
    if (json.has<String>("GAME_NAME")) GAME_NAME = json.get<String>("GAME_NAME");
    if (json.has<String>("GAME_ICON")) GAME_ICON = json.get<String>("GAME_ICON");
    if (json.has<String>("GAME_SYSDATA")) GAME_SYSDATA = json.get<String>("GAME_SYSDATA");

    if (json.has<Number>("MAX_FPS")) MAX_FPS = json.get<Number>("MAX_FPS");
    if (json.has<Number>("INTERVAL")) INTERVAL = json.get<Number>("INTERVAL");
    if (json.has<Number>("TILE_SIZE")) TILE_SIZE = json.get<Number>("TILE_SIZE");
    if (json.has<Number>("WWIDTH")) WWIDTH = json.get<Number>("WWIDTH");
    if (json.has<Number>("WHEIGHT")) WHEIGHT = json.get<Number>("WHEIGHT");
    if (json.has<Number>("INTERVAL")) INTERVAL = json.get<Number>("INTERVAL");
    
    if (json.has<Number>("FONT_SIZE")) FONT_SIZE = json.get<Number>("FONT_SIZE");
    //if (json.has<String>("FONT_PATH")) FONT_PATH = json.get<String>("FONT_PATH");
    if (json.has<Number>("CHAR_COLOR_RED")) CHAR_COLOR_RED = json.get<Number>("CHAR_COLOR_RED");
    if (json.has<Number>("CHAR_COLOR_GREEN")) CHAR_COLOR_GREEN = json.get<Number>("CHAR_COLOR_GREEN");
    if (json.has<Number>("CHAR_COLOR_BLUE")) CHAR_COLOR_BLUE = json.get<Number>("CHAR_COLOR_BLUE");
    if (json.has<Number>("CHAR_COLOR_ALPHA")) CHAR_COLOR_ALPHA = json.get<Number>("CHAR_COLOR_ALPHA");

    if (json.has<Number>("CHAR_SHADOW_COLOR_RED")) CHAR_SHADOW_COLOR_RED = json.get<Number>("CHAR_SHADOW_COLOR_RED");
    if (json.has<Number>("CHAR_SHADOW_COLOR_GREEN")) CHAR_SHADOW_COLOR_GREEN = json.get<Number>("CHAR_SHADOW_COLOR_GREEN");
    if (json.has<Number>("CHAR_SHADOW_COLOR_BLUE")) CHAR_SHADOW_COLOR_BLUE = json.get<Number>("CHAR_SHADOW_COLOR_BLUE");
    if (json.has<Number>("CHAR_SHADOW_COLOR_ALPHA")) CHAR_SHADOW_COLOR_ALPHA = json.get<Number>("CHAR_SHADOW_COLOR_ALPHA");

    if (json.has<Number>("SOUND_POOL_NUM")) SOUND_POOL_NUM = json.get<Number>("SOUND_POOL_NUM");
    if (json.has<Number>("VOICE_POOL_NUM")) VOICE_POOL_NUM = json.get<Number>("VOICE_POOL_NUM");

    if (json.has<Number>("SCREEN_PIECE_NUM")) SCREEN_PIECE_NUM = json.get<Number>("SCREEN_PIECE_NUM");
      
    if (json.has<Number>("TEXT_FRAMERATE")) TEXT_FRAMERATE = json.get<Number>("TEXT_FRAMERATE");
    if (json.has<Number>("BGM_VOLUME")) BGM_VOLUME = json.get<Number>("BGM_VOLUME");
    if (json.has<Number>("SE_VOLUME")) SE_VOLUME = json.get<Number>("SE_VOLUME");
    if (json.has<Number>("VOICE_VOLUME")) VOICE_VOLUME = json.get<Number>("VOICE_VOLUME");
    
    if (json.has<String>("MOUSEOVER_SE")) MOUSEOVER_SE = json.get<String>("MOUSEOVER_SE");
    if (json.has<String>("MOUSEDOWN_SE")) MOUSEDOWN_SE = json.get<String>("MOUSEDOWN_SE");
    if (json.has<String>("BOXCLOSED_SE")) BOXCLOSED_SE = json.get<String>("BOXCLOSED_SE");
    
}

unsigned long CCommon::GetTicks(){
    return __clock.getElapsedTime().asMilliseconds();
}

//void CCommon::SaveSysData()
//{
//    FILE* File = fopen(GAME_SYSDATA.c_str(), "w");
//    map<string, string>::iterator it;
//    for ( it=_SystemVariableTable.begin(); it != _SystemVariableTable.end(); it++ )
//        fprintf (File, "%s = %s\n",(*it).first.c_str(),(*it).second.c_str());
//
//    fclose (File);
//}
//
//void CCommon::OnCleanup()
//{
//    //_PlayerVariableTable.clear();
//    //_SystemVariableTable.clear();
//
//    //for (int i = 0; i < LogList.size(); i++)
//    //{
//    //    if (LogList[i] != NULL)
//    //    {
//    //        SDL_FreeSurface(LogList[i]);
//    //        LogList[i] = NULL;
//    //    }
//    //}
//
//    //LogList.clear();
//}
