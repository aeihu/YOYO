/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCAMERACONTROL_H_
    #define _CCAMERACONTROL_H_

#include "CCamera.h"

class CCameraControl
{
    private:
        map<string, CCamera*>           _cameraList;
        sf::RenderWindow*               _display;
    protected:
    public:
        bool AddCamera(string name, string filename);
        bool DelCamera(string name);
        CCamera* GetCamera(string name);
        
        bool Move(string name, float x, float y, size_t elapsed, bool pause, bool reset);
        bool MoveX(string name, float x, size_t elapsed, bool pause, bool reset);
        bool MoveY(string name, float y, size_t elapsed, bool pause, bool reset);
        bool Zoom(string name, float zoom, size_t elapsed, bool pause, bool reset);
        bool Rotation(string name, float rotation, size_t elapsed, bool pause, bool reset);

        bool UseCamera(string name);
        bool UseDefaultCamera();

        bool OnInit(sf::RenderWindow* display);
};


#endif