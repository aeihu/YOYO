/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CAction.h"

CAction::CAction(int* val, int fin, int inc)
{
    _data._int = val;
    _dataOfFinish._int = fin;
    _incr._int = inc;
    _type = INT;
}

CAction::CAction(float* val, float fin, float inc)
{
    _data._float = val;
    _dataOfFinish._float = fin;
    _incr._float = inc;
    _type = FLOAT;
}

bool CAction::OnLoop()
{
    switch(_type)
    {
        case INT:
            if (*(_data._int) != _dataOfFinish._int){
                *(_data._int) += _incr._int;

                if (_incr._int < 0)
                    if (*(_data._int) < _dataOfFinish._int){
                        *(_data._int) = _dataOfFinish._int;
                        return true;
                    }
                else if (_incr._int > 0)
                    if (*(_data._int) > _dataOfFinish._int){
                        *(_data._int) = _dataOfFinish._int;
                        return true;
                    }
            }
            else
                return true;
        break;
        case FLOAT:
            if (*(_data._float) != _dataOfFinish._float){
                *(_data._float) += _incr._float;

                if (_incr._float < 0)
                    if (*(_data._float) < _dataOfFinish._float){
                        *(_data._float) = _dataOfFinish._float;
                        return true;
                    }
                else if (_incr._float > 0)
                    if (*(_data._float) > _dataOfFinish._float){
                        *(_data._float) = _dataOfFinish._float;
                        return true;
                    }
            }
            else
                return true;
        break;
        case FUNC:
        break;
    }

    return false;
}