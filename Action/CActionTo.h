/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CACTION_H_
    #define _CACTION_H_

#include "CActionBaseClass.h"
#include "../Common/CCommon.h"

class CActionTo : public CActionBaseClass
{
    private:
        bool        _restore;
        float       _orgVal;
        float*      _val;
        float       _valOfFinish;
        float       _incr;
        bool        _isRunning;
        size_t      _elapsed;
    protected:
    public:
        CActionTo(float* val, size_t elapsed, float fin, bool restore=false, bool pause=false);

        bool PauseRequest() const;
        bool OnLoop(bool cleanup=true);
        virtual CActionBaseClass* Copy();
        virtual inline EActType GetType() { return ACTION_TO;}
};

#endif
