/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCOMMON_H_
    #define _CCOMMON_H_

#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include "Cio.h"

using namespace std;

typedef enum {BUTTON_FOCUS, MAP_FOCUS, MESSAGEBOX_FOCUS, MENUBOX_FOCUS, LOGBOX_FOCUS, BUTTON_STATE} eEventFocus;

class CCommon
{
    private:
        sf::Clock Clock;

        void SetValue(const char* name, const char* value);
    public:
        map<string, string>        PlayerVariableTable;
        map<string, string>        SystemVariableTable;
        eEventFocus                EventFocus;

        string CONFIG_PATH;
        string GAME_PATH;
        string GAME_NAME;
        string GAME_ICON;
        string GAME_SYSDATA;

        bool APPLY_ALPHA;

        int MAX_FRAME;
        int COLOR_KEY_RED;
        int COLOR_KEY_GREEN;
        int COLOR_KEY_BLUE;

        string ITEM_DATA_PATH;
        string EQUIP_DATA_PATH;
        string MAGIC_DATA_PATH;
        string SKILL_DATA_PATH;
        string MONSTER_DATA_PATH;

        string ICON_PATH;
        int ICON_SIZE;
            
        int ANIMATION_EFFECTS_MOVE_RANGE;
        int ANIMATION_EFFECTS_MOVE_INCREMENT;
        int BOX_ANIMATION_INTERVAL;
        
        int BATTLE_PLAYER_POSTION1_X;
        int BATTLE_PLAYER_POSTION1_Y;
        int BATTLE_PLAYER_POSTION2_X;
        int BATTLE_PLAYER_POSTION2_Y;
        int BATTLE_PLAYER_POSTION3_X;
        int BATTLE_PLAYER_POSTION3_Y;
        int BATTLE_PLAYER_POSTION4_X;
        int BATTLE_PLAYER_POSTION4_Y;

        int BATTLE_ENEMY_POSTION1_X;
        int BATTLE_ENEMY_POSTION1_Y;
        int BATTLE_ENEMY_POSTION2_X;
        int BATTLE_ENEMY_POSTION2_Y;
        int BATTLE_ENEMY_POSTION3_X;
        int BATTLE_ENEMY_POSTION3_Y;
        int BATTLE_ENEMY_POSTION4_X;
        int BATTLE_ENEMY_POSTION4_Y;
        int BATTLE_ENEMY_POSTION5_X;
        int BATTLE_ENEMY_POSTION5_Y;
        int BATTLE_ENEMY_POSTION6_X;
        int BATTLE_ENEMY_POSTION6_Y;
        int BATTLE_ENEMY_POSTION7_X;
        int BATTLE_ENEMY_POSTION7_Y;
        int BATTLE_ENEMY_POSTION8_X;
        int BATTLE_ENEMY_POSTION8_Y;

        int MAP_WIDTH    ;//20
        int MAP_HEIGHT    ;//20
        int MAP_ANIMATIOM_MAXFRAMES    ;//4
        int MAP_ANIMATIOM_FRAMERATE    ;//500

        //<config>
        int  TILE_SIZE;//    32
        int  WWIDTH;//        800
        int  WHEIGHT;//        600
        int  FONT_SIZE;//   16
        string  FONT_PATH;//   "C://WINDOWS//Fonts//MSGOTHIC.TTC"
        char   CHAR_COLOR_RED;
        char   CHAR_COLOR_GREEN;
        char   CHAR_COLOR_BLUE;
        char   CHAR_COLOR_ALPHA;//10
        char   FONT_SHADOW;//10
        char   CHAR_SHADOW_COLOR_RED ;//10
        char   CHAR_SHADOW_COLOR_GREEN ;//10
        char   CHAR_SHADOW_COLOR_BLUE ;//10
        char   CHAR_SHADOW_COLOR_ALPHA ;//10
        //</config>

        //<option>
        int  TEXT_FRAMERATE ;//10
        int  BGM_VOLUME;// 10
        int  SE_VOLUME;// 10
        //</option>

        unsigned int  BOX_TILE_SIZE;// 16
        int  WALK_SPEED;// 5

        string MOUSEOVER_SE;// "MOUSEOVER"
        string MOUSEDOWN_SE;// "MOUSEDOWN"
        string BOXCLOSED_SE;// "BOXCLOSED"

