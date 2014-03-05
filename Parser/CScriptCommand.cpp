/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CScriptCommand.h"
#include "../Stage_Action/CEntity.h"
#include "../Stage_Talk/CCharacterLayer.h"
#include "../Stage_Action/CPlayer.h"
#include "../Parser/CParser.h"
#include "../Sound/CSoundBank.h"
#include "../Gui/CButton.h"
#include "../GSM_Window/CMenuBox.h"
#include "../GSM_Window/CObjectInfoBox.h"
#include "../GSM_Window/CObjectListBox.h"
#include "../Battlefield/CCharacterData.h"
#include "../GSM_Window/CLoadObject.h"
#include "../Stage_Action/CMapEventControl.h"
#include "../Animation/CAnimationBank.h"
#include "../Common/CResourceManager.h"
#include "../GSM_Window/CLogBox.h"
#include <iostream>

//
//int Cmd_Move(const char* name, int x, int y, bool pause)
//{
//    int counter = 0;
//    int v = CEntity::EntityList.size();
//    for(int i = 0;i < v;i++) {
//        if(strcmp(CEntity::EntityList[i]->Name.c_str(), name) == 0) 
//        {
//            if (pause)
//                CEntity::EntityList[i]->SetDestination(x, y, &CParser::parser.Pause);
//            else
//                CEntity::EntityList[i]->SetDestination(x, y, NULL);
//
//            counter++;
//        }
//    }
//
//    return counter;
//}
//
//bool Cmd_ViewPoint(const char* name)
//{
//    int v = CEntity::EntityList.size();
//    for(int i = 0;i < v;i++) {
//        if(strcmp(CEntity::EntityList[i]->Name.c_str(), name) == 0) 
//        {
//            CCamera::CameraControl.SetTarget(&CEntity::EntityList[i]->X, &CEntity::EntityList[i]->Y);
//            CMapEventControl::MapEventControl.SetTarget(&CEntity::EntityList[i]->X, &CEntity::EntityList[i]->Y);
//            return true;
//        }
//    }
//
//    return false;
//}
//
//bool Cmd_ViewPointMove(int x, int y)
//{
//    //int v = CEntity::EntityList.size();
// //   for(int i = 0;i < v;i++) {
//    //    if(strcmp(CEntity::EntityList[i]->Name.c_str(), name) == 0) 
//    //    {
//    //        CCamera::CameraControl.SetTarget(&CEntity::EntityList[i]->X, &CEntity::EntityList[i]->Y);
//    //        return true;
//    //    }
// //   }
//    return true;
//}
//
//int Cmd_DeleteCharacter(const char* name)
//{
//    int counter = 0;
//    
//    for(int i = CEntity::EntityList.size() - 1;i >= 0; i--) 
//    {
//        if(strcmp(CEntity::EntityList[i]->Name.c_str(), name) == 0) 
//        {
//            CEntity::EntityList[i]->OnCleanup();
//            delete CEntity::EntityList[i];
//            CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
//            counter++;
//        }
//    }
//
//    for(int i = CPlayerControl::PlayerList.size() - 1;i >= 0; i--) 
//    {
//        if(strcmp(CPlayerControl::PlayerList[i]->Name.c_str(), name) == 0) 
//        {
//            CPlayerControl::PlayerList.erase(CPlayerControl::PlayerList.begin() +i);
//        }
//    }
//
//    return counter;
//}
//
//bool Cmd_CreateCharacter(const char* name, int x, int y, const char* filename, int width, int height, int maxframes, bool isNPC)
//{
//    CPlayer* temp = new CPlayer(name, x * CCommon::common.TILE_SIZE, y * CCommon::common.TILE_SIZE);
//    if (!temp->OnLoad(filename, width, height ,maxframes))
//    {
//        delete temp;
//        return false;
//    }
//
//    CEntity::EntityList.push_back(temp);
//    if (!isNPC && (CPlayerControl::PlayerList.size() < CCommon::common.MAX_PLAYER_NUM))
//        CPlayerControl::PlayerList.push_back(temp);
//
//    return true;
//}
//
bool Cmd_ShowInfo(vector<string> args)
{
    CResourceManager::GetInfo();
    //CResourceManager::GetInfo("ImageList", CResourceManager::_ImgLayerControl._ImgLayerList);
    //CResourceManager::GetInfo("BackgroundList", CResourceManager::_BackgroundLayerControl._ImgLayerList);
    //CResourceManager::GetInfo("CharacterList", CResourceManager::_CharacterLayerControl._CharacterList);
    //CResourceManager::GetInfo("MessageBoxList", CResourceManager::_MessageBoxControl._MessageBoxList);
    return true;
}

