/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CFuncOfAction.h"

CFuncOfAction::CFuncOfAction(void (*func)())
{
    _func = func;
}

bool CFuncOfAction::OnLoop(bool cleanup)
{
    if (_func != 0){
        _func();
    }
    
    return true;
}
        
CActionBaseClass* CFuncOfAction::Copy()
{
    return new CFuncOfAction(_func);
}