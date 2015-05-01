/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnRender() {
    
    //sf::Clock _t;
    //_t.restart();
    _display->clear();

    CResourceControl::_ResourceManager.OnRender(_display);
    _display->display();
       // std::cout << _t.getElapsedTime().asMilliseconds() << std::endl;
}


//==============================================================================
