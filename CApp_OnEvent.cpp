/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
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
    switch(key.code) {
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
        
        default: {
        }
    }
}

//------------------------------------------------------------------------------
void CApp::OnKeyUp(sf::Event::KeyEvent key) {
    switch(key.code) {
        case sf::Keyboard::Up: {
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

        default: {
        }
    }
}

//------------------------------------------------------------------------------
void CApp::OnLButtonDown(int mX, int mY)
{
    CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonDown(mX, mY);
}

void CApp::OnRButtonDown(int mX, int mY)
{    

}

void CApp::OnRButtonUp(int mX, int mY)
{
}
//------------------------------------------------------------------------------
void CApp::OnLButtonUp(int mX, int mY)
{
    CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonUp(mX, mY);
}


//------------------------------------------------------------------------------
void CApp::OnMouseMove(int mX, int mY)
{
    CResourceControl::_ResourceManager._DrawableObjectControl.OnMouseMove(mX, mY);
}

//------------------------------------------------------------------------------
void CApp::OnExit() {
    _running = false;
}

//==============================================================================
