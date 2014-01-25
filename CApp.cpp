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
CApp::CApp() {
    sf_Display = NULL;
	
    Running = true;

	FullScreen = false;
}

//------------------------------------------------------------------------------
int CApp::OnExecute() 
{
    if(OnInit() == false) {
	  return -1;
    }
    sf::Event Event;

    while(Running) {
		while(sf_Display->IsOpen()){
			while(sf_Display->PollEvent(Event)) {
				OnEvent(&Event);
			}

			OnLoop();
			OnRender();
		}
    }

    OnCleanup();
    return 0;
}

//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
