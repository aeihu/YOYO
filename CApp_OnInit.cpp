/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() 
{
    sf_Display = new sf::RenderWindow();

    if (!CCommon::common.OnInit()){
        return false;
    }

    CParser::parser.SetRunning(&Running);

    sf_Display->Create(
        sf::VideoMode(
        CCommon::common.WWIDTH, 
        CCommon::common.WHEIGHT, 32), CCommon::common.GAME_NAME);

    sf_Display->SetFramerateLimit(CCommon::common.MAX_FRAME);
 //   if((sf_Display = SDL_SetVideoMode(
    //    CCommon::common.WWIDTH, 
    //    CCommon::common.WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) 
    //{
    //    cout << "Unable to set "<< CCommon::common.WWIDTH << "x" << CCommon::common.WHEIGHT 
    //        <<" video: " << SDL_GetError() << endl;
 //       return false;
 //   }



    //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if (!CParser::parser.LoadScript(CCommon::common.GAME_PATH.c_str(), "init"))
    {
        cout << "CApp::OnInit(): can't find script file \"" << CCommon::common.GAME_PATH.c_str()
            << "\" or section [init]." << endl;
        return false;
    }


//    if (!CMessageBox::messagebox.CBox::OnInit(
//        CCommon::common.MSGBOX_TILESETS_PATH.c_str(),
//        CCommon::common.MSGBOX_TABLE_PATH.c_str(),
//        CCommon::common.BOX_TILE_SIZE))
//    {
//        cout << "CMessageBox: initialization failed." << endl;
//        return false;
//    }

    //if(!CObjectInfoBox::objectinfobox.OnInit(
    //    CCommon::common.INFOBOX_TILESETS_PATH.c_str() ,
    //    CCommon::common.INFOBOX_WIDTH ,
    //    CCommon::common.INFOBOX_HEIGHT ,
    //    CCommon::common.INFOBOX_TILE_TOP, 
    //    CCommon::common.INFOBOX_TILE_BOTTOM, 
    //    CCommon::common.INFOBOX_TILE_LEFT ,
    //    CCommon::common.INFOBOX_TILE_RIGHT ,
    //    CCommon::common.INFOBOX_TILE_TOPLEFT, 
    //    CCommon::common.INFOBOX_TILE_TOPRIGHT, 
    //    CCommon::common.INFOBOX_TILE_BOTTOMLEFT, 
    //    CCommon::common.INFOBOX_TILE_BOTTOMRIGHT,
    //    CCommon::common.INFOBOX_TILE_FILLER,
    //    CCommon::common.INFOBOX_TILE_FILLER_SIZE ,
    //    CCommon::common.INFOBOX_ANIMATION_TYPE ))
    //{
    //    cout << "CObjectInfoBox: initialization failed." << endl;
    //    return false;
    //}
    //if(!CObjectListBox::objectlistbox.OnInit(
    //    CCommon::common.LISTBOX_TILESETS_PATH.c_str() ,
    //    CCommon::common.LISTBOX_WIDTH ,
    //    CCommon::common.LISTBOX_HEIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOP, 
    //    CCommon::common.LISTBOX_TILE_BOTTOM, 
    //    CCommon::common.LISTBOX_TILE_LEFT ,
    //    CCommon::common.LISTBOX_TILE_RIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOPLEFT, 
    //    CCommon::common.LISTBOX_TILE_TOPRIGHT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMLEFT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMRIGHT,
    //    CCommon::common.LISTBOX_TILE_FILLER,
    //    CCommon::common.LISTBOX_TILE_FILLER_SIZE,
    //    CCommon::common.LISTBOX_ANIMATION_TYPE ))
    //{
    //    cout << "CObjectListBox: initialization failed." << endl;
    //    return false;
    //}

    //if(!CEquipListBox::equiplistbox.OnInit(
    //    CCommon::common.LISTBOX_TILESETS_PATH.c_str() ,
    //    CCommon::common.LISTBOX_WIDTH ,
    //    CCommon::common.LISTBOX_HEIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOP, 
    //    CCommon::common.LISTBOX_TILE_BOTTOM, 
    //    CCommon::common.LISTBOX_TILE_LEFT ,
    //    CCommon::common.LISTBOX_TILE_RIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOPLEFT, 
    //    CCommon::common.LISTBOX_TILE_TOPRIGHT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMLEFT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMRIGHT,
    //    CCommon::common.LISTBOX_TILE_FILLER,
    //    CCommon::common.LISTBOX_TILE_FILLER_SIZE,
    //    CCommon::common.LISTBOX_ANIMATION_TYPE ))
    //{
    //    cout << "CEquipListBox: initialization failed." << endl;
    //    return false;
    //}
    //
    //if(!CSkillListBox::skilllistbox.OnInit(
    //    CCommon::common.LISTBOX_TILESETS_PATH.c_str() ,
    //    CCommon::common.LISTBOX_WIDTH ,
    //    CCommon::common.LISTBOX_HEIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOP, 
    //    CCommon::common.LISTBOX_TILE_BOTTOM, 
    //    CCommon::common.LISTBOX_TILE_LEFT ,
    //    CCommon::common.LISTBOX_TILE_RIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOPLEFT, 
    //    CCommon::common.LISTBOX_TILE_TOPRIGHT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMLEFT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMRIGHT,
    //    CCommon::common.LISTBOX_TILE_FILLER,
    //    CCommon::common.LISTBOX_TILE_FILLER_SIZE,
    //    CCommon::common.LISTBOX_ANIMATION_TYPE ))
    //{
    //    cout << "CSkillListBox: initialization failed." << endl;
    //    return false;
    //}
    
    //if(!CItemListBox::itemlistbox.OnInit(
    //    CCommon::common.LISTBOX_TILESETS_PATH.c_str() ,
    //    CCommon::common.LISTBOX_WIDTH ,
    //    CCommon::common.LISTBOX_HEIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOP, 
    //    CCommon::common.LISTBOX_TILE_BOTTOM, 
    //    CCommon::common.LISTBOX_TILE_LEFT ,
    //    CCommon::common.LISTBOX_TILE_RIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOPLEFT, 
    //    CCommon::common.LISTBOX_TILE_TOPRIGHT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMLEFT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMRIGHT,
    //    CCommon::common.LISTBOX_TILE_FILLER,
    //    CCommon::common.LISTBOX_TILE_FILLER_SIZE,
    //    CCommon::common.LISTBOX_ANIMATION_TYPE ))
    //{
    //    cout << "CItemListBox: initialization failed." << endl;
    //    return false;
    //}
    //
    //if(!CMagicListBox::magiclistbox.OnInit(
    //    CCommon::common.LISTBOX_TILESETS_PATH.c_str() ,
    //    CCommon::common.LISTBOX_WIDTH ,
    //    CCommon::common.LISTBOX_HEIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOP, 
    //    CCommon::common.LISTBOX_TILE_BOTTOM, 
    //    CCommon::common.LISTBOX_TILE_LEFT ,
    //    CCommon::common.LISTBOX_TILE_RIGHT ,
    //    CCommon::common.LISTBOX_TILE_TOPLEFT, 
    //    CCommon::common.LISTBOX_TILE_TOPRIGHT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMLEFT, 
    //    CCommon::common.LISTBOX_TILE_BOTTOMRIGHT,
    //    CCommon::common.LISTBOX_TILE_FILLER,
    //    CCommon::common.LISTBOX_TILE_FILLER_SIZE,
    //    CCommon::common.LISTBOX_ANIMATION_TYPE ))
    //{
    //    cout << "CMagicListBox: initialization failed." << endl;
    //    return false;
    //}

    //if (!CMenuBox::menubox.OnInit(
    //    CCommon::common.MENUBOX_TILESETS_PATH.c_str() ,
    //    CCommon::common.MENUBOX_WIDTH ,
    //    CCommon::common.MENUBOX_HEIGHT ,
    //    CCommon::common.MENUBOX_TILE_TOP, 
    //    CCommon::common.MENUBOX_TILE_BOTTOM, 
    //    CCommon::common.MENUBOX_TILE_LEFT ,
    //    CCommon::common.MENUBOX_TILE_RIGHT ,
    //    CCommon::common.MENUBOX_TILE_TOPLEFT, 
    //    CCommon::common.MENUBOX_TILE_TOPRIGHT, 
    //    CCommon::common.MENUBOX_TILE_BOTTOMLEFT, 
    //    CCommon::common.MENUBOX_TILE_BOTTOMRIGHT,
    //    CCommon::common.MENUBOX_TILE_FILLER,
    //    CCommon::common.MENUBOX_TILE_FILLER_SIZE,
    //    CCommon::common.MENUBOX_ANIMATION_TYPE,
    //    CCommon::common.MENUBOX_TILE_SELECTEDITEM,
    //    CCommon::common.MENUBOX_TILE_UPARROW,
    //    CCommon::common.MENUBOX_TILE_DOWNARROW,
    //    CCommon::common.MENUBOX_TILE_BAR))
    //{
    //    cout << "CMenuBox: initialization failed." << endl;
    //    return false;
    //}
    /*
    if (!CLogBox::logbox.OnInit(
        CCommon::common.LOGBOX_TILESETS_PATH.c_str() ,
        CCommon::common.LOGBOX_WIDTH ,
        CCommon::common.LOGBOX_HEIGHT ,
        CCommon::common.LOGBOX_TILE_TOP, 
        CCommon::common.LOGBOX_TILE_BOTTOM, 
        CCommon::common.LOGBOX_TILE_LEFT ,
        CCommon::common.LOGBOX_TILE_RIGHT ,
        CCommon::common.LOGBOX_TILE_TOPLEFT, 
        CCommon::common.LOGBOX_TILE_TOPRIGHT, 
        CCommon::common.LOGBOX_TILE_BOTTOMLEFT, 
        CCommon::common.LOGBOX_TILE_BOTTOMRIGHT,
        CCommon::common.LOGBOX_TILE_FILLER,
        CCommon::common.LOGBOX_TILE_FILLER_SIZE,
        CCommon::common.LOGBOX_ANIMATION_TYPE,
        CCommon::common.LOGBOX_TILE_UPARROW,
        CCommon::common.LOGBOX_TILE_DOWNARROW,
        CCommon::common.LOGBOX_TILE_BAR,
        CCommon::common.MSGBOX_MSG_HEIGHT))
    {
        cout << "CLogBox: initialization failed." << endl;
        return false;
    }*/

    //CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
 //   CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
    
    //CObjectInfoBox::objectinfobox.LoadFont(CCommon::common.FONT_PATH.c_str() , CCommon::common.FONT_SIZE);
    //CObjectInfoBox::objectinfobox.SetColor(100,100,200);
    //Item itm;
    //itm.HP = 1;
    //itm.INFO = "It's test items";
    //itm.MAX_HP = 1;
    //itm.MAX_MP = 1;
    //itm.MP = 1;
    //itm.Name = "Hello World";
    //CObjectInfoBox::objectinfobox.LoadObject(itm);

  return true;
}

//==============================================================================