//void Cmd_AddPosition(string name, float x, float y)
bool Cmd_AddPosition(vector<string> args)
{
    if (args.size() != 3)
        return false;

    string name = args[0];
    float x = atof(args[1].c_str());
    float y = atof(args[2].c_str());
    CResourceManager::_CharacterLayerControl.AddPosition(name, x, y);
    return true;
}

//void Cmd_DelPosition(string name)
bool Cmd_DelPosition(vector<string> args)
{
    if (args.size() != 1)
        return false;

    string name = args[0];
    CResourceManager::_CharacterLayerControl.DelPosition(name);
    return true;
}

//bool Cmd_ShowCharacterLayer(string name, const char* filename, float x, float y, char type, float buf, float incr, bool pause)
bool Cmd_ShowCharacterLayer(vector<string> args)
{    
    if (args.size() != 1)
        return false;

    string name = args[0];
    const char* filename = args[1].c_str();
    float x = atof(args[2].c_str());
    float y = atof(args[3].c_str());

    switch (CResourceManager::_CharacterLayerControl.AddCharacter(name, filename, x, y)){
        case 0:
       ///     CResourceManager::_CharacterLayerControl.Show(name, x, y, type, incr, pause);
            return true;
        break;
        case 1:
            cout << "Cmd_ShowCharacterLayer(): character layer \""<< name << "\" has existed." <<endl;
        break;
        case 2:
            cout << "Cmd_ShowCharacterLayer(): failed to create character layer." <<endl;
        break;
    }

    return false;
}

bool Cmd_ShowCharacterLayer(string name, const char* filename, string position, char type, float buf, float incr, bool pause)
{    
    //float x=0,y=0;
    //if (CResourceManager::_CharacterLayerControl.GetPosition(position,&x,&y)){
    //    Cmd_ShowCharacterLayer(name, filename, x, y, type, incr, pause);
    //    return true;
    //}
    //cout << "Cmd_ShowCharacterLayer(): can't find position \""<< position << "\"." <<endl;
    return false;
}

bool Cmd_MoveCharacterLayer(string name, float x, float y, float incr, bool pause)
{
    if(!CResourceManager::_CharacterLayerControl.Move(name, x, y, incr, pause)){
        cout << "Cmd_MoveCharacterLayer(): can't find character layer \""<< name << "\"." <<endl;
        return false;
    }
    return true;
}

bool Cmd_MoveCharacterLayer(string name, string position, float incr, bool pause)
{
    float x=0,y=0;
    if (CResourceManager::_CharacterLayerControl.GetPosition(position,&x,&y)){
        Cmd_MoveCharacterLayer(name, x, y, incr, pause);
        return true;
    }
    cout << "Cmd_ShowCharacterLayer(): can't find position \""<< position << "\"." <<endl;
    return false;
}

bool Cmd_HideCharacterLayer(string name, char type, float buf, float incr, bool pause)
{
    if (!CResourceManager::_CharacterLayerControl.IsAlreadyExists(name)){
        cout << "Cmd_HideCharacterLayer(): can't find character layer \""<< name << "\"." <<endl;
        return false;
    }

    CResourceManager::_CharacterLayerControl.Hide(name, type, incr, pause);
    return true;
}

