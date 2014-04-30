/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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

    APPLY_ALPHA = false;

    MAX_FPS = 60;
    COLOR_KEY_RED =
    COLOR_KEY_GREEN =
    COLOR_KEY_BLUE = 0;



//    ANIMATION_EFFECTS_MOVE_RANGE = 30;
//    ANIMATION_EFFECTS_MOVE_INCREMENT = 2;

    INCREMENT = 10;
    INTERVAL = 15;

    //MAP_WIDTH    = 20;
    //MAP_HEIGHT    = 20;
    //MAP_ANIMATIOM_MAXFRAMES = 4;
    //MAP_ANIMATIOM_FRAMERATE = 500;

    //<config>
    TILE_SIZE    = 32;
    WWIDTH = 800;
    WHEIGHT    =    600;
    FONT_SIZE =  16;
    CHAR_COLOR_RED = 254;
    CHAR_COLOR_GREEN = 254;
    CHAR_COLOR_BLUE = 254;
    CHAR_COLOR_ALPHA = 255;
    FONT_SHADOW = 1;
    CHAR_SHADOW_COLOR_RED = 10;
    CHAR_SHADOW_COLOR_GREEN = 10;
    CHAR_SHADOW_COLOR_BLUE = 10;
    CHAR_SHADOW_COLOR_ALPHA = 120;
    SOUND_POOL_NUM = 5;
    VOICE_POOL_NUM = 3;
    FONT_PATH =  "C://WINDOWS//Fonts//MSGOTHIC.TTC";
    //</config>

    //<option>
    TEXT_FRAMERATE = 10;
    BGM_VOLUME = 10;
    SE_VOLUME = 10;
    //</option>

    MOUSEOVER_SE = "MOUSEOVER";
    MOUSEDOWN_SE = "MOUSEDOWN";
    BOXCLOSED_SE = "BOXCLOSED";

    CHARACTER_LAYER_MOVE_BUFFER = 300.0f;
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
    list<string> __expressions = Cio::LoadTxtFile(CONFIG_PATH, "\r\n");

    for (list<string>::iterator it=__expressions.begin();
        it!=__expressions.end(); it++){
        string __paraName = "";
        string __paraValue = "";
        if(Cio::AnalyticExpression((*it), __paraName, __paraValue))
            SetValue(__paraName.c_str(), __paraValue.c_str());
    }
    __expressions.clear();
    
//===========================================================================
    __expressions = Cio::LoadTxtFile(GAME_SYSDATA, "\r\n");

    for (list<string>::iterator it=__expressions.begin();
        it!=__expressions.end(); it++){
        string __paraName = "";
        string __paraValue = "";
        if(Cio::AnalyticExpression((*it), __paraName, __paraValue))
            _SystemVariableTable[__paraName] = __paraValue;
    }
    
    return true;
}

