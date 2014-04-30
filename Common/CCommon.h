/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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

        int MAX_FPS;
        int COLOR_KEY_RED;
        int COLOR_KEY_GREEN;
        int COLOR_KEY_BLUE;

        unsigned int INCREMENT;//    25
        unsigned int INTERVAL;//    25

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
        
        unsigned char   SOUND_POOL_NUM ;//5
        unsigned char   VOICE_POOL_NUM ;//3
        //</config>

        //<option>
        int  TEXT_FRAMERATE ;//10
        int  BGM_VOLUME;// 10
        int  SE_VOLUME;// 10
        //</option>

        string MOUSEOVER_SE;// "MOUSEOVER"
        string MOUSEDOWN_SE;// "MOUSEDOWN"
        string BOXCLOSED_SE;// "BOXCLOSED"

        float CHARACTER_LAYER_MOVE_BUFFER;// 30

        static CCommon _Common;

        CCommon();

        unsigned int SizeOfCharWithUTF8(char Char);
        void SaveSysData();
        unsigned long GetTicks();

        bool OnInit();
        void OnCleanup();
};

#endif
