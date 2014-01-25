/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

////=============================================================================
//#include "CFPS.h"
//
////=============================================================================
//CFPS CFPS::FPSControl;
//
////=============================================================================
//CFPS::CFPS() {
//    OldTime     = 0;
//    LastTime    = 0;
//
//    SpeedFactor    = 0;
//
//    Frames      = 0;
//    NumFrames   = 0;
//}
//
////=============================================================================
//void CFPS::OnLoop() {
//    if(OldTime + 1000 < SDL_GetTicks()) {
//        OldTime = SDL_GetTicks();
//
//        NumFrames = Frames;
//
//        Frames = 0;
//    }
//
//    SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * 32.0f;
//
//    LastTime = SDL_GetTicks();
//
//    Frames++;
//}
//
////=============================================================================
//int CFPS::GetFPS() {
//    return NumFrames;
//}
//
////------------------------------------------------------------------------------
//float CFPS::GetSpeedFactor() {
//    return SpeedFactor;
//}
//
////==============================================================================