        string MSGBOX_TILESETS_PATH;// "./tilesets/12indow.png"
        string MSGBOX_TABLE_PATH;
        int  MSGBOX_LOCATION_X;// 10
        int  MSGBOX_LOCATION_Y;// 300
        int  MSGBOX_MSG_OFFSET_X;// 10
        int  MSGBOX_MSG_OFFSET_Y;// 10
        unsigned int  MSGBOX_MSG_WIDTH;// 10
        unsigned int  MSGBOX_MSG_HEIGHT;// 10
        //int  MSGBOX_ANIMATION_INTERVAL;
        int  MSGBOX_SPEAKER_OFFSET_X;// 10
        int  MSGBOX_SPEAKER_OFFSET_Y;// 10
        int  MSGBOX_CURSOR_OFFSET_X;// 10
        int  MSGBOX_CURSOR_OFFSET_Y;// 10
        int  MSGBOX_CURSOR_SIZE;
        int  MSGBOX_CURSOR_TILE;
        int  MSGBOX_CURSOR_FRAMERATE;
        int  MSGBOX_CURSOR_MAX_FRAMES;
        int  MSGBOX_WIDTH;// 38
        int  MSGBOX_HEIGHT;// 8
        int  MSGBOX_TILE_TOP;// 9
        int  MSGBOX_TILE_BOTTOM;// 45
        int  MSGBOX_TILE_LEFT;// 20
        int  MSGBOX_TILE_RIGHT;// 23
        int  MSGBOX_TILE_TOPLEFT;// 8
        int  MSGBOX_TILE_TOPRIGHT;// 11
        int  MSGBOX_TILE_BOTTOMLEFT;// 44
        int  MSGBOX_TILE_BOTTOMRIGHT;// 47
        int  MSGBOX_TILE_FILLER;// 3
        int  MSGBOX_TILE_FILLER_SIZE;// 32
        int  MSGBOX_ANIMATION_TYPE;//0

        string  INFOBOX_TILESETS_PATH;// "./tilesets/12indow.png"
        int  INFOBOX_LOCATION_X;// 10
        int  INFOBOX_LOCATION_Y;// 300
        int  INFOBOX_INFO_OFFSET_X;// 10
        int  INFOBOX_INFO_OFFSET_Y;// 10
        int  INFOBOX_WIDTH;// 10
        int  INFOBOX_HEIGHT;// 8
        //int  INFOBOX_ANIMATION_INTERVAL;
        int  INFOBOX_TILE_TOP;// 9
        int  INFOBOX_TILE_BOTTOM;// 45
        int  INFOBOX_TILE_LEFT;// 20
        int  INFOBOX_TILE_RIGHT;// 23
        int  INFOBOX_TILE_TOPLEFT;// 8
        int  INFOBOX_TILE_TOPRIGHT;// 11
        int  INFOBOX_TILE_BOTTOMLEFT;// 44
        int  INFOBOX_TILE_BOTTOMRIGHT;// 47
        int  INFOBOX_TILE_FILLER;// 32
        int  INFOBOX_TILE_FILLER_SIZE;// 32
        int  INFOBOX_ANIMATION_TYPE;//0

        string  LISTBOX_TILESETS_PATH;// "./tilesets/12indow.png"
        int  LISTBOX_LOCATION_X;// 10
        int  LISTBOX_LOCATION_Y;// 300
        int  LISTBOX_INFO_OFFSET_X;// 10
        int  LISTBOX_INFO_OFFSET_Y;// 10
        int  LISTBOX_WIDTH;// 38
        int  LISTBOX_HEIGHT;// 8
        //int  LISTBOX_ANIMATION_INTERVAL;
        int  LISTBOX_TILE_TOP;// 9
        int  LISTBOX_TILE_BOTTOM;// 45
        int  LISTBOX_TILE_LEFT;// 20
        int  LISTBOX_TILE_RIGHT ;//23
        int  LISTBOX_TILE_TOPLEFT;// 8
        int  LISTBOX_TILE_TOPRIGHT;// 11
        int  LISTBOX_TILE_BOTTOMLEFT;// 44
        int  LISTBOX_TILE_BOTTOMRIGHT;// 47
        int  LISTBOX_TILE_FILLER;// 32
        int  LISTBOX_TILE_FILLER_SIZE;// 32
        int  LISTBOX_ANIMATION_TYPE;//0

