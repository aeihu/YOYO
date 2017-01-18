/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CEvent.h"
#include <iostream>
//==============================================================================
CEvent::CEvent() {
}

//------------------------------------------------------------------------------
CEvent::~CEvent() {
    //Do nothing
}

//==============================================================================
void CEvent::OnEvent(sf::Event* Event) {
    switch(Event->type) {
        case sf::Event::GainedFocus: {
            OnGainedFocus();
            break;
        }
                                     
        case sf::Event::LostFocus: {
            OnLostFocus();
            break;
        }

        case sf::Event::KeyPressed: {
            OnKeyDown(Event->key);
            break;
        }

        case sf::Event::KeyReleased: {
            OnKeyUp(Event->key);
            break;
        }
 
        case sf::Event::MouseMoved: {
            OnMouseMove(Event->mouseMove.x, Event->mouseMove.y);
            break;
        }

        case sf::Event::MouseWheelScrolled: {
            OnMouseWheel(Event->mouseWheelScroll.delta);
            break;
        }

        case sf::Event::MouseButtonPressed: {
            switch(Event->mouseButton.button) {
                case sf::Mouse::Left: {
                    OnLButtonDown(Event->mouseButton.x, Event->mouseButton.y);
                    break;
                }
                case sf::Mouse::Right: {
                    OnRButtonDown(Event->mouseButton.x, Event->mouseButton.y);
                    break;
                }
                case sf::Mouse::Middle: {
                    OnMButtonDown(Event->mouseButton.x, Event->mouseButton.y);
                    break;
                }
            }
            break;
        }

        case sf::Event::MouseButtonReleased:{
            switch(Event->mouseButton.button) {
                case sf::Mouse::Left: {
                    OnLButtonUp(Event->mouseButton.x, Event->mouseButton.y);
                    break;
                }
                case sf::Mouse::Right: {
                    OnRButtonUp(Event->mouseButton.x, Event->mouseButton.y);
                    break;
                }
                case sf::Mouse::Middle: {
                    OnMButtonUp(Event->mouseButton.x, Event->mouseButton.y);
                    break;
                }
            }
            break;
        }

        case sf::Event::Closed: {
            OnExit();
            break;
        }

        //case SDL_SYSWMEVENT: {
        //    //Ignore
        //    break;
        //}

        case sf::Event::Resized: {
            //OnResize(Event->resize.w,Event->resize.h);
            break;
        }

        //case SDL_VIDEOEXPOSE: {
        //    OnExpose();
        //    break;
        //}

        //default: {
        //    OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
        //    break;
        //}
    }
}

//------------------------------------------------------------------------------
void CEvent::OnGainedFocus() {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnLostFocus() {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnKeyDown(sf::Event::KeyEvent key) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnKeyUp(sf::Event::KeyEvent key) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMouseMove(int mX, int mY) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMouseWheel(int delta) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
//void CEvent::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
//    //Pure virtual, do nothing
//}
//
////------------------------------------------------------------------------------
//void CEvent::OnJoyButtonDown(Uint8 which,Uint8 button) {
//    //Pure virtual, do nothing
//}
//
////------------------------------------------------------------------------------
//void CEvent::OnJoyButtonUp(Uint8 which,Uint8 button) {
//    //Pure virtual, do nothing
//}
//
////------------------------------------------------------------------------------
//void CEvent::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
//    //Pure virtual, do nothing
//}
//
////------------------------------------------------------------------------------
//void CEvent::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
//    //Pure virtual, do nothing
//}

//------------------------------------------------------------------------------
void CEvent::OnMinimize() {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnRestore() {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnResize(int w,int h) {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnExpose() {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
void CEvent::OnExit() {
    //Pure virtual, do nothing
}

//------------------------------------------------------------------------------
//void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2) {
//    //Pure virtual, do nothing
//}

//==============================================================================
