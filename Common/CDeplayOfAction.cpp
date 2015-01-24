/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CDeplayOfAction.h"

CDeplayOfAction::CDeplayOfAction(size_t delay)
{
    _pause = true;
    _time = CCommon::_Common.GetTicks() + delay;
}

bool CDeplayOfAction::OnLoop()
{
    return _time < CCommon::_Common.GetTicks() ? true : false;
}