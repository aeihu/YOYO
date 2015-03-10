/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CActionTo.h"

CActionTo::CActionTo(float* val, size_t elapsed, float fin, bool restore, bool pause)
{
    _val = NULL;
    if (val){
        _isRunning = false;
        _val = val;
        _valOfFinish = fin;
        _pause = pause;
        _restore = restore;
        _elapsed = elapsed;
    }
}

/*
    when result is true, it's mean action has finished
*/
bool CActionTo::OnLoop(bool cleanup)
{
    if (_val == NULL)
        return true;
    
    if (!_isRunning){
        _isRunning = true;
        _orgVal = *_val;

        if (_elapsed == 0)
            *_val = _valOfFinish;
        else
            _incr = abs((_valOfFinish - *_val) * ((1000.0f/(float)CCommon::_Common.MAX_FPS)/(float)_elapsed));
    }

    if ((*_val) != _valOfFinish){
        if (_skip){
            *_val = _valOfFinish;
            goto FINISH;
        }

        bool __b = (*_val) < _valOfFinish ? true:false; 
        (*_val) += __b ? _incr : -_incr;
        //(*_val) += (__b ? _incr : -_incr) * (_skip ? 10 : 1);
        //_skip = false;

        if (__b){
            if ((*_val) >= _valOfFinish){
                (*_val) = _valOfFinish;
                goto FINISH;
            }
        }
        else{
            if ((*_val) <= _valOfFinish){
                (*_val) = _valOfFinish;
                goto FINISH;
            }
        }
  
        return false;
    }
    else{
FINISH:
        if (_restore) *_val = _orgVal;
        
        _isRunning = false;
        return true;
    }
}

bool CActionTo::IsPause() const
{
    return _pause && _isRunning;
}
