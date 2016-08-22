/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(sf::Event* Event) {
    CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnKeyDown(sf::Event::KeyEvent key) {
    switch(key.code) {
        case sf::Keyboard::A: {
            CResourceControl::_ResourceManager.SetAuto(!CResourceControl::_ResourceManager.GetAuto());
            break;
        }
        case sf::Keyboard::Left: {

            break;
        }

        case sf::Keyboard::Right: {

            break;
        }

        case sf::Keyboard::Up: {
     
            break;
        }

        case sf::Keyboard::Down: {

            break;
        }
                        
        case sf::Keyboard::LControl: {
            CResourceControl::_ResourceManager.SkipOn();
            break;
        }
                        
        case sf::Keyboard::Return: {

            break;
        }
        case sf::Keyboard::Space: {
            break;
        }

        case sf::Keyboard::Escape: {

            break;
        }
        
        case sf::Keyboard::F4: {
            if (CCommon::_Common.FULL_SCREEN)
                SetWindow();
            else
                SetFullScreen();
            
            break;
        }

        case sf::Keyboard::F6: {
            CResourceControl::_ResourceManager.OnSaveData(0);
            break;
        }

        case sf::Keyboard::F10: {
            CResourceControl::_ResourceManager.OnLoadData(0);
            break;
        }
        
        default: {
        }
    }
}

//------------------------------------------------------------------------------
void CApp::OnKeyUp(sf::Event::KeyEvent key) {
    switch(key.code) {
        case sf::Keyboard::Up: {
                                   CResourceControl::_ResourceManager._LuaControl.GetLuaThreadInfo();
            break;
        }

        case sf::Keyboard::Down: {
            break;
        }

        case sf::Keyboard::Left: {
            break;
        }

        case sf::Keyboard::Right: {
            break;
        }

        case sf::Keyboard::Return: {

            break;
        }

        case sf::Keyboard::Space: {
            break;
        }

        case sf::Keyboard::Escape: {
          
            break;
        }

        case sf::Keyboard::LControl: {
            CResourceControl::_ResourceManager.SkipOff();
            break;
        }

        default: {
        }
    }
}

//------------------------------------------------------------------------------
void CApp::OnLButtonDown(int mX, int mY)
{
    CResourceControl::_ResourceManager.OnLButtonDown(mX, mY);
    CResourceControl::_ResourceManager.SetAuto(false);
}

void CApp::OnRButtonDown(int mX, int mY)
{    
    CResourceControl::_ResourceManager.OnRButtonDown(mX, mY);
    CResourceControl::_ResourceManager.SetAuto(false);
}

void CApp::OnRButtonUp(int mX, int mY)
{
    CResourceControl::_ResourceManager.OnRButtonUp(mX, mY);
}
//------------------------------------------------------------------------------
void CApp::OnLButtonUp(int mX, int mY)
{
    CResourceControl::_ResourceManager.OnLButtonUp(mX, mY);
}

//------------------------------------------------------------------------------
void CApp::OnMouseMove(int mX, int mY)
{
    CResourceControl::_ResourceManager.OnMouseMove(mX, mY);
}

//------------------------------------------------------------------------------
void CApp::OnExit() {
    _running = false;
}

//==============================================================================
