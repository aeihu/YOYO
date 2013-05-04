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
void CApp::OnEvent(sf::Event* Event) {
    CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnKeyDown(sf::Event::KeyEvent key) {
    switch(key.Code) {
        case sf::Key::Left: {
            //CPositions::PositionsControl.Move("ma",0, 50, 5, true);
            //CPositions::PositionsControl._characterList["ma"].SetFace("FACE1");
            //switch (CCommon::common.EventFocus)
            //{
            //    case BUTTON_FOCUS: 
            //    break;
            //    case MAP_FOCUS:
            //        if (CPlayerControl::PlayerList.size() > 0)
            //            CPlayerControl::PlayerList[0]->MoveLeft = true;
            //    break;
            //    case MESSAGEBOX_FOCUS:
            //    break;
            //    case MENUBOX_FOCUS:
            //    break;
            //    case LOGBOX_FOCUS:
            //    break;
            //    case BUTTON_STATE:
            //    break;
            //}

            break;
        }

        case sf::Key::Right: {
            //CPositions::PositionsControl.Move("ma",660, 0, 5, true);
            //CPositions::PositionsControl._characterList["ma"].SetFace("FACE2");
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                    //if (CPlayerControl::PlayerList.size() > 0)
                    //    CPlayerControl::PlayerList[0]->MoveRight = true;
                break;
                case MESSAGEBOX_FOCUS:
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }
            break;
        }

        case sf::Key::Up: {
            //CPositions::PositionsControl._characterList["ma"].SetFace("FACE3");
            //switch (CCommon::common.EventFocus)
            //{
            //    case BUTTON_FOCUS: 
            //    break;
            //    case MAP_FOCUS:
            //        if (CPlayerControl::PlayerList.size() > 0)
            //            CPlayerControl::PlayerList[0]->MoveUp = true;
            //    break;
            //    case MESSAGEBOX_FOCUS:
            //    break;
            //    case MENUBOX_FOCUS:
            //        if (CMenuBox::menubox.Visible)
            //            CMenuBox::menubox.IndexSubt();
            //    break;
            //    case LOGBOX_FOCUS:
            //        if (CLogBox::logbox.Visible)
            //            CLogBox::logbox.OffsetSubt();
            //    break;
            //    case BUTTON_STATE:
            //    break;
            //}

            break;
        }

        case sf::Key::Down: {
            //CPositions::PositionsControl._characterList["ma"].SetFace("FACE4");
            //switch (CCommon::common.EventFocus)
            //{
            //    case BUTTON_FOCUS: 
            //    break;
            //    case MAP_FOCUS:
            //        if (CPlayerControl::PlayerList.size() > 0)
            //            CPlayerControl::PlayerList[0]->MoveDown = true;
            //    break;
            //    case MESSAGEBOX_FOCUS:
            //    break;
            //    case MENUBOX_FOCUS:
            //        if (CMenuBox::menubox.Visible)
            //            CMenuBox::menubox.IndexIncr();
            //    break;
            //    case LOGBOX_FOCUS:
            //        if (CLogBox::logbox.Visible)
            //            CLogBox::logbox.OffsetIncr();
            //    break;
            //    case BUTTON_STATE:
            //    break;
            //}

            break;
        }
                        
        case sf::Key::Return: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                break;
                case MESSAGEBOX_FOCUS:
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }

            break;
        }
        case sf::Key::Space: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                break;
                case MESSAGEBOX_FOCUS:
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }
            break;
        }

        case sf::Key::Escape: {
            
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                //    SetGameState(MESSAGEBOX_FOCUS);
                break;
                case MESSAGEBOX_FOCUS:
                //    SetGameState(MAP_FOCUS);
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
//                    CLogBox::logbox.OnRButtonDown(0, 0);
                break;
                case BUTTON_STATE:
                break;
            }

            break;
        }
        
        case sf::Key::F4: {
            if (!FullScreen)
            {
                
                sf_Display->Create(
                    sf::VideoMode(
                    CCommon::common.WWIDTH, 
                    CCommon::common.WHEIGHT, 32), CCommon::common.GAME_NAME, sf::Style::Fullscreen);
                //if((sf_Display = SDL_SetVideoMode(
                //    CCommon::common.WWIDTH, 
                //    CCommon::common.WHEIGHT, 32,  SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)) == NULL) {
                //        cout << "Unable to set "<< CCommon::common.WWIDTH << "x" << CCommon::common.WHEIGHT 
                //            <<" video: " << SDL_GetError() << endl;
                //    return;
                //}
                FullScreen = true;
            }
            else{
                sf_Display->Create(
                    sf::VideoMode(
                    CCommon::common.WWIDTH, 
                    CCommon::common.WHEIGHT, 32), CCommon::common.GAME_NAME);
            
                FullScreen = false;
            }
            break;
        }
        
        default: {
        }
    }
}