void Cmd_SetFaceCharacterLayer(string name, string face)
{
    CResourceManager::_CharacterLayerControl._CharacterList[name].SetFace(face);
}
//
//bool Cmd_AlphaCharacterLayer(char postion, int alpha)
//{
//    //for (int i = 0; i < CResourceManager::_CharacterLayerControl._CharacterList.size(); i++)
//    //{
//    //    if(CResourceManager::_CharacterLayerControl._CharacterList[i]->Postion == postion)
//    //    {
//    //        CResourceManager::_CharacterLayerControl._CharacterList[i]->Alpha = alpha;
//    //        return true;
//    //    }
//    //}
//    return false;
//}
//
//bool Cmd_LoadMap(const char* filename)
//{
//    return CArea::AreaControl.OnLoad(filename);
//}
//
//bool Cmd_LoadScript(const char* filename, const char* Section)
//{
//    return CParser::parser.LoadScript(filename, Section);
//}
//
//bool Cmd_AddBackground(string name, const char* filename, float x, float y)
bool Cmd_AddBackground(vector<string> args)
{
    float x = 0.0f;
    float y = 0.0f;

    if (args.size() == 4){
        x = atof(args[2].c_str());
        y = atof(args[3].c_str());
    }
    else if (args.size() == 2){
    
    }
    else{
        cout << "Cmd_AddBackground(): command invaild." << args.size()
            << " can't set  argument(s) in the command.." <<endl;
        return false;
    }

    string name = args[0];
    const char* filename = args[1].c_str();

    if (CResourceManager::_BackgroundLayerControl.AddImage(name, filename)){
        return true;
    }
    else{
        cout << "Cmd_AddBackground(): failed to load image." <<endl;
        return false;
    }
}

//bool Cmd_ShowBackground(string name, int inrc, bool pause)
bool Cmd_ShowBackground(vector<string> args)
{
    int inrc = 10;
    if (args.size() == 2){
        inrc = atoi(args[1].c_str());
    }
    else if (args.size() == 1){
    }
    else{
        cout << "Cmd_ShowBackground(): command invaild." << args.size()
            << " can't set  argument(s) in the command.." <<endl;
        return false;
    }

    string name = args[0];
    bool pause = false;

    if (CResourceManager::_BackgroundLayerControl.SetImageVisibility(name, 255, inrc, pause))
        return true;

    cout << "Cmd_ShowBackground(): can't find image \""<< name << "\"." << endl;
    return false;
}

//bool Cmd_DelBackground(string name)
bool Cmd_DelBackground(vector<string> args)
{
    if (args.size() != 1){
        cout << "Cmd_DelBackground(): command invaild." << args.size()
            << " can't set  argument(s) in the command.." <<endl;
        return false;
    }

    string name = args[0];

    if (CResourceManager::_BackgroundLayerControl.DelImage(name)){
        return true;
    }
    else{
        cout << "Cmd_DelBackground(): Image \"" << name << "\" has no existed." <<endl;
        return false;
    }
}

//bool Cmd_HideBackground(string name, int inrc, bool pause)
bool Cmd_HideBackground(vector<string> args)
{
    int inrc = 10;
    if (args.size() == 2){
        inrc = atoi(args[1].c_str());
    }
    else if (args.size() == 1){
    }
    else{
        cout << "Cmd_HideBackground(): command invaild." << args.size()
            << " can't set  argument(s) in the command.." <<endl;
        return false;
    }

    string name = args[0];
    bool pause = false;

    if (CResourceManager::_BackgroundLayerControl.SetImageVisibility(name, 0, inrc, pause))
        return true;

    cout << "Cmd_HideBackground(): can't find image \""<< name << "\"." << endl;
    return false;
}

/*
    Cmd_AddImg: comand of add image.
    args[0]: set image name.
    args[1]: set image path.
    args[2]: set image postion of x.
    args[3]: set image postion of y.
*/
bool Cmd_AddImg(vector<string> args)
{
    if (args.size() != 4)
        return false;

    string name = args[0];
    const char* filename = args[1].c_str();
    float x = atof(args[2].c_str());
    float y = atof(args[3].c_str());

    if (CResourceManager::_ImgLayerControl.AddImage(name, filename, x, y)){
        return true;
    }
    else{
        cout << "Cmd_AddImg(): failed to load image." <<endl;
        return false;
    }
}