        string  MENUBOX_TILESETS_PATH;// "./tilesets/12indow.png"
        int  MENUBOX_LOCATION_X;// 10
        int  MENUBOX_LOCATION_Y;// 10
        int  MENUBOX_INFO_OFFSET_X;// 10
        int  MENUBOX_INFO_OFFSET_Y;// 10
        int  MENUBOX_WIDTH;// 15
        int  MENUBOX_HEIGHT;// 8
        //int  MENUBOX_ANIMATION_INTERVAL;
        int  MENUBOX_TILE_TOP;// 9
        int  MENUBOX_TILE_BOTTOM;// 45
        int  MENUBOX_TILE_LEFT;// 20
        int  MENUBOX_TILE_RIGHT;// 23
        int  MENUBOX_TILE_TOPLEFT;// 8
        int  MENUBOX_TILE_TOPRIGHT;// 11
        int  MENUBOX_TILE_BOTTOMLEFT;// 44
        int  MENUBOX_TILE_BOTTOMRIGHT;// 47
        int  MENUBOX_TILE_FILLER;// 32
        int  MENUBOX_TILE_FILLER_SIZE;// 32
        int  MENUBOX_TILE_SELECTEDITEM;
        int  MENUBOX_TILE_UPARROW;
        int  MENUBOX_TILE_DOWNARROW;
        int  MENUBOX_TILE_BAR;
        int  MENUBOX_ANIMATION_TYPE;//0
        
        string  LOGBOX_TILESETS_PATH;// "./tilesets/12indow.png"
        int  LOGBOX_LOCATION_X;// 10
        int  LOGBOX_LOCATION_Y;// 10
        int  LOGBOX_INFO_OFFSET_X;// 10
        int  LOGBOX_INFO_OFFSET_Y;// 10
        int  LOGBOX_WIDTH;// 15
        int  LOGBOX_HEIGHT;// 8
        //int  LOGBOX_ANIMATION_INTERVAL;
        int  LOGBOX_TILE_TOP;// 9
        int  LOGBOX_TILE_BOTTOM;// 45
        int  LOGBOX_TILE_LEFT;// 20
        int  LOGBOX_TILE_RIGHT;// 23
        int  LOGBOX_TILE_TOPLEFT;// 8
        int  LOGBOX_TILE_TOPRIGHT;// 11
        int  LOGBOX_TILE_BOTTOMLEFT;// 44
        int  LOGBOX_TILE_BOTTOMRIGHT;// 47
        int  LOGBOX_TILE_FILLER;// 32
        int  LOGBOX_TILE_FILLER_SIZE;// 32
        int  LOGBOX_TILE_UPARROW;
        int  LOGBOX_TILE_DOWNARROW;
        int  LOGBOX_TILE_BAR;
        int  LOGBOX_ANIMATION_TYPE;//0
        
        string  GALLERYBOX_TILESETS_PATH;// "./tilesets/12indow.png"
        int  GALLERYBOX_LOCATION_X;// 10
        int  GALLERYBOX_LOCATION_Y;// 10
        int  GALLERYBOX_INFO_OFFSET_X;// 10
        int  GALLERYBOX_INFO_OFFSET_Y;// 10
        int  GALLERYBOX_WIDTH;// 15
        int  GALLERYBOX_HEIGHT;// 8
        int  GALLERYBOX_IMAGE_WIDTH;// 15
        int  GALLERYBOX_IMAGE_HEIGHT;// 8
        int  GALLERYBOX_INFO_WIDTH;// 15
        int  GALLERYBOX_INFO_HEIGHT;// 8

        int  BOX_ALPHA_INCREMENT;//    25
        int  BOX_ALPHA_INTERVAL;//    25

        int  IMAGELAYER_ALPHA_INCREMENT;//    25
        int  IMAGELAYER_ALPHA_INTERVAL;//    25
        float  IMAGELAYER_X;
        float  IMAGELAYER_Y;

        int  BACKGROUNDLAYER_ALPHA_INCREMENT;//    25
        int  BACKGROUNDLAYER_ALPHA_INTERVAL;//    25
        float  BACKGROUNDLAYER_X;//    0
        float  BACKGROUNDLAYER_Y;//    0

        float  CHARACTERLAYER_MOVE_BUFFER;// 4
        float  CHARACTERLAYER_MOVE_INCREMENT;//    10

        int  CHARACTERLAYER_HEIGHT;//    10

        int  CHARACTERLAYER_LEFT_L_X;//    10
        int  CHARACTERLAYER_LEFT_L_Y;//    240
        int  CHARACTERLAYER_LEFT_M_X;//    100
        int  CHARACTERLAYER_LEFT_M_Y;//    240
        int  CHARACTERLAYER_MIDDLE_X;//    400
        int  CHARACTERLAYER_MIDDLE_Y;//    240
        int  CHARACTERLAYER_RIGHT_Q_X;//    500
        int  CHARACTERLAYER_RIGHT_Q_Y;//    240
        int  CHARACTERLAYER_RIGHT_R_X;  //    600
        int  CHARACTERLAYER_RIGHT_R_Y;  //    240

        int  MAX_PLAYER_NUM;//    1

        static CCommon common;

        CCommon();

        unsigned int SizeOfCharWithUTF8(char Char);
        void SaveSysData();
        unsigned long GetTicks();

        bool OnInit();
        void OnCleanup();
};

#endif
