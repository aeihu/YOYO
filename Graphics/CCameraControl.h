/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CCAMERACONTROL_H_
    #define _CCAMERACONTROL_H_

#include "CCamera.h"

class CCameraControl
{
    private:
        map<string, CCamera*>           _cameraList;
        sf::RenderTarget*               _display;
        string                          _currcentCamera;
    protected:
    public:
        bool AddCamera(string name, string filename);
        bool ResetCamera(string name);
        bool DelCamera(string name);
        CCamera* GetCamera(string name);
        
        void UseCamera(vector<string> args);
        bool UseCamera(string name);
        void UseDefaultCamera();

        bool OnInit(sf::RenderTarget* display);
        void OnLoop();
        void OnCleanup();
        void OnSaveData(Object& json) const;
        void OnLoadData(Object json);
};


#endif