//bool Cmd_ShowImg(string name, int inrc, bool pause)
bool Cmd_ShowImg(vector<string> args)
{
    if (args.size() != 3)
        return false;

    string name = args[0];
    int inrc = atof(args[1].c_str());
    bool pause =true;

    if (CResourceManager::_ImgLayerControl.SetImageVisibility(name, 255, inrc, pause))
        return true;

    cout << "Cmd_ShowImg(): can't find image \""<< name << "\"." << endl;
    return false;
}

bool Cmd_HideImg(string name, int inrc, bool pause)
{
    if (CResourceManager::_ImgLayerControl.SetImageVisibility(name, 0, inrc, pause))
        return true;

    cout << "Cmd_HideImg(): can't find image \""<< name << "\"." << endl;
    return false;
}

bool Cmd_DelImg(string name)
{
    if (CResourceManager::_ImgLayerControl.DelImage(name)){
        return true;
    }
    else{
        cout << "Cmd_DelImg(): Image \"" << name << "\" has no existed." <<endl;
        return false;
    }
}

//
//void Cmd_WhiteScreen(int msec)
//{
//    if (CImgLayer::ImgLayerList.count("WHITESCREEN") < 1)
//    {
//        CImgLayer::ImgLayerList["WHITESCREEN"] = new CImgLayer(0,0);
//    }
//    
//    CImgLayer::ImgLayerList["WHITESCREEN"]->SetColor(255,255,255,0);
//    CImgLayer::ImgLayerList["WHITESCREEN"]->SetAlpha(255, &CParser::parser.Pause);
//    CImgLayer::ImgLayerList["WHITESCREEN"]->SetInterval(msec);
//}
//
//void Cmd_BlackScreen(int msec)
//{
//    if (CImgLayer::ImgLayerList.count("BLACKSCREEN") < 1)
//    {
//        CImgLayer::ImgLayerList["BLACKSCREEN"] = new CImgLayer(0,0);
//    }
//    
//    CImgLayer::ImgLayerList["BLACKSCREEN"]->SetColor(0,0,0,0);
//    CImgLayer::ImgLayerList["BLACKSCREEN"]->SetAlpha(255, &CParser::parser.Pause);
//    CImgLayer::ImgLayerList["BLACKSCREEN"]->SetInterval(msec);
//}
//
bool Cmd_Say(const char* filename)
{
    return CSoundBank::SoundControl.Say(filename);
}

bool Cmd_PlayBGM(const char* filename)
{
    if(!CSoundBank::SoundControl.OnLoadBGM(filename))
        return false;

    CSoundBank::SoundControl.PlayBgm();
    return true;
}

void Cmd_PauseBGM()
{
    if (CSoundBank::SoundControl.GetBgmStatus() == sf::Music::Playing)
        CSoundBank::SoundControl.PauseBgm();
}

void Cmd_ResumeBGM()
{
    if (CSoundBank::SoundControl.GetBgmStatus() == sf::Music::Paused)
        CSoundBank::SoundControl.PlayBgm();
}

int Cmd_AddSE(const char* name, const char* filename)
{
    return CSoundBank::SoundControl.AddSE(name, filename);
}

bool Cmd_DelSE(string name)
{
    return CSoundBank::SoundControl.DeleteSE(name);
}

bool Cmd_PlaySE(const char* name)
{
    if(CSoundBank::SoundControl.PlaySE(name))
        return true;

    return false;
}

bool Cmd_AddButton(string name, const char* filename)
{
    switch (CResourceManager::_ButtonControl.AddButton(name, filename))
    {
        case 0:
            return true;
        break;
        case -1:
            cout << "Cmd_AddButton(): Button \"" << name << "\" has existed." <<endl;
        break;
        case -2:
            cout << "Cmd_AddButton(): failed to add Button." << endl;
        break;
    }

    return false;
}
//
bool Cmd_DelButton(string name)
{
    if (CResourceManager::_ButtonControl.DelButton(name))
        return true;

    cout << "Cmd_DelButton(): can't find Button \""<< name << "\"." <<endl;
    return false;
}

