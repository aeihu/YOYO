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
CApp::CApp() {
    sf_Display = NULL;
	
    Running = true;

	FullScreen = false;
}

//------------------------------------------------------------------------------
void FuncOfStdin()
{
    string __cmd;
    while (true){
        getline(cin,__cmd);

        CParser::_Parser.CParser::ExecuteCmd(__cmd, NULL, false);
    }
}

//------------------------------------------------------------------------------
int CApp::OnExecute() 
{
    if(OnInit() == false) {
        OnCleanup();
        return -1;
    }
    sf::Event Event;
    sf::Thread  _threadOfStdin(&FuncOfStdin);
    _threadOfStdin.launch();
	while(sf_Display->isOpen() && Running){
		while(sf_Display->pollEvent(Event)) {
			OnEvent(&Event);
		}
        
		OnLoop();
		OnRender();
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
