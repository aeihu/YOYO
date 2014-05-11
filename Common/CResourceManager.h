/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CRESOURCEMANAGER_H_
    #define _CRESOURCEMANAGER_H_

#include "../Stage_Talk/CImgLayerControl.h"
#include "../Stage_Talk/CCharacterLayerControl.h"
#include "../GSM_Window/CMessageBoxControl.h"
#include "../GSM_Window/CLogBoxControl.h"
#include "../Effect/CParticleSystemControl.h"
#include "../Gui/CButtonControl.h"
#include "../Text/CFontControl.h"
#include "../Sound/CSoundBank.h"
#include "CPositionControl.h"

class CResourceManager
{
    private:
        template<typename X>
        void static GetInfo(const char* resourcename, map<string, X> xlist);
    public:
        static CParticleSystemControl   _ParticleSystemControl;
        static CCharacterLayerControl   _CharacterLayerControl;
        static CImgLayerControl         _ImgLayerControl;
        static CImgLayerControl         _BackgroundLayerControl;
        static CMessageBoxControl       _MessageBoxControl;
        static CButtonControl           _ButtonControl;
        static CPositionControl         _PositionControl;
        static CFontControl             _FontControl;
        static CLogBoxControl           _LogBoxControl;

        static void GetInfo();
};

#endif
