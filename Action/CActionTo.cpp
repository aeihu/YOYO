/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CActionTo.h"

CActionTo::CActionTo(float* val, size_t elapsed, float fin, bool restore)
{
    _val = NULL;
    if (val){
        _isRunning = false;
        _val = val;
        _valOfFinish = fin;
        _restore = restore;
        _elapsed = elapsed;
    }
}

/*
    when result is true, it's mean action has finished
*/
bool CActionTo::OnLoop()
{
    if (_val == NULL)
        return true;
    
    if (!_isRunning){
        _isRunning = true;
        _orgVal = *_val;

        if (_elapsed == 0)
            *_val = _valOfFinish;
        else{
            float __fps = 60.0f;
            if (CCommon::_Common.MAX_FPS > 0)
                __fps = (float)CCommon::_Common.MAX_FPS;

            _incr = abs((_valOfFinish - *_val) * ((1000.0f/__fps)/(float)_elapsed));
        }
    }

    if ((*_val) != _valOfFinish){
        if (_skip || _allSkip){
            *_val = _valOfFinish;
            goto FINISH;
        }

        bool __b = (*_val) < _valOfFinish ? true:false; 
        (*_val) += __b ? _incr : -_incr;

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
        
        _skip = _isRunning = false;
        return true;
    }
}

CActionBaseClass* CActionTo::Copy()
{
    return new CActionTo(_val, _elapsed, _valOfFinish, _restore);
}
