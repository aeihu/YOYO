/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
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
#include "jsonxx.h"

using namespace std;
using namespace jsonxx;

class CCommon
{
    private:
        sf::Clock __clock;

        void SetValue(Object json);
    public:
        string CONFIG_PATH;
        string GAME_PATH;
        string GAME_NAME;
        string GAME_ICON;
        string GAME_SYSDATA;
        bool FULL_SCREEN;

        size_t MAX_FPS;

        size_t INTERVAL;//    25

        //<config>
        size_t  TILE_SIZE;//    32
        size_t  WWIDTH;//        800
        size_t  WHEIGHT;//        600
        
        unsigned char   SOUND_POOL_NUM ;//5
        unsigned char   VOICE_POOL_NUM ;//3

        size_t          SCREEN_PIECE_NUM;//   16
        //</config>

        //<option>
        size_t  TEXT_FRAMERATE ;//10
        size_t  AUTO_FRAMERATE ;//10
        float  BGM_VOLUME;// 10
        float  SE_VOLUME;// 10
        float  VOICE_VOLUME;// 10
        //</option>

        string MOUSEOVER_SE;// "MOUSEOVER"
        string MOUSEDOWN_SE;// "MOUSEDOWN"
        string BOXCLOSED_SE;// "BOXCLOSED"

        static CCommon _Common;

        CCommon();

        //void SaveSysData();
        unsigned long GetTicks();

        bool OnInit();
        bool IsFileExist(string filename);
        //void OnCleanup();
};

#endif
