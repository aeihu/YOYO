/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBAISCPROPERTIES_H_
    #define _CBAISCPROPERTIES_H_

#include "CSequenceOfAction.h"
#include "CObject.h"
#include <SFML/Graphics.hpp>
#include <list>

using namespace std;

class CBaiscProperties : public CObject
{
    protected:
        sf::Vector2f                        _scale;
        sf::Vector2f                        _coordinate;
        sf::Vector2f                        _offset;
        float                               _rotation;
        
        list<CActionBaseClass*>             _actList;
    public:
        virtual float& GetRotation();
        void SetRotation(float r);
        sf::Vector2f& GetPosition();
        virtual void SetPosition(float x, float y);
        virtual sf::Vector2f& GetOffset();
        virtual void SetOffset(float x, float y);
        virtual void SetOffsetX(float x);
        virtual void SetOffsetY(float y);

        virtual sf::Vector2f& GetScale();
        virtual void SetScale(float x, float y);
        virtual void SetScaleX(float x);
        virtual void SetScaleY(float y);
        virtual bool AddAction(CActionBaseClass* act);
        virtual bool AddAction(float* val, size_t elapsed, float fin, bool pause, bool reset);
        //virtual bool AddAction(int* val, size_t elapsed, int fin);
        virtual bool AddActionOfRotation(size_t elapsed, float rotation, bool pause, bool reset);
        virtual bool AddActionOfScale(size_t elapsed, float x, float y, bool pause, bool reset);
        virtual bool AddActionOfScaleX(size_t elapsed, float x, bool pause, bool reset);
        virtual bool AddActionOfScaleY(size_t elapsed, float y, bool pause, bool reset);

        virtual bool AddActionOfMove(size_t elapsed, float x, float y, bool pause, bool reset);	  
        virtual bool AddActionOfMoveX(size_t elapsed, float x, bool pause, bool reset);
        virtual bool AddActionOfMoveY(size_t elapsed, float y, bool pause, bool reset);

        virtual bool OnLoop();
        virtual void OnSaveData(Object& json) const;
};

#endif
