/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#ifndef _CEVENTFUNCTIONS_H_
    #define _CEVENTFUNCTIONS_H_

#include <SFML/Window/Event.hpp>

class CEventFunctions
{
    public:
        virtual bool OnKeyDown(sf::Event::KeyEvent key) { return false; }
        virtual bool OnKeyUp(sf::Event::KeyEvent key) { return false; }
        virtual bool OnMouseMove(int mX, int mY) { return false; }
        virtual bool OnMouseWheel(int delta) { return false; }
        virtual bool OnLButtonDown(int mX, int mY) { return false; }
        virtual bool OnLButtonUp(int mX, int mY) { return false; }
        virtual bool OnRButtonDown(int mX, int mY) { return false; }
        virtual bool OnRButtonUp(int mX, int mY) { return false; }
        virtual bool OnMButtonDown(int mX, int mY) { return false; }
        virtual bool OnMButtonUp(int mX, int mY) { return false; }
};

#endif