/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CCommon.h"

CCommon CCommon::common;

CCommon::CCommon()
{
    //Surf_IconTileset = NULL;
    //GameState = MAP_FOCUS;
    CONFIG_PATH = "./game.config";
    GAME_PATH = "./game/main";
    GAME_NAME = "RPG %d";
    GAME_ICON = "./icon.ico";
    GAME_SYSDATA = "./sys.dat";

    APPLY_ALPHA = false;

    MAX_FRAME = 35;
    COLOR_KEY_RED =
    COLOR_KEY_GREEN =
    COLOR_KEY_BLUE = 0;

    ITEM_DATA_PATH =
    EQUIP_DATA_PATH = 
    MAGIC_DATA_PATH = 
    SKILL_DATA_PATH = "./data/data.xml";
    MONSTER_DATA_PATH = "./data/monster.xml";

    ICON_PATH = "./tilesets/icon.png";
    ICON_SIZE = 16;
    
    ANIMATION_EFFECTS_MOVE_RANGE = 30;
    ANIMATION_EFFECTS_MOVE_INCREMENT = 2;
    BOX_ANIMATION_INTERVAL = 10;

    MAP_WIDTH    = 20;
    MAP_HEIGHT    = 20;
    MAP_ANIMATIOM_MAXFRAMES = 4;
    MAP_ANIMATIOM_FRAMERATE = 500;

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
    FONT_PATH =  "C://WINDOWS//Fonts//MSGOTHIC.TTC";
    //</config>

    //<option>
    TEXT_FRAMERATE = 10;
    BGM_VOLUME = 10;
    SE_VOLUME = 10;
    //</option>
    BATTLE_PLAYER_POSTION1_X = 530;
    BATTLE_PLAYER_POSTION1_Y = 50;
    BATTLE_PLAYER_POSTION2_X = 530;
    BATTLE_PLAYER_POSTION2_Y = 150;
    BATTLE_PLAYER_POSTION3_X = 530;
    BATTLE_PLAYER_POSTION3_Y = 250;
    BATTLE_PLAYER_POSTION4_X = 530;
    BATTLE_PLAYER_POSTION4_Y = 350;

    BATTLE_ENEMY_POSTION1_X = 30;
    BATTLE_ENEMY_POSTION1_Y = 50;
    BATTLE_ENEMY_POSTION2_X = 30;
    BATTLE_ENEMY_POSTION2_Y = 150;
    BATTLE_ENEMY_POSTION3_X = 30;
    BATTLE_ENEMY_POSTION3_Y = 250;
    BATTLE_ENEMY_POSTION4_X = 30;
    BATTLE_ENEMY_POSTION4_Y = 350;
    BATTLE_ENEMY_POSTION5_X = 130;
    BATTLE_ENEMY_POSTION5_Y = 50;
    BATTLE_ENEMY_POSTION6_X = 130;
    BATTLE_ENEMY_POSTION6_Y = 150;
    BATTLE_ENEMY_POSTION7_X = 130;
    BATTLE_ENEMY_POSTION7_Y = 250;
    BATTLE_ENEMY_POSTION8_X = 130;
    BATTLE_ENEMY_POSTION8_Y = 350;

    BOX_TILE_SIZE = 16;
    WALK_SPEED = 5;

    MOUSEOVER_SE = "MOUSEOVER";
    MOUSEDOWN_SE = "MOUSEDOWN";
    BOXCLOSED_SE = "BOXCLOSED";

    MSGBOX_TILESETS_PATH = "./tilesets/12indow.png";
    MSGBOX_TABLE_PATH = "";
    MSGBOX_LOCATION_Y = 300;
    MSGBOX_MSG_OFFSET_X = 16;
    MSGBOX_MSG_OFFSET_Y = 32;
    MSGBOX_MSG_WIDTH = 36;// 10
    MSGBOX_MSG_HEIGHT = 5;// 10
    MSGBOX_SPEAKER_OFFSET_X = 16;
    MSGBOX_SPEAKER_OFFSET_Y = 16;
    MSGBOX_CURSOR_OFFSET_X = 16;
    MSGBOX_CURSOR_OFFSET_Y = 16;
    MSGBOX_CURSOR_SIZE = 16;
    MSGBOX_CURSOR_TILE = 16;
    MSGBOX_CURSOR_FRAMERATE = 500;
    MSGBOX_CURSOR_MAX_FRAMES = 4;
    MSGBOX_WIDTH = 38;
    MSGBOX_HEIGHT = 8;
    MSGBOX_TILE_TOP = 9;
    MSGBOX_TILE_BOTTOM = 45;
    MSGBOX_TILE_LEFT = 20;
    MSGBOX_TILE_RIGHT = 23;
    MSGBOX_TILE_TOPLEFT = 8;
    MSGBOX_TILE_TOPRIGHT = 11;
    MSGBOX_TILE_BOTTOMLEFT = 44;
    MSGBOX_TILE_BOTTOMRIGHT = 47;
    MSGBOX_TILE_FILLER = 3;
    MSGBOX_TILE_FILLER_SIZE = 32;
    MSGBOX_ANIMATION_TYPE = 1;

    INFOBOX_TILESETS_PATH = "./tilesets/12indow.png";
    INFOBOX_LOCATION_X = 10;
    INFOBOX_LOCATION_Y = 300;
    INFOBOX_INFO_OFFSET_X = 16;
    INFOBOX_INFO_OFFSET_Y = 16;
    INFOBOX_WIDTH = 10;
    INFOBOX_HEIGHT = 8;
    INFOBOX_TILE_TOP = 9;
    INFOBOX_TILE_BOTTOM = 45;
    INFOBOX_TILE_LEFT = 20;
    INFOBOX_TILE_RIGHT = 23;
    INFOBOX_TILE_TOPLEFT = 8;
    INFOBOX_TILE_TOPRIGHT = 11;
    INFOBOX_TILE_BOTTOMLEFT = 44;
    INFOBOX_TILE_BOTTOMRIGHT = 47;
    INFOBOX_TILE_FILLER = 32;
    INFOBOX_TILE_FILLER_SIZE = 32;
    INFOBOX_ANIMATION_TYPE = 1;

    LISTBOX_TILESETS_PATH = "./tilesets/12indow.png";
    LISTBOX_LOCATION_X = 10;
    LISTBOX_LOCATION_Y = 300;
    LISTBOX_INFO_OFFSET_X = 16;
    LISTBOX_INFO_OFFSET_Y = 16;
    LISTBOX_WIDTH = 38;
    LISTBOX_HEIGHT = 8;
    LISTBOX_TILE_TOP = 9;
    LISTBOX_TILE_BOTTOM = 45;
    LISTBOX_TILE_LEFT = 20;
    LISTBOX_TILE_RIGHT = 23;
    LISTBOX_TILE_TOPLEFT = 8;
    LISTBOX_TILE_TOPRIGHT = 11;
    LISTBOX_TILE_BOTTOMLEFT = 44;
    LISTBOX_TILE_BOTTOMRIGHT = 47;
    LISTBOX_TILE_FILLER = 32;
    LISTBOX_TILE_FILLER_SIZE = 32;
    LISTBOX_ANIMATION_TYPE = 1;

    MENUBOX_TILESETS_PATH = "./tilesets/12indow.png";
    MENUBOX_LOCATION_X = 10;
    MENUBOX_LOCATION_Y = 10;
    MENUBOX_INFO_OFFSET_X = 16;
    MENUBOX_INFO_OFFSET_Y = 16;
    MENUBOX_WIDTH = 15;
    MENUBOX_HEIGHT = 8;
    MENUBOX_TILE_TOP = 9;
    MENUBOX_TILE_BOTTOM = 45;
    MENUBOX_TILE_LEFT = 20;
    MENUBOX_TILE_RIGHT = 23;
    MENUBOX_TILE_TOPLEFT = 8;
    MENUBOX_TILE_TOPRIGHT = 11;
    MENUBOX_TILE_BOTTOMLEFT = 44;
    MENUBOX_TILE_BOTTOMRIGHT = 47;
    MENUBOX_TILE_FILLER = 32;
    MENUBOX_TILE_FILLER_SIZE = 32;
    MENUBOX_TILE_SELECTEDITEM = 6;
    MENUBOX_TILE_UPARROW = 58;
    MENUBOX_TILE_DOWNARROW = 58;
    MENUBOX_TILE_BAR = 6;
    MENUBOX_ANIMATION_TYPE = 1;

    LOGBOX_TILESETS_PATH = "./tilesets/12indow.png";
    LOGBOX_LOCATION_X = 10;
    LOGBOX_LOCATION_Y = 10;
    LOGBOX_INFO_OFFSET_X = 10;
    LOGBOX_INFO_OFFSET_Y = 10;
    LOGBOX_WIDTH = 60;
    LOGBOX_HEIGHT = 60;
    LOGBOX_TILE_TOP = 10;
    LOGBOX_TILE_BOTTOM = 10;
    LOGBOX_TILE_LEFT = 10;
    LOGBOX_TILE_RIGHT = 10;
    LOGBOX_TILE_TOPLEFT = 10;
    LOGBOX_TILE_TOPRIGHT = 10;
    LOGBOX_TILE_BOTTOMLEFT = 10;
    LOGBOX_TILE_BOTTOMRIGHT = 10;
    LOGBOX_TILE_FILLER = 10;
    LOGBOX_TILE_FILLER_SIZE = 10;
    LOGBOX_TILE_UPARROW = 10;
    LOGBOX_TILE_DOWNARROW = 10;
    LOGBOX_TILE_BAR = 10;
    LOGBOX_ANIMATION_TYPE = 0;
    
    GALLERYBOX_TILESETS_PATH = "./tilesets/12indow.png";
    GALLERYBOX_LOCATION_X = 10;
    GALLERYBOX_LOCATION_Y = 10;
    GALLERYBOX_INFO_OFFSET_X = 10;
    GALLERYBOX_INFO_OFFSET_Y = 10;
    GALLERYBOX_WIDTH = 15;// 15
    GALLERYBOX_HEIGHT = 8;// 8
    GALLERYBOX_IMAGE_WIDTH = 8;// 15
    GALLERYBOX_IMAGE_HEIGHT = 8;// 8
    GALLERYBOX_INFO_WIDTH = 8;// 15
    GALLERYBOX_INFO_HEIGHT = 8;// 8

    BOX_ALPHA_INCREMENT = 10;//    25
    BOX_ALPHA_INTERVAL = 25;//    25

    IMAGELAYER_ALPHA_INCREMENT = 10;//    25
    IMAGELAYER_ALPHA_INTERVAL = 25;//    25
    IMAGELAYER_X = 0.0f;
    IMAGELAYER_Y = 0.0f;

    BACKGROUNDLAYER_ALPHA_INCREMENT = 10;//    25
    BACKGROUNDLAYER_ALPHA_INTERVAL = 25;//    25
    BACKGROUNDLAYER_X = 0.0f;//    0
    BACKGROUNDLAYER_Y = 0.0f;//    0

    CHARACTERLAYER_MOVE_BUFFER = 100.0f;
    CHARACTERLAYER_MOVE_INCREMENT = 5.0f;
    CHARACTERLAYER_HEIGHT = 10;

    CHARACTERLAYER_LEFT_L_X    = 10;
    CHARACTERLAYER_LEFT_L_Y    = 240;
    CHARACTERLAYER_LEFT_M_X = 100;
    CHARACTERLAYER_LEFT_M_Y = 240;
    CHARACTERLAYER_MIDDLE_X    = 400;
    CHARACTERLAYER_MIDDLE_Y    = 240;
    CHARACTERLAYER_RIGHT_Q_X = 500;
    CHARACTERLAYER_RIGHT_Q_Y = 240;
    CHARACTERLAYER_RIGHT_R_X = 600;
    CHARACTERLAYER_RIGHT_R_Y = 240;

    MAX_PLAYER_NUM    = 1;
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
            SystemVariableTable[__paraName] = __paraValue;
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
        GAME_NAME += " %d";
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
    if (strcmp(name,"MAX_FRAME") == 0)
    {
        MAX_FRAME = atoi(value);
        MAX_FRAME = MAX_FRAME < 0 ? 0 : MAX_FRAME;
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

    if (strcmp(name,"ITEM_DATA_PATH") == 0)
    {
        ITEM_DATA_PATH = value;
        return;
    }
    if (strcmp(name,"EQUIP_DATA_PATH") == 0)
    {
        EQUIP_DATA_PATH = value;
        return;
    }
    if (strcmp(name,"MAGIC_DATA_PATH") == 0)
    {
        MAGIC_DATA_PATH = value;
        return;
    }
    if (strcmp(name,"SKILL_DATA_PATH") == 0)
    {
        SKILL_DATA_PATH = value;
        return;
    }
    if (strcmp(name,"MONSTER_DATA_PATH") == 0)
    {
        MONSTER_DATA_PATH = value;
        return;
    }
    if (strcmp(name,"ICON_PATH") == 0)
    {
        ICON_PATH = value;
        
        //if (Surf_IconTileset != NULL)
        //{
        //    SDL_FreeSurface(Surf_IconTileset);
        //    Surf_IconTileset = NULL;
        //}

        //Surf_IconTileset = CSurface::OnLoad(ICON_PATH.c_str());

        //CSurface::Transparent(Surf_IconTileset,
        //    CCommon::common.COLOR_KEY_RED, 
        //    CCommon::common.COLOR_KEY_GREEN,
        //    CCommon::common.COLOR_KEY_BLUE);
        return;
    }
    if (strcmp(name,"ICON_SIZE") == 0)
    {
        ICON_SIZE = atoi(value);
        ICON_SIZE = ICON_SIZE  < 0 ? 0 : ICON_SIZE;
        return;
    }
    if (strcmp(name,"ANIMATION_EFFECTS_MOVE_RANGE") == 0)
    {
        ICON_SIZE = atoi(value);
        ICON_SIZE = ICON_SIZE  < 0 ? 0 : ICON_SIZE;
        return;
    }
    if (strcmp(name,"ANIMATION_EFFECTS_MOVE_INCREMENT") == 0)
    {
        ICON_SIZE = atoi(value);
        ICON_SIZE = ICON_SIZE  < 1 ? 1 : ICON_SIZE;
        return;
    }    
    if (strcmp(name,"BOX_ANIMATION_INTERVAL") == 0)
    {
        BOX_ANIMATION_INTERVAL = atoi(value);
        return;
    }
    if (strcmp(name,"MAP_WIDTH") == 0)
    {
        MAP_WIDTH = atoi(value);
        return;
    }
    if (strcmp(name,"MAP_HEIGHT") == 0)
    {
        MAP_HEIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"MAP_ANIMATIOM_MAXFRAMES") == 0)
    {
        MAP_ANIMATIOM_MAXFRAMES = atoi(value);
        return;
    }
    if (strcmp(name,"MAP_ANIMATIOM_FRAMERATE") == 0)
    {
        MAP_ANIMATIOM_FRAMERATE = atoi(value);
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
    if (strcmp(name,"BATTLE_PLAYER_POSTION1_X") == 0)
    {
        BATTLE_PLAYER_POSTION1_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_PLAYER_POSTION1_Y") == 0)
    {
        BATTLE_PLAYER_POSTION1_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_PLAYER_POSTION2_X") == 0)
    {
        BATTLE_PLAYER_POSTION2_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_PLAYER_POSTION2_Y") == 0)
    {
        BATTLE_PLAYER_POSTION2_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_PLAYER_POSTION3_X") == 0)
    {
        BATTLE_PLAYER_POSTION3_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_PLAYER_POSTION3_Y") == 0)
    {
        BATTLE_PLAYER_POSTION3_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_PLAYER_POSTION4_X") == 0)
    {
        BATTLE_PLAYER_POSTION4_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_PLAYER_POSTION4_Y") == 0)
    {
        BATTLE_PLAYER_POSTION4_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION1_X") == 0)
    {
        BATTLE_ENEMY_POSTION1_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION1_Y") == 0)
    {
        BATTLE_ENEMY_POSTION1_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION2_X") == 0)
    {
        BATTLE_ENEMY_POSTION2_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION2_Y") == 0)
    {
        BATTLE_ENEMY_POSTION2_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION3_X") == 0)
    {
        BATTLE_ENEMY_POSTION3_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION3_Y") == 0)
    {
        BATTLE_ENEMY_POSTION3_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION4_X") == 0)
    {
        BATTLE_ENEMY_POSTION4_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION4_Y") == 0)
    {
        BATTLE_ENEMY_POSTION4_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION5_X") == 0)
    {
        BATTLE_ENEMY_POSTION5_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION5_Y") == 0)
    {
        BATTLE_ENEMY_POSTION5_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION6_X") == 0)
    {
        BATTLE_ENEMY_POSTION6_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION6_Y") == 0)
    {
        BATTLE_ENEMY_POSTION6_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION7_X") == 0)
    {
        BATTLE_ENEMY_POSTION7_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION7_Y") == 0)
    {
        BATTLE_ENEMY_POSTION7_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION8_X") == 0)
    {
        BATTLE_ENEMY_POSTION8_X = atoi(value);
        return;
    }
    if (strcmp(name,"BATTLE_ENEMY_POSTION8_Y") == 0)
    {
        BATTLE_ENEMY_POSTION8_Y = atoi(value);
        return;
    }
    if (strcmp(name,"BOX_TILE_SIZE") == 0)
    {
        BOX_TILE_SIZE = atoi(value);
        return;
    }
    if (strcmp(name,"WALK_SPEED ") == 0)
    {
        WALK_SPEED = atoi(value);
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
    if (strcmp(name,"MSGBOX_TILESETS_PATH") == 0)
    {
        MSGBOX_TILESETS_PATH = value;
        return;
    }
    if (strcmp(name,"MSGBOX_TABLE_PATH") == 0)
    {
        MSGBOX_TABLE_PATH = value;
        return;
    }
    if (strcmp(name,"MSGBOX_LOCATION_X") == 0)
    {
        MSGBOX_LOCATION_X = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_LOCATION_Y") == 0)
    {
        MSGBOX_LOCATION_Y = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_MSG_OFFSET_X") == 0)
    {
        MSGBOX_MSG_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_MSG_OFFSET_Y") == 0)
    {
        MSGBOX_MSG_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_MSG_WIDTH") == 0)
    {
        MSGBOX_MSG_WIDTH = (unsigned int)atoi(value);
        MSGBOX_MSG_WIDTH = MSGBOX_MSG_WIDTH < 0 ? 0 : MSGBOX_MSG_WIDTH;
        return;
    }
    if (strcmp(name,"MSGBOX_MSG_HEIGHT") == 0)
    {
        MSGBOX_MSG_HEIGHT = (unsigned int)atoi(value);
        MSGBOX_MSG_HEIGHT = MSGBOX_MSG_HEIGHT < 0 ? 0 : MSGBOX_MSG_HEIGHT;
        return;
    }
    if (strcmp(name,"MSGBOX_SPEAKER_OFFSET_X") == 0)
    {
        MSGBOX_SPEAKER_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_SPEAKER_OFFSET_Y") == 0)
    {
        MSGBOX_SPEAKER_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_CURSOR_OFFSET_X") == 0)
    {
        MSGBOX_CURSOR_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_CURSOR_OFFSET_Y") == 0)
    {
        MSGBOX_CURSOR_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_CURSOR_SIZE") == 0)
    {
        MSGBOX_CURSOR_SIZE = atoi(value);
        MSGBOX_CURSOR_SIZE = MSGBOX_CURSOR_SIZE < 0 ? 0 : MSGBOX_CURSOR_SIZE;
        return;
    }
    if (strcmp(name,"MSGBOX_CURSOR_TILE") == 0)
    {
        MSGBOX_CURSOR_TILE = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_CURSOR_FRAMERATE") == 0)
    {
        MSGBOX_CURSOR_FRAMERATE = atoi(value);
        MSGBOX_CURSOR_FRAMERATE = MSGBOX_CURSOR_FRAMERATE < 1 ? 1 : MSGBOX_CURSOR_FRAMERATE;
        return;
    }
    if (strcmp(name,"MSGBOX_CURSOR_MAX_FRAMES") == 0)
    {
        MSGBOX_CURSOR_MAX_FRAMES = atoi(value);
        MSGBOX_CURSOR_MAX_FRAMES = MSGBOX_CURSOR_MAX_FRAMES < 1 ? 1 : MSGBOX_CURSOR_MAX_FRAMES;
        return;
    }

    if (strcmp(name,"MSGBOX_WIDTH") == 0)
    {
        MSGBOX_WIDTH = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_HEIGHT") == 0)
    {
        MSGBOX_HEIGHT = atoi(value);
        return;
    }
    //if (strcmp(name,"MSGBOX_ANIMATION_INTERVAL") == 0)
    //{
    //    MSGBOX_ANIMATION_INTERVAL = atoi(value);
    //    return;
    //}
    if (strcmp(name,"MSGBOX_TILE_TOP") == 0)
    {
        MSGBOX_TILE_TOP = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_BOTTOM") == 0)
    {
        MSGBOX_TILE_BOTTOM = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_LEFT") == 0)
    {
        MSGBOX_TILE_LEFT = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_RIGHT") == 0)
    {
        MSGBOX_TILE_RIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_TOPLEFT") == 0)
    {
        MSGBOX_TILE_TOPLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_TOPRIGHT") == 0)
    {
        MSGBOX_TILE_TOPRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_BOTTOMLEFT") == 0)
    {
        MSGBOX_TILE_BOTTOMLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_BOTTOMRIGHT") == 0)
    {
        MSGBOX_TILE_BOTTOMRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_FILLER") == 0)
    {
        MSGBOX_TILE_FILLER = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_TILE_FILLER_SIZE") == 0)
    {
        MSGBOX_TILE_FILLER_SIZE = atoi(value);
        return;
    }
    if (strcmp(name,"MSGBOX_ANIMATION_TYPE") == 0)
    {
        MSGBOX_ANIMATION_TYPE = atoi(value);

        if (MSGBOX_ANIMATION_TYPE < 0 || MSGBOX_ANIMATION_TYPE > 4)
            MSGBOX_ANIMATION_TYPE = 0;
        return;
    }
    if (strcmp(name,"INFOBOX_TILESETS_PATH") == 0)
    {
        INFOBOX_TILESETS_PATH = value;
        return;
    }
    if (strcmp(name,"INFOBOX_LOCATION_X") == 0)
    {
        INFOBOX_LOCATION_X = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_LOCATION_Y") == 0)
    {
        INFOBOX_LOCATION_Y = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_INFO_OFFSET_X") == 0)
    {
        INFOBOX_INFO_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_INFO_OFFSET_Y") == 0)
    {
        INFOBOX_INFO_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_WIDTH") == 0)
    {
        INFOBOX_WIDTH = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_HEIGHT") == 0)
    {
        INFOBOX_HEIGHT = atoi(value);
        return;
    }
    //if (strcmp(name,"INFOBOX_ANIMATION_INTERVAL") == 0)
    //{
    //    INFOBOX_ANIMATION_INTERVAL = atoi(value);
    //    return;
    //}
    if (strcmp(name,"INFOBOX_TILE_TOP") == 0)
    {
        INFOBOX_TILE_TOP = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_BOTTOM") == 0)
    {
        INFOBOX_TILE_BOTTOM = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_LEFT") == 0)
    {
        INFOBOX_TILE_LEFT = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_RIGHT") == 0)
    {
        INFOBOX_TILE_RIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_TOPLEFT") == 0)
    {
        INFOBOX_TILE_TOPLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_TOPRIGHT") == 0)
    {
        INFOBOX_TILE_TOPRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_BOTTOMLEFT") == 0)
    {
        INFOBOX_TILE_BOTTOMLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_BOTTOMRIGHT") == 0)
    {
        INFOBOX_TILE_BOTTOMRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_FILLER") == 0)
    {
        INFOBOX_TILE_FILLER = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_TILE_FILLER_SIZE") == 0)
    {
        INFOBOX_TILE_FILLER_SIZE = atoi(value);
        return;
    }
    if (strcmp(name,"INFOBOX_ANIMATION_TYPE") == 0)
    {
        INFOBOX_ANIMATION_TYPE = atoi(value);

        if (INFOBOX_ANIMATION_TYPE < 0 || INFOBOX_ANIMATION_TYPE > 4)
            INFOBOX_ANIMATION_TYPE = 0;
        return;
    }
    if (strcmp(name,"LISTBOX_TILESETS_PATH") == 0)
    {
        LISTBOX_TILESETS_PATH = value;
        return;
    }
    if (strcmp(name,"LISTBOX_LOCATION_X") == 0)
    {
        LISTBOX_LOCATION_X = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_LOCATION_Y") == 0)
    {
        LISTBOX_LOCATION_Y = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_INFO_OFFSET_X") == 0)
    {
        LISTBOX_INFO_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_INFO_OFFSET_Y") == 0)
    {
        LISTBOX_INFO_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_WIDTH") == 0)
    {
        LISTBOX_WIDTH = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_HEIGHT") == 0)
    {
        LISTBOX_HEIGHT = atoi(value);
        return;
    }
    //if (strcmp(name,"LISTBOX_ANIMATION_INTERVAL") == 0)
    //{
    //    LISTBOX_ANIMATION_INTERVAL = atoi(value);
    //    return;
    //}
    if (strcmp(name,"LISTBOX_TILE_TOP") == 0)
    {
        LISTBOX_TILE_TOP = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_BOTTOM") == 0)
    {
        LISTBOX_TILE_BOTTOM = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_LEFT") == 0)
    {
        LISTBOX_TILE_LEFT = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_RIGHT") == 0)
    {
        LISTBOX_TILE_RIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_TOPLEFT") == 0)
    {
        LISTBOX_TILE_TOPLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_TOPRIGHT") == 0)
    {
        LISTBOX_TILE_TOPRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_BOTTOMLEFT") == 0)
    {
        LISTBOX_TILE_BOTTOMLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_BOTTOMRIGHT") == 0)
    {
        LISTBOX_TILE_BOTTOMRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_FILLER") == 0)
    {
        LISTBOX_TILE_FILLER = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_TILE_FILLER_SIZE") == 0)
    {
        LISTBOX_TILE_FILLER_SIZE = atoi(value);
        return;
    }
    if (strcmp(name,"LISTBOX_ANIMATION_TYPE") == 0)
    {
        LISTBOX_ANIMATION_TYPE = atoi(value);

        if (LISTBOX_ANIMATION_TYPE < 0 || LISTBOX_ANIMATION_TYPE > 4)
            LISTBOX_ANIMATION_TYPE = 0;
        return;
    }
    if (strcmp(name,"MENUBOX_TILESETS_PATH") == 0)
    {
        MENUBOX_TILESETS_PATH = value;
        return;
    }
    if (strcmp(name,"MENUBOX_LOCATION_X") == 0)
    {
        MENUBOX_LOCATION_X = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_LOCATION_Y") == 0)
    {
        MENUBOX_LOCATION_Y = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_INFO_OFFSET_X") == 0)
    {
        MENUBOX_INFO_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_INFO_OFFSET_Y") == 0)
    {
        MENUBOX_INFO_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_WIDTH") == 0)
    {
        MENUBOX_WIDTH = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_HEIGHT") == 0)
    {
        MENUBOX_HEIGHT = atoi(value);
        return;
    }
    //if (strcmp(name,"MENUBOX_ANIMATION_INTERVAL") == 0)
    //{
    //    MENUBOX_ANIMATION_INTERVAL = atoi(value);
    //    return;
    //}
    if (strcmp(name,"MENUBOX_TILE_TOP") == 0)
    {
        MENUBOX_TILE_TOP = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_BOTTOM") == 0)
    {
        MENUBOX_TILE_BOTTOM = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_LEFT") == 0)
    {
        MENUBOX_TILE_LEFT = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_RIGHT") == 0)
    {
        MENUBOX_TILE_RIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_TOPLEFT") == 0)
    {
        MENUBOX_TILE_TOPLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_TOPRIGHT") == 0)
    {
        MENUBOX_TILE_TOPRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_BOTTOMLEFT") == 0)
    {
        MENUBOX_TILE_BOTTOMLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_BOTTOMRIGHT") == 0)
    {
        MENUBOX_TILE_BOTTOMRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_UPARROW") == 0)
    {
        MENUBOX_TILE_UPARROW = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_DOWNARROW") == 0)
    {
        MENUBOX_TILE_DOWNARROW = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_FILLER") == 0)
    {
        MENUBOX_TILE_FILLER = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_FILLER_SIZE") == 0)
    {
        MENUBOX_TILE_FILLER_SIZE = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_SELECTEDITEM") == 0)
    {
        MENUBOX_TILE_SELECTEDITEM = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_TILE_BAR") == 0)
    {
        MENUBOX_TILE_BAR = atoi(value);
        return;
    }
    if (strcmp(name,"MENUBOX_ANIMATION_TYPE") == 0)
    {
        MENUBOX_ANIMATION_TYPE = atoi(value);

        if (MENUBOX_ANIMATION_TYPE < 0 || MENUBOX_ANIMATION_TYPE > 4)
            MENUBOX_ANIMATION_TYPE = 0;
        return;
    }

    if (strcmp(name,"LOGBOX_TILESETS_PATH") == 0)
    {
        LOGBOX_TILESETS_PATH = value;
        return;
    }
    if (strcmp(name,"LOGBOX_LOCATION_X") == 0)
    {
        LOGBOX_LOCATION_X = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_LOCATION_Y") == 0)
    {
        LOGBOX_LOCATION_Y = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_INFO_OFFSET_X") == 0)
    {
        LOGBOX_INFO_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_INFO_OFFSET_Y") == 0)
    {
        LOGBOX_INFO_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_WIDTH") == 0)
    {
        LOGBOX_WIDTH = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_HEIGHT") == 0)
    {
        LOGBOX_HEIGHT = atoi(value);
        return;
    }
    //if (strcmp(name,"LOGBOX_ANIMATION_INTERVAL") == 0)
    //{
    //    LOGBOX_ANIMATION_INTERVAL = atoi(value);
    //    return;
    //}
    if (strcmp(name,"LOGBOX_TILE_TOP") == 0)
    {
        LOGBOX_TILE_TOP = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_BOTTOM") == 0)
    {
        LOGBOX_TILE_BOTTOM = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_LEFT") == 0)
    {
        LOGBOX_TILE_LEFT = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_RIGHT") == 0)
    {
        LOGBOX_TILE_RIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_TOPLEFT") == 0)
    {
        LOGBOX_TILE_TOPLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_TOPRIGHT") == 0)
    {
        LOGBOX_TILE_TOPRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_BOTTOMLEFT") == 0)
    {
        LOGBOX_TILE_BOTTOMLEFT = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_BOTTOMRIGHT") == 0)
    {
        LOGBOX_TILE_BOTTOMRIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_FILLER") == 0)
    {
        LOGBOX_TILE_FILLER = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_FILLER_SIZE") == 0)
    {
        LOGBOX_TILE_FILLER_SIZE = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_UPARROW") == 0)
    {
        LOGBOX_TILE_UPARROW = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_DOWNARROW") == 0)
    {
        LOGBOX_TILE_DOWNARROW = atoi(value);
        return;
    }
    if (strcmp(name,"LOGBOX_TILE_BAR") == 0)
    {
        LOGBOX_TILE_BAR = atoi(value);
        return;
    }

    if (strcmp(name,"LOGBOX_ANIMATION_TYPE") == 0)
    {
        LOGBOX_ANIMATION_TYPE = atoi(value);

        if (LOGBOX_ANIMATION_TYPE < 0 || LOGBOX_ANIMATION_TYPE > 4)
            LOGBOX_ANIMATION_TYPE = 0;
        return;
    }
    
    if (strcmp(name,"GALLERYBOX_TILESETS_PATH") == 0)
    {
        GALLERYBOX_TILESETS_PATH = value;
        return;
    }
    if (strcmp(name,"GALLERYBOX_LOCATION_X") == 0)
    {
        GALLERYBOX_LOCATION_X = atoi(value);
        return;
    }
    if (strcmp(name,"GALLERYBOX_LOCATION_Y") == 0)
    {
        GALLERYBOX_LOCATION_Y = atoi(value);
        return;
    }
    if (strcmp(name,"GALLERYBOX_INFO_OFFSET_X") == 0)
    {
        GALLERYBOX_INFO_OFFSET_X = atoi(value);
        return;
    }
    if (strcmp(name,"GALLERYBOX_INFO_OFFSET_Y") == 0)
    {
        GALLERYBOX_INFO_OFFSET_Y = atoi(value);
        return;
    }
    if (strcmp(name,"GALLERYBOX_WIDTH") == 0)
    {
        GALLERYBOX_WIDTH = atoi(value);
        GALLERYBOX_WIDTH = GALLERYBOX_WIDTH < 1 ? 1 : GALLERYBOX_WIDTH;
        return;
    }
    if (strcmp(name,"GALLERYBOX_HEIGHT") == 0)
    {
        GALLERYBOX_HEIGHT = atoi(value);
        GALLERYBOX_HEIGHT = GALLERYBOX_HEIGHT < 1 ? 1 : GALLERYBOX_HEIGHT;
        return;
    }
    if (strcmp(name,"GALLERYBOX_IMAGE_WIDTH") == 0)
    {
        GALLERYBOX_IMAGE_WIDTH = atoi(value);
        GALLERYBOX_IMAGE_WIDTH = GALLERYBOX_IMAGE_WIDTH < 1 ? 1 : GALLERYBOX_IMAGE_WIDTH;
        return;
    }
    if (strcmp(name,"GALLERYBOX_IMAGE_HEIGHT") == 0)
    {
        GALLERYBOX_IMAGE_HEIGHT = atoi(value);
        GALLERYBOX_IMAGE_HEIGHT = GALLERYBOX_IMAGE_HEIGHT < 1 ? 1 : GALLERYBOX_IMAGE_HEIGHT;
        return;
    }
    if (strcmp(name,"GALLERYBOX_INFO_WIDTH") == 0)
    {
        GALLERYBOX_INFO_WIDTH = atoi(value);
        GALLERYBOX_INFO_WIDTH = GALLERYBOX_INFO_WIDTH < 1 ? 1 : GALLERYBOX_INFO_WIDTH;
        return;
    }
    if (strcmp(name,"GALLERYBOX_INFO_HEIGHT") == 0)
    {
        GALLERYBOX_INFO_HEIGHT = atoi(value);
        GALLERYBOX_INFO_HEIGHT = GALLERYBOX_INFO_HEIGHT < 1 ? 1 : GALLERYBOX_INFO_HEIGHT;
        return;
    }

    if (strcmp(name,"BOX_ALPHA_INCREMENT") == 0)
    {
        BOX_ALPHA_INCREMENT = atoi(value);
        BOX_ALPHA_INCREMENT = BOX_ALPHA_INCREMENT < 1 ? 1 : BOX_ALPHA_INCREMENT;
        return;
    }
    if (strcmp(name,"BOX_ALPHA_INTERVAL") == 0)
    {
        BOX_ALPHA_INTERVAL = atoi(value);
        BOX_ALPHA_INTERVAL = BOX_ALPHA_INTERVAL < 1 ? 1 : BOX_ALPHA_INTERVAL;
        return;
    }

    if (strcmp(name,"IMAGELAYER_ALPHA_INCREMENT") == 0)
    {
        IMAGELAYER_ALPHA_INCREMENT = atoi(value);
        IMAGELAYER_ALPHA_INCREMENT = IMAGELAYER_ALPHA_INCREMENT < 1 ? 1 : IMAGELAYER_ALPHA_INCREMENT;
        return;
    }
    if (strcmp(name,"IMAGELAYER_ALPHA_INTERVAL") == 0)
    {
        IMAGELAYER_ALPHA_INTERVAL = atoi(value);
        IMAGELAYER_ALPHA_INTERVAL = IMAGELAYER_ALPHA_INTERVAL < 1 ? 1 : IMAGELAYER_ALPHA_INTERVAL;
        return;
    }
    if (strcmp(name,"IMAGELAYER_X") == 0)
    {
        IMAGELAYER_X = atof(value);
        return;
    }
    if (strcmp(name,"IMAGELAYER_Y") == 0)
    {
        IMAGELAYER_Y = atof(value);
        return;
    }

    if (strcmp(name,"BACKGROUNDLAYER_ALPHA_INCREMENT") == 0)
    {
        BACKGROUNDLAYER_ALPHA_INCREMENT = atoi(value);
        BACKGROUNDLAYER_ALPHA_INCREMENT = BACKGROUNDLAYER_ALPHA_INCREMENT < 1 ? 1 : BACKGROUNDLAYER_ALPHA_INCREMENT;
        return;
    }
    if (strcmp(name,"BACKGROUNDLAYER_ALPHA_INTERVAL") == 0)
    {
        BACKGROUNDLAYER_ALPHA_INTERVAL = atoi(value);
        BACKGROUNDLAYER_ALPHA_INTERVAL = BACKGROUNDLAYER_ALPHA_INTERVAL < 1 ? 1 : BACKGROUNDLAYER_ALPHA_INTERVAL;
        return;
    }
    if (strcmp(name,"BACKGROUNDLAYER_X") == 0)
    {
        BACKGROUNDLAYER_X = atof(value);
        return;
    }
    if (strcmp(name,"BACKGROUNDLAYER_Y") == 0)
    {
        BACKGROUNDLAYER_Y = atof(value);
        return;
    }

    if (strcmp(name,"CHARACTERLAYER_MOVE_BUFFER") == 0)
    {
        CHARACTERLAYER_MOVE_BUFFER = atof(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_MOVE_INCREMENT") == 0)
    {
        CHARACTERLAYER_MOVE_INCREMENT = atof(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_HEIGHT") == 0)
    {
        CHARACTERLAYER_HEIGHT = atoi(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_LEFT_L_X") == 0)
    {
        CHARACTERLAYER_LEFT_L_X = atoi(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_LEFT_L_Y") == 0)
    {
        CHARACTERLAYER_LEFT_L_Y = atoi(value);
        return;
    }

    if (strcmp(name,"CHARACTERLAYER_LEFT_M_X") == 0)
    {
        CHARACTERLAYER_LEFT_M_X = atoi(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_LEFT_M_Y") == 0)
    {
        CHARACTERLAYER_LEFT_M_Y = atoi(value);
        return;
    }
    
    if (strcmp(name,"CHARACTERLAYER_MIDDLE_X") == 0)
    {
        CHARACTERLAYER_MIDDLE_X = atoi(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_MIDDLE_Y") == 0)
    {
        CHARACTERLAYER_MIDDLE_Y = atoi(value);
        return;
    }

    if (strcmp(name,"CHARACTERLAYER_RIGHT_Q_X") == 0)
    {
        CHARACTERLAYER_RIGHT_Q_X = atoi(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_RIGHT_Q_Y") == 0)
    {
        CHARACTERLAYER_RIGHT_Q_Y = atoi(value);
        return;
    }

    if (strcmp(name,"CHARACTERLAYER_RIGHT_R_X") == 0)
    {
        CHARACTERLAYER_RIGHT_R_X = atoi(value);
        return;
    }
    if (strcmp(name,"CHARACTERLAYER_RIGHT_R_Y") == 0)
    {
        CHARACTERLAYER_RIGHT_R_Y = atoi(value);
        return;
    }
    if (strcmp(name,"MAX_PLAYER_NUM") == 0)
    {
        MAX_PLAYER_NUM = atoi(value);
        return;
    }
}

unsigned long CCommon::GetTicks(){
    return Clock.GetElapsedTime() * 1000;
}

unsigned int CCommon::SizeOfCharWithUTF8(char Char)
{
    if (Char < 0)
    {
        if((unsigned char)Char >= 0xE0)
        {
            return 3;
        }
        else if ((unsigned char)Char >= 0xC0 && (unsigned char)Char < 0xE0)
        {
            return 2;
        }
    }

    return 1;
}

void CCommon::SaveSysData()
{
    FILE* File = fopen(GAME_SYSDATA.c_str(), "w");
    map<string, string>::iterator it;
    for ( it=SystemVariableTable.begin(); it != SystemVariableTable.end(); it++ )
        fprintf (File, "%s = %s\n",(*it).first.c_str(),(*it).second.c_str());

    fclose (File);
}

void CCommon::OnCleanup()
{
    PlayerVariableTable.clear();
    SystemVariableTable.clear();

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
