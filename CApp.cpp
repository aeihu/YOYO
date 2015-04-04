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
    _display = NULL;
	_EndableOfIcon = false;
    _running = true;
}

void CApp::SetWindow(bool isFirst)
{
    if (CCommon::_Common.FULL_SCREEN || isFirst){
        sf::View __tmpView = _display->getView();
        _display->clear();

        _display->create(sf::VideoMode(CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT, 32), 
        L"人魚と海と少年の夏", sf::Style::Close);
        _display->setView(__tmpView);

        if (_EndableOfIcon){
            _display->setIcon(_icon.getSize().x, _icon.getSize().y, _icon.getPixelsPtr());
        }
        
        if (CCommon::_Common.MAX_FPS < 1){
            _display->setVerticalSyncEnabled(true);
        }
        else{
            _display->setFramerateLimit(CCommon::_Common.MAX_FPS);
        }

        CCommon::_Common.FULL_SCREEN = false;
    }
}
        
void CApp::SetFullScreen(bool isFirst)
{
    if (!CCommon::_Common.FULL_SCREEN || isFirst){
        sf::View __tmpView = _display->getView();
        _display->clear();

        _display->create(sf::VideoMode(CCommon::_Common.WWIDTH, CCommon::_Common.WHEIGHT, 32), 
            L"人魚と海と少年の夏", sf::Style::Fullscreen);
        _display->setView(__tmpView);
        
        if (CCommon::_Common.MAX_FPS < 1){
            _display->setVerticalSyncEnabled(true);
        }
        else{
            _display->setFramerateLimit(CCommon::_Common.MAX_FPS);
        }
        if (_display->isOpen()){
            CCommon::_Common.FULL_SCREEN = true;
        }
        else
            SetWindow();
    }
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
    sf::Event __events;
    sf::Thread  __threadOfStdin(&FuncOfStdin);
    __threadOfStdin.launch();

	while(_display->isOpen() && _running){
		while(_display->pollEvent(__events)) {
			OnEvent(&__events);
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
