/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#ifndef _CEVENT_H_
    #define _CEVENT_H_

#include <SFML/Window/Event.hpp>

//==============================================================================
class CEvent {
    public:
        CEvent();

        virtual ~CEvent();

        virtual void OnEvent(sf::Event* Event);

        virtual void OnGainedFocus();

        virtual void OnLostFocus();

        virtual void OnKeyDown(sf::Event::KeyEvent key);

        virtual void OnKeyUp(sf::Event::KeyEvent key);

        virtual void OnMouseMove(int mX, int mY);

        virtual void OnMouseWheel(int delta);

        virtual void OnLButtonDown(int mX, int mY);

        virtual void OnLButtonUp(int mX, int mY);

        virtual void OnRButtonDown(int mX, int mY);

        virtual void OnRButtonUp(int mX, int mY);

        virtual void OnMButtonDown(int mX, int mY);

        virtual void OnMButtonUp(int mX, int mY);

        virtual void OnMinimize();

        virtual void OnRestore();

        virtual void OnResize(int w,int h);

        virtual void OnExpose();

        virtual void OnExit();

        //virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
};

//==============================================================================

#endif
