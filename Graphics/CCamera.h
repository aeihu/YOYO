/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CCAMERA_H_
    #define _CCAMERA_H_ 

#include <SFML/Graphics.hpp>
#include "../Common/CBaiscProperties.h"
#include "../Common/CConfigFile.h"

class CCamera : public CBaiscProperties, public CConfigFile
{
    private:
        sf::View            _camera;
        sf::Vector2f        _size;

        bool CheckList(Object json);
        bool SetProperty(Object json);
    protected:
    public:
        static CCamera* CCamera::Create(const char* filename);

        void Reset(float x, float y, float w, float h);
        void SetViewport(float x, float y, float w, float h);
        void SetCenter(float x, float y);
        void SetSize(float w, float h);
        void SetZoom(float zoom);
        void SetRotation(float angle);
        void Bind(sf::RenderTarget* window);
        bool OnLoop();
        sf::Vector2f GetCenter();
        sf::Vector2f GetPosition();
        virtual void OnSaveData(Object& json) const;
};


#endif
