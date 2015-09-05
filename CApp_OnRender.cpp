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
    _display->clear();

    CResourceControl::_ResourceManager.OnRender(_display);
    _display->display();
}


//==============================================================================
