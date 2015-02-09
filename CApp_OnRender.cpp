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
void CApp::OnRender() {
    
    sf::Clock _t;
    _t.restart();
    sf_Display->clear();
 
    CResourceControl::_ResourceManager.OnRender(sf_Display);
    sf_Display->display();
       // std::cout << _t.getElapsedTime().asMilliseconds() << std::endl;
}


//==============================================================================