bool Cmd_ShowButton(string name, int incr, bool pause)
{
    if (!CResourceManager::_ButtonControl.SetImageVisibility(name, 255, incr, pause)){
        cout << "Cmd_ShowButton(): can't find Button \""<< name << "\"." <<endl;
        return false;
    }

    return true;
}

bool Cmd_HideButton(string name, int incr, bool pause)
{
    if (!CResourceManager::_ButtonControl.SetImageVisibility(name, 0, incr, pause)){
        cout << "Cmd_HideButton(): can't find Button \""<< name << "\"." <<endl;
        return false;
    }

    return true;
}
//
//
//void  Cmd_FullScreen()
//{
//    SDL_Event e;
//    e.key.type = SDL_KEYDOWN;
//    e.key.state = SDL_PRESSED;
//    e.key.keysym.sym = SDLK_F4;
//    SDL_PushEvent(&e);
//}
//
//void  Cmd_Window()
//{
//    SDL_Event e;
//    e.key.type = SDL_KEYDOWN;
//    e.key.state = SDL_PRESSED;
//    e.key.keysym.sym = SDLK_F5;
//    SDL_PushEvent(&e);
//}
//
//void Cmd_SetFontShadow(bool b)
//{
//    CCommon::common.FONT_SHADOW = b;
//}
//
bool Cmd_Message(string name, string msg)
{
    if(CResourceManager::_MessageBoxControl._MessageBoxList.count(name) < 1){
            cout << "Cmd_Message(): MessageBox \"" << name << "\" has no existed." <<endl;
        return false;
    }

    CResourceManager::_MessageBoxControl._MessageBoxList[name].SetText(msg);
    return true;
}
//
//bool Cmd_SetMessageBoxSpeakerName(string name)
//{
//    return CMessageBox::messagebox.SetSpeakerName(name.c_str());
//}
//
bool Cmd_AddMessageBox(string name, const char* filename)
{
    switch (CResourceManager::_MessageBoxControl.AddMessageBox(name, filename))
    {
        case 0:
            return true;
        break;
        case -1:
            cout << "Cmd_AddMessageBox(): MessageBox \"" << name << "\" has existed." <<endl;
        break;
        case -2:
            cout << "Cmd_AddMessageBox(): failed to add MessageBox." << endl;
        break;
    }

    return false;
}

bool Cmd_DelMessageBox(string name)
{
    if (CResourceManager::_MessageBoxControl.DelMessageBox(name))
        return true;

    cout << "Cmd_DelMessageBox(): can't find MessageBox \""<< name << "\"." <<endl;
    return false;
}

bool Cmd_ShowMessageBox(string name, int incr, bool pause)
{
    if (!CResourceManager::_MessageBoxControl.SetImageVisibility(name, 255, incr, pause)){
        cout << "Cmd_ShowMessageBox(): can't find MessageBox \""<< name << "\"." <<endl;
        return false;
    }

    return true;
}

