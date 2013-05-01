/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
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

		virtual void OnMouseWheel(int delta);	//Not implemented

		virtual void OnLButtonDown(int mX, int mY);

		virtual void OnLButtonUp(int mX, int mY);

		virtual void OnRButtonDown(int mX, int mY);

		virtual void OnRButtonUp(int mX, int mY);

		virtual void OnMButtonDown(int mX, int mY);

		virtual void OnMButtonUp(int mX, int mY);

		//virtual void OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value);

		//virtual void OnJoyButtonDown(Uint8 which,Uint8 button);

		//virtual void OnJoyButtonUp(Uint8 which,Uint8 button);

		//virtual void OnJoyHat(Uint8 which,Uint8 hat,Uint8 value);

		//virtual void OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel);

		virtual void OnMinimize();

		virtual void OnRestore();

		virtual void OnResize(int w,int h);

		virtual void OnExpose();

		virtual void OnExit();

		//virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
};

//==============================================================================

#endif
