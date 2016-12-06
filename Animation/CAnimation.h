/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/
#ifndef _CANIMATION_H_
  #define _CANIMATION_H_

#include "../Common/CCommon.h"
//==============================================================================
class CAnimation {
    private:
        bool                    _enable;
        bool                    _isLoop;
        int                     _currentFrame;
        int                     _frameInc;
        int                     _frameRate; //Milliseconds
        unsigned long           _oldTime;
        int                     _maxFrames;

        void                    OnOscillate();
        void                    OnForWard();
        void                    OnBackWard();
    public:
        typedef enum{
            Oscillate,
            Forward,
            Backward
        } eAnimationType;

        eAnimationType          _Type;

        CAnimation();
        void OnAnimate(unsigned long time);
        void SetFrameRate(int rate);
        void SetCurrentFrame(int frame);
        int GetCurrentFrame() const;
        bool GetEnable() const;
        void SetFrameInc(int inc);
        virtual void TurnOn(bool loop);
        virtual void TurnOff();
        void SetMaxFrames(int frame);
        int GetMaxFrames() const;
};

//==============================================================================

#endif
