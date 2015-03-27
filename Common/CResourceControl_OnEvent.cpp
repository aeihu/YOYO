/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CResourceControl.h"

//==============================================================================
void CResourceControl::OnEvent(sf::Event* Event) {
    CEvent::OnEvent(Event);
}

//==============================================================================
void CResourceControl::OnKeyDown(sf::Event::KeyEvent key) {
    if (!_pauseOfAction)
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
                //if (!FullScreen)
                //{
                //    FullScreen = true;
                //}
                //else{
                //    FullScreen = false;
                //}
                break;
            }
        
            default: {
            }
        }
}

//------------------------------------------------------------------------------
void CResourceControl::OnKeyUp(sf::Event::KeyEvent key) 
{
    if (!_pauseOfAction)
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
void CResourceControl::OnLButtonDown(int mX, int mY)
{
    if (!_pauseOfAction)
        CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonDown(mX, mY);
}

void CResourceControl::OnRButtonDown(int mX, int mY)
{    

}

void CResourceControl::OnRButtonUp(int mX, int mY)
{
}
//------------------------------------------------------------------------------
void CResourceControl::OnLButtonUp(int mX, int mY)
{
    if (!_pauseOfAction)
        CResourceControl::_ResourceManager._DrawableObjectControl.OnLButtonUp(mX, mY);
}


//------------------------------------------------------------------------------
void CResourceControl::OnMouseMove(int mX, int mY)
{
    if (!_pauseOfAction)
        CResourceControl::_ResourceManager._DrawableObjectControl.OnMouseMove(mX, mY);
}

//------------------------------------------------------------------------------
void CResourceControl::OnExit() 
{
    //Running = false;
}

//==============================================================================
