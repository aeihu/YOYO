/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CAction.h"

CAction::CAction(float* val, size_t elapsed, float fin, bool restore, bool pause)
{
    _val = NULL;
    if (val){
        if (elapsed == 0) elapsed = 1;
        _val = val;
        _valOfFinish = fin;
        _pause = pause;
        _incr = (fin - *val) * ((1000.0f/(float)CCommon::_Common.MAX_FPS)/(float)elapsed);
        _orgVal = *val;
        _restore = restore;
    }
}

/*
    when result is true, it's mean action is finished
*/
bool CAction::OnLoop()
{
    if (_val == NULL)
        return true;

    if ((*_val) != _valOfFinish){
        (*_val) += _incr;

        if (_incr < 0){
            if ((*_val) < _valOfFinish)
                (*_val) = _valOfFinish;
        }
        else if (_incr > 0){
            if ((*_val) > _valOfFinish)
                (*_val) = _valOfFinish;
        }
  

        return false;
    }
    else{
        if (_restore) *_val = _orgVal;

        return true;
    }
}