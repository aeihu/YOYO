/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CButton.h"
#include "../Common/CResourceControl.h"

void CButton::Exec(void* data)
{
    CResourceControl::_ResourceManager._LuaControl.RunScript(_scr);
}

//================================
//property:
//* PATH,
//* ORDER,
//* WIDTH,
//* HEIGHT,
//* MAX_FRAMES,
//* FRAME_RATE,
//* SCRIPT,
//SCALE,
//SCALE_X,
//SCALE_Y,
//ROTATION,
//ORIGIN_X,
//ORIGIN_Y,
//X,
//Y,
//RED,
//GREEN,
//BLUE,
//ALPHA,
//================================
bool CButton::CheckList(const Object& json)
{
    bool result = CButtonBase::CheckList(json);

    if (!json.has<String>("SCRIPT")){
        cout << "can't find value of SCRIPT." << endl;
        result = false;
    }

    return result;
}

bool CButton::SetProperty(const Object& json, bool isLoad)
{
    _scr = json.get<String>("SCRIPT");
    return CButtonBase::SetProperty(json, isLoad);
}

CButton* CButton::Create(const char* filename)
{
    CButton* __btn = new CButton();
    if (__btn->LoadConfigFile(filename)){
        __btn->SetClassName("Button");
        __btn->SetPath(filename);
        __btn->SetLayerOrder(161);
        return __btn;
    }
    
    delete __btn;
    return NULL;
}