//------------------------------------------------------------------------------
void CApp::OnKeyUp(sf::Event::KeyEvent key) {
    switch(key.Code) {
        case sf::Key::Up: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                    //if (CPlayerControl::PlayerList.size() > 0)
                    //    CPlayerControl::PlayerList[0]->MoveUp = false;
                break;
                case MESSAGEBOX_FOCUS:
                break;
                case MENUBOX_FOCUS:
                    //CMenuBox::menubox.OnLButtonUp( 0,0);
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }
            break;
        }

        case sf::Key::Down: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                    //if (CPlayerControl::PlayerList.size() > 0)
                    //    CPlayerControl::PlayerList[0]->MoveDown = false;
                break;
                case MESSAGEBOX_FOCUS:
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }
            break;
        }

        case sf::Key::Left: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                    //if (CPlayerControl::PlayerList.size() > 0)
                    //    CPlayerControl::PlayerList[0]->MoveLeft = false;
                break;
                case MESSAGEBOX_FOCUS:

                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }
            break;
        }

        case sf::Key::Right: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                    //if (CPlayerControl::PlayerList.size() > 0)
                    //    CPlayerControl::PlayerList[0]->MoveRight = false;
                break;
                case MESSAGEBOX_FOCUS:
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }
            break;
        }

        case sf::Key::Return: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                break;
                case MESSAGEBOX_FOCUS:
                    //CMessageBox::messagebox.Scroll();
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }

            break;
        }

        case sf::Key::Space: {
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                break;
                case MESSAGEBOX_FOCUS:
                    //CMessageBox::messagebox.Scroll();
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }
            break;
        }

        case sf::Key::Escape: {
            
            switch (CCommon::common.EventFocus)
            {
                case BUTTON_FOCUS: 
                break;
                case MAP_FOCUS:
                break;
                case MESSAGEBOX_FOCUS:
//                    CMessageBox::messagebox.OnRButtonDown(0,0);
                break;
                case MENUBOX_FOCUS:
                break;
                case LOGBOX_FOCUS:
                break;
                case BUTTON_STATE:
                break;
            }

            break;
        }

        default: {
        }
    }
}

//------------------------------------------------------------------------------
void CApp::OnLButtonDown(int mX, int mY)
{
    {
        map<std::string, CButton>::iterator it;
        for ( it=CResourceManager::_ButtonControl._ButtonList.begin();it!=CResourceManager::_ButtonControl._ButtonList.end(); it++ )
        {
            if ((*it).second.OnLButtonDown(mX,mY))
                return;
        }
    }

    {
        map<string, CMessageBox>::iterator it;
        for ( it=CResourceManager::_MessageBoxControl._MessageBoxList.begin(); it!=CResourceManager::_MessageBoxControl._MessageBoxList.end(); it++ )
        {
            if ((*it).second.OnLButtonDown(mX,mY))
                return;
        }
    }
}

void CApp::OnRButtonDown(int mX, int mY)
{    
    //switch (CCommon::common.EventFocus)
    //{
    //    case BUTTON_FOCUS: 
    //        {
    //        }
    //    break;
    //    case MAP_FOCUS:
    //        if (CPlayerControl::PlayerList.size() > 0)
    //            CPlayerControl::PlayerList[0]->MouseDown = true;
    //    break;
    //    case MESSAGEBOX_FOCUS:
    //        CMessageBox::messagebox.OnRButtonDown(mX, mY);
    //    break;
    //    case MENUBOX_FOCUS:
    //    break;
    //    case LOGBOX_FOCUS:
    //        CLogBox::logbox.OnRButtonDown(mX, mY);
    //    break;
    //    case BUTTON_STATE:
    //    break;
    //}
}

void CApp::OnRButtonUp(int mX, int mY)
{
}
//------------------------------------------------------------------------------
void CApp::OnLButtonUp(int mX, int mY)
{
    {
        map<std::string, CButton>::iterator it;
        for ( it=CResourceManager::_ButtonControl._ButtonList.begin();it!=CResourceManager::_ButtonControl._ButtonList.end(); it++ )
        {
            if ((*it).second.OnLButtonUp(mX,mY))
                return;
        }
    }

    {
        map<string, CMessageBox>::iterator it;
        for ( it=CResourceManager::_MessageBoxControl._MessageBoxList.begin(); it!=CResourceManager::_MessageBoxControl._MessageBoxList.end(); it++ )
        {
            if ((*it).second.OnLButtonUp(mX,mY))
                return;
        }
    }
}


//------------------------------------------------------------------------------
void CApp::OnMouseMove(int mX, int mY)
{
    map<std::string, CButton>::iterator it;
    for ( it=CResourceManager::_ButtonControl._ButtonList.begin();it!=CResourceManager::_ButtonControl._ButtonList.end(); it++ )
    {
        //cout<< mX << "," << mY <<endl;
        (*it).second.OnMouseMove(mX,mY);
    }
}

//------------------------------------------------------------------------------
void CApp::OnExit() {
    Running = false;
}

//==============================================================================