bool Cmd_HideMessageBox(string name, int incr, bool pause)
{
    if (!CResourceManager::_MessageBoxControl.SetImageVisibility(name, 0, incr, pause)){
        cout << "Cmd_HideMessageBox(): can't find MessageBox \""<< name << "\"." <<endl;
        return false;
    }

    return true;
}
//
//
//bool Cmd_MenuBoxAddBtn(string name, const char* filename, const char* section)
//{
//    return CMenuBox::menubox.AddBtn(name, filename, section);
//}
//
//bool Cmd_MenuBoxDelBtn(string name)
//{
//    return CMenuBox::menubox.DelBtn(name);
//}
//
//int Cmd_ShowMenuBox(const char* filename, const char* section, bool pause)
//{
//    if (CMenuBox::menubox.Visible)
//        return 0;
//
//    if(!CParser::parser.ExecuteAllCmd(filename, section))
//        return -1;
//
//    CMenuBox::menubox.Refresh();
//    if (pause)
//        CMenuBox::menubox.Show(&CParser::parser.Pause);
//    else
//        CMenuBox::menubox.Show(NULL);
//
//    return 1;
//}
//
//bool Cmd_HideMenuBox(bool pause)
//{
//    if (!CMenuBox::menubox.Visible)
//        return false;
//
//    CMenuBox::menubox.ClearBtn();
//    if (pause)
//        CMenuBox::menubox.Hide(&CParser::parser.Pause);
//    else
//        CMenuBox::menubox.Hide(NULL);
//
//    return true;
//}
//
//bool Cmd_ShowInfoBox(bool pause)
//{
//    if (CObjectInfoBox::objectinfobox.Visible)
//        return false;
//
//    if (pause)
//        CObjectInfoBox::objectinfobox.Show(&CParser::parser.Pause);
//    else
//        CObjectInfoBox::objectinfobox.Show(NULL);
//    
//    return true;
//}
//
//bool Cmd_HideInfoBox(bool pause)
//{
//    if (!CObjectInfoBox::objectinfobox.Visible)
//        return false;
//
//    if (pause)
//        CObjectInfoBox::objectinfobox.Hide(&CParser::parser.Pause);
//    else
//        CObjectInfoBox::objectinfobox.Hide(NULL);
//    
//    return true;
//}
//
//bool Cmd_ShowLogBox(bool pause)
//{
//    if (CLogBox::logbox.Visible)
//        return false;
//
//    if (pause)
//        CLogBox::logbox.Show(&CParser::parser.Pause);
//    else
//        CLogBox::logbox.Show(NULL);
//    
//    return true;
//}
//
//bool Cmd_HideLogBox(bool pause)
//{
//    if (!CLogBox::logbox.Visible)
//        return false;
//
//    if (pause)
//        CLogBox::logbox.Hide(&CParser::parser.Pause);
//    else
//        CLogBox::logbox.Hide(NULL);
//    
//    return true;
//}
//
//void Cmd_PrintInfoBox(const char* type, string id)
//{
//    if (strcmp(type, "Equip") == 0)
//    {
//        //CObjectListBox::objectlistbox.List.type = TYPE_EQUIP;
//        //CObjectListBox::objectlistbox.List.ptr.equip_list = NULL;
//        //CObjectListBox::objectlistbox.List.ptr.equip_list = &CPlayerDataControl::playerdatacontrol.EquipList;
//    }
//    else if (strcmp(type, "Item") == 0)
//    {
//        //CObjectListBox::objectlistbox.List.type = TYPE_ITEM;
//        //CObjectListBox::objectlistbox.List.ptr.item_list = NULL;
//        //CObjectListBox::objectlistbox.List.ptr.item_list = &CPlayerDataControl::playerdatacontrol.ItemList;
//    }
//}
//
//bool Cmd_AddVariable(string name, string val, map<string, string> &var_table)
//{
//    name = "$" + name;
//    if(var_table.count(name) > 0)
//        return false;
//
//    var_table[name] = val;
//    return true;
//}
//
//bool Cmd_SetVariable(string name, string val, map<string, string> &var_table)
//{
//    name = "$" + name;
//    if(var_table.count(name) < 1)
//        return false;
//    
//    var_table[name] = val;
//    return true;
//}
//
//bool Cmd_DelVariable(string name, map<string, string> &var_table)
//{
//    name = "$" + name;
//    if(var_table.count(name) < 1)
//        return false;
//
//    var_table.erase(name);
//    return true;
//}
//
//bool Cmd_EditEquipList(string id, int num)
//{
//    if (!CLoadObject::loadobject.IsAlreadyExists("Equip", id.c_str()))
//        return -1;
//
//    for (int i = 0; i < CPlayerDataControl::playerdatacontrol.EquipList.size(); i++)
//    {
//        if (CPlayerDataControl::playerdatacontrol.EquipList[i].first.Name == id)
//        {
//            CPlayerDataControl::playerdatacontrol.EquipList[i].second += num;
//            if (CPlayerDataControl::playerdatacontrol.EquipList[i].second <= 0)
//            {
//                CPlayerDataControl::playerdatacontrol.EquipList.erase(
//                    CPlayerDataControl::playerdatacontrol.EquipList.begin() + i);
//            }
//
//            return 1;
//        }
//    }
//
//    if (num < 1)
//        return 0;
//
//    Equip equip;
//    if(CLoadObject::loadobject.GetEquip(id.c_str(),equip))
//    {
//        CPlayerDataControl::playerdatacontrol.EquipList.push_back(make_pair(equip, num));
//        return 1;
//    }
//    else
//        return -2;
//}
//
//bool Cmd_EditItemList(string id, int num)
//{
//    if (!CLoadObject::loadobject.IsAlreadyExists("Item", id.c_str()))
//        return -1;
//    
//    for (int i = 0; i < CPlayerDataControl::playerdatacontrol.ItemList.size(); i++)
//    {
//        if (CPlayerDataControl::playerdatacontrol.ItemList[i].first.Name == id)
//        {
//            CPlayerDataControl::playerdatacontrol.ItemList[i].second += num;
//            if (CPlayerDataControl::playerdatacontrol.ItemList[i].second <= 0)
//            {
//                CPlayerDataControl::playerdatacontrol.ItemList.erase(
//                    CPlayerDataControl::playerdatacontrol.ItemList.begin() + i);
//            }
//
//            return 1;
//        }
//    }
//
//    if (num < 1)
//        return 0;
//
//    Item item;
//    if(CLoadObject::loadobject.GetItem(id.c_str(), item))
//    {
//        CPlayerDataControl::playerdatacontrol.ItemList.push_back(make_pair(item, num));
//        return 1;
//    }
//    else
//        return -2;
//}
//
//void Cmd_EditMoney(int num)
//{
//    CPlayerDataControl::playerdatacontrol.Money += num;
//}
//
////void Cmd_SetMoney(int num)
////{
////    CPlayerDataControl::playerdatacontrol.Money = num;
////}
//
//void Cmd_DelCommand(vector<string> &cmdlist, int num)
//{
//    if (num > 0)
//    {
//        if (cmdlist.size() > 0)
//        {
//            if (cmdlist.size() > num)
//                cmdlist.erase(cmdlist.begin(), cmdlist.begin() + num);
//            else
//                cmdlist.clear();
//        }
//    }
//}
//
//bool Cmd_DelCommand(vector<string> &cmdlist, string flag)
//{
//    flag = "#" + flag;
//    for(int i = 0; i < cmdlist.size() ; i++)
//    {
//        if (cmdlist[i] == flag)
//        {
//            Cmd_DelCommand(cmdlist, i + 1);
//            return true;
//        }
//    }
//    return false;
//}
//
//bool Cmd_AddMapEvent(string name, const char* filename, const char* section)
//{
//    if(CMapEventControl::MapEventControl.MapEventList.count(name) < 1)
//        return false;
//
//    vector<string> cmdlist;
//
//    if(CParser::parser.LoadScript(filename, section, cmdlist))
//    {
//        CMapEventControl::MapEventControl.MapEventList[name] = cmdlist;
//        cmdlist.clear();
//        return true;
//    }
//    else
//    {
//        cmdlist.clear();
//        return false;
//    }
//}
//
//bool Cmd_AddMapEventPoint(string name, int x, int y)
//{
//    for (int i = CMapEventControl::MapEventControl.EventPoint.size() - 1; i >= 0 ; i--)
//    {
//        if (CMapEventControl::MapEventControl.EventPoint[i].first == name &&
//            CMapEventControl::MapEventControl.EventPoint[i].second.first == x &&
//            CMapEventControl::MapEventControl.EventPoint[i].second.second == y)
//            return false;
//    }
//
//    CMapEventControl::MapEventControl.EventPoint.push_back(make_pair(name, make_pair(x, y)));
//    return true;
//}
//
//bool Cmd_DelMapEvent(string name)
//{
//    if(CMapEventControl::MapEventControl.MapEventList.count(name) < 1)
//        return false;
//
//    CMapEventControl::MapEventControl.MapEventList[name].clear();
//    CMapEventControl::MapEventControl.MapEventList.erase(name);
//
//    for (int i = CMapEventControl::MapEventControl.EventPoint.size() - 1; i >= 0 ; i--)
//    {
//        if (CMapEventControl::MapEventControl.EventPoint[i].first == name)
//            CMapEventControl::MapEventControl.EventPoint.erase(
//                CMapEventControl::MapEventControl.EventPoint.begin() + i);
//    }
//
//    return true;
//}
//
//void Cmd_ClearMapEvent()
//{
//    CMapEventControl::MapEventControl.OnCleanup();
//}
//
//bool Cmd_PlayAnimation(string name, int x, int y)
//{
//    return CAnimationBank::animationbank.PlayAnime(name, x, y);
//}
//
//int Cmd_ToNextAnimationData(string name)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(name) < 1)
//        return -1;
//
//    if (!CAnimationBank::animationbank.AnimationList[name].Running)
//        return -2;
//        
//    CAnimationBank::animationbank.AnimationList[name].Next();
//    return 0;
//}
//
//int Cmd_StopAnimation(string name)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(name) < 1)
//        return -1;
//
//    if (!CAnimationBank::animationbank.AnimationList[name].Running)
//        return -2;
//
//    CAnimationBank::animationbank.AnimationList[name].Stop();
//    return 0;
//}
//
//int Cmd_AddAnimationScript(string name, int framerate)
//{
//    if (framerate < 1)
//        return -1;
//    
//    if(CAnimationBank::animationbank.AnimationList.count(name) > 0)
//        return -2;
//
//    CAnimationBank::animationbank.AnimationList[name] = CAnimationScript(framerate);
//
//    return 0;
//}
//
//int Cmd_DelAnimationScript(string name)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(name) < 1)
//        return -1;
//
//    if (CAnimationBank::animationbank.AnimationList[name].Running)
//        return 0;
//
//    CAnimationBank::animationbank.AnimationList.erase(name);
//    return 1;
//}
//
//int Cmd_AddAnimationData(string scrname ,string dataname, string filename, 
//    int startindex, int maxframes, bool loop, int size, string se)
//{
//    if (maxframes < 1)
//        return -1;
//    
//    if(CAnimationBank::animationbank.AnimationList.count(scrname) < 1)
//        return -2;
//
//    CAnimationBank::animationbank.AnimationList[scrname].Script.push_back(
//        new CAnimationData(dataname, filename, startindex, maxframes, loop, size, se));
//
//    return 0;
//}
//
//int Cmd_DelAnimationData(string scrname, string dataname)
//{
//    if(CAnimationBank::animationbank.AnimationList.count(scrname) < 1)
//        return -1;
//    
//    if (CAnimationBank::animationbank.AnimationList[scrname].Running)
//        return -2;
//
//    int count = 0;
//    for (int i = CAnimationBank::animationbank.AnimationList[scrname].Script.size() - 1; i >= 0; i--)
//    {
//        if (CAnimationBank::animationbank.AnimationList[scrname].Script[i]->Name == dataname)
//        {
//            delete CAnimationBank::animationbank.AnimationList[scrname].Script[i];
//            CAnimationBank::animationbank.AnimationList[scrname].Script.erase(
//                CAnimationBank::animationbank.AnimationList[scrname].Script.begin() + i);
//            count++;
//        }
//    }
//    return count;
//}
//
//int Cmd_If(string op, string val1, string val2)
//{
//    bool b = true;
//
//    if (op == "<")
//    {
//        b = atoi(val1.c_str()) < atoi(val2.c_str());
//    }
//    else if (op == ">")
//    {
//        b = atoi(val1.c_str()) > atoi(val2.c_str());
//    }
//    else if (op == ">=")
//    {
//        b = atoi(val1.c_str()) >= atoi(val2.c_str());
//    }
//    else if (op == "<=")
//    {
//        b = atoi(val1.c_str()) <= atoi(val2.c_str());
//    }
//    else if (op == "==")
//    {
//        b = val1 == val2;
//    }
//    else if (op == "!=")
//    {
//        b = val1 != val2;
//    }
//    else
//    {
//        return -1;
//    }
//
//    if (b)
//        return 1;
//    else
//        return 0;
//}