void CCommon::SetValue(const char* name, const char* value)
{
    if (strcmp(name,"GAME_PATH") == 0)
    {
        GAME_PATH = value;
        return;
    }
    if (strcmp(name,"GAME_NAME") == 0)
    {
        GAME_NAME = value;
        return;
    }
    if (strcmp(name,"GAME_ICON") == 0)
    {
        GAME_ICON = value;
        return;
    }
    if (strcmp(name,"GAME_SYSDATA") == 0)
    {
        GAME_SYSDATA = value;
        return;
    }
    if (strcmp(name,"MAX_FPS") == 0)
    {
        MAX_FPS = atoi(value);
        MAX_FPS = MAX_FPS < 0 ? 0 : MAX_FPS;
        return;
    }
    if (strcmp(name,"COLOR_KEY_RED") == 0)
    {
        COLOR_KEY_RED = atoi(value);

        if (COLOR_KEY_RED > 255)
            COLOR_KEY_RED = 255;
        else if (COLOR_KEY_RED < 0)
            COLOR_KEY_RED = 0;
        return;
    }
    if (strcmp(name,"COLOR_KEY_GREEN") == 0)
    {
        COLOR_KEY_GREEN = atoi(value);

        if (COLOR_KEY_GREEN > 255)
            COLOR_KEY_GREEN = 255;
        else if (COLOR_KEY_GREEN < 0)
            COLOR_KEY_GREEN = 0;
        return;
    }
    if (strcmp(name,"COLOR_KEY_BLUE") == 0)
    {
        COLOR_KEY_BLUE = atoi(value);

        if (COLOR_KEY_BLUE > 255)
            COLOR_KEY_BLUE = 255;
        else if (COLOR_KEY_BLUE < 0)
            COLOR_KEY_BLUE = 0;
        return;
    }
    if (strcmp(name,"CHAR_COLOR_RED") == 0)
    {
        CHAR_COLOR_RED = atoi(value);

        if (CHAR_COLOR_RED > 255)
            CHAR_COLOR_RED = 255;
        else if (CHAR_COLOR_RED < 0)
            CHAR_COLOR_RED = 0;
        return;
    }
    if (strcmp(name,"CHAR_COLOR_GREEN") == 0)
    {
        CHAR_COLOR_GREEN = atoi(value);

        if (CHAR_COLOR_GREEN > 255)
            CHAR_COLOR_GREEN = 255;
        else if (CHAR_COLOR_GREEN < 0)
            CHAR_COLOR_GREEN = 0;
        return;
    }
    if (strcmp(name,"CHAR_COLOR_BLUE") == 0)
    {
        CHAR_COLOR_BLUE = atoi(value);

        if (CHAR_COLOR_BLUE > 255)
            CHAR_COLOR_BLUE = 255;
        else if (CHAR_COLOR_BLUE < 0)
            CHAR_COLOR_BLUE = 0;
        return;
    }
    if (strcmp(name,"CHAR_COLOR_ALPHA") == 0)
    {
        CHAR_COLOR_ALPHA = atoi(value);

        if (CHAR_COLOR_ALPHA > 255)
            CHAR_COLOR_ALPHA = 255;
        else if (CHAR_COLOR_ALPHA < 0)
            CHAR_COLOR_ALPHA = 0;
        return;
    }
    
    if (strcmp(name,"SOUND_POOL_NUM") == 0)
    {
        SOUND_POOL_NUM = atoi(value);

        if (SOUND_POOL_NUM > 50)
            SOUND_POOL_NUM = 50;
        else if (SOUND_POOL_NUM < 0)
            SOUND_POOL_NUM = 5;
        return;
    }

    if (strcmp(name,"VOICE_POOL_NUM") == 0)
    {
        VOICE_POOL_NUM = atoi(value);

        if (VOICE_POOL_NUM > 50)
            VOICE_POOL_NUM = 50;
        else if (VOICE_POOL_NUM < 0)
            VOICE_POOL_NUM = 3;
        return;
    }

    if (strcmp(name,"INCREMENT") == 0)
    {
        INCREMENT = atoi(value);
        INCREMENT = INCREMENT  <= 0 ? 10 : INCREMENT;
        return;
    }
    if (strcmp(name,"INTERVAL") == 0)
    {
        INTERVAL = atoi(value);
        INTERVAL = INTERVAL  < 0 ? 10 : INTERVAL;
        return;
    }

    if (strcmp(name,"TILE_SIZE") == 0)
    {
        TILE_SIZE = atoi(value);
        return;
    }
    if (strcmp(name,"WWIDTH") == 0)
    {
        WWIDTH = atoi(value);
        WWIDTH = WWIDTH  < 0 ? 800 : WWIDTH;
        return;
    }
    if (strcmp(name,"WHEIGHT") == 0)
    {
        WHEIGHT = atoi(value);
        WHEIGHT = WHEIGHT  < 0 ? 600 : WHEIGHT;
        return;
    }
    if (strcmp(name,"FONT_SIZE") == 0)
    {
        FONT_SIZE = atoi(value);
        FONT_SIZE = FONT_SIZE  < 0 ? 16 : FONT_SIZE;
        return;
    }
    if (strcmp(name,"FONT_PATH") == 0)
    {
        FONT_PATH = value;
        return;
    }
    if (strcmp(name,"TEXT_FRAMERATE") == 0)
    {
        TEXT_FRAMERATE = atoi(value);
        return;
    }
    if (strcmp(name,"FONT_SHADOW") == 0)
    {
        FONT_SHADOW = atoi(value);
        return;
    }
    if (strcmp(name,"CHAR_SHADOW_COLOR_RED") == 0)
    {
        CHAR_SHADOW_COLOR_RED = atoi(value);
        if (CHAR_SHADOW_COLOR_RED > 255)
            CHAR_SHADOW_COLOR_RED = 255;
        else if (CHAR_SHADOW_COLOR_RED < 0)
            CHAR_SHADOW_COLOR_RED = 0;
        return;
    }
    if (strcmp(name,"CHAR_SHADOW_COLOR_GREEN") == 0)
    {
        CHAR_SHADOW_COLOR_GREEN = atoi(value);
        if (CHAR_SHADOW_COLOR_GREEN > 255)
            CHAR_SHADOW_COLOR_GREEN = 255;
        else if (CHAR_SHADOW_COLOR_GREEN < 0)
            CHAR_SHADOW_COLOR_GREEN = 0;
        return;
    }
    if (strcmp(name,"CHAR_SHADOW_COLOR_BLUE") == 0)
    {
        CHAR_SHADOW_COLOR_BLUE = atoi(value);
        if (CHAR_SHADOW_COLOR_BLUE > 255)
            CHAR_SHADOW_COLOR_BLUE = 255;
        else if (CHAR_SHADOW_COLOR_BLUE < 0)
            CHAR_SHADOW_COLOR_BLUE = 0;
        return;
    }
    if (strcmp(name,"CHAR_SHADOW_COLOR_ALPHA") == 0)
    {
        CHAR_SHADOW_COLOR_ALPHA = atoi(value);
        if (CHAR_SHADOW_COLOR_ALPHA > 255)
            CHAR_SHADOW_COLOR_ALPHA = 255;
        else if (CHAR_SHADOW_COLOR_ALPHA < 0)
            CHAR_SHADOW_COLOR_ALPHA = 0;
        return;
    }

    if (strcmp(name,"BGM_VOLUME") == 0)
    {
        BGM_VOLUME = atoi(value);
        return;
    }
    if (strcmp(name,"SE_VOLUME") == 0)
    {
        SE_VOLUME = atoi(value);
        return;
    }
    if (strcmp(name,"MOUSEOVER_SE") == 0)
    {
        MOUSEOVER_SE = value;
        return;
    }
    if (strcmp(name,"MOUSEDOWN_SE") == 0)
    {
        MOUSEDOWN_SE = value;
        return;
    }
    if (strcmp(name,"BOXCLOSED_SE") == 0)
    {
        BOXCLOSED_SE = value;
        return;
    }
}

unsigned long CCommon::GetTicks(){
    return __clock.getElapsedTime().asMilliseconds();
}

unsigned int CCommon::SizeOfCharWithUTF8(char Char)
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

void CCommon::SaveSysData()
{
    FILE* File = fopen(GAME_SYSDATA.c_str(), "w");
    map<string, string>::iterator it;
    for ( it=_SystemVariableTable.begin(); it != _SystemVariableTable.end(); it++ )
        fprintf (File, "%s = %s\n",(*it).first.c_str(),(*it).second.c_str());

    fclose (File);
}

void CCommon::OnCleanup()
{
    _PlayerVariableTable.clear();
    _SystemVariableTable.clear();

    //for (int i = 0; i < LogList.size(); i++)
    //{
    //    if (LogList[i] != NULL)
    //    {
    //        SDL_FreeSurface(LogList[i]);
    //        LogList[i] = NULL;
    //    }
    //}

    //LogList.clear();
}
