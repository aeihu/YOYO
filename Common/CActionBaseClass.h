/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CACTIONBASECLASS_H_
    #define _CACTIONBASECLASS_H_

class CActionBaseClass
{
    protected:
        bool        _pause;
    public:
        CActionBaseClass() {_pause = false;}
        virtual bool OnLoop()=0; 
        virtual bool IsPause() {return _pause;}
};

#endif
