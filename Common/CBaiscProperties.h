/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CBAISCPROPERTIES_H_
    #define _CBAISCPROPERTIES_H_

#include "CSequenceOfAction.h"
#include "CSimultaneousOfAction.h"
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
        
        //CSequenceOfAction                   _actList;
    public:
        CBaiscProperties();

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
        //virtual bool AddAction(CActionBaseClass* act);
        virtual CAction* CreateActionOfRotation(size_t elapsed, float rotation, bool restore, bool pause);
        virtual CSimultaneousOfAction* CreateActionOfScale(size_t elapsed, float x, float y, bool restore, bool pause);
        virtual CAction* CreateActionOfScaleX(size_t elapsed, float x, bool restore, bool pause);
        virtual CAction* CreateActionOfScaleY(size_t elapsed, float y, bool restore, bool pause);

        virtual CSimultaneousOfAction* CreateActionOfMove(size_t elapsed, float x, float y, bool restore, bool pause);	  
        virtual CAction* CreateActionOfMoveX(size_t elapsed, float x, bool restore, bool pause);
        virtual CAction* CreateActionOfMoveY(size_t elapsed, float y, bool restore, bool pause);

        virtual bool OnLoop()=0;
        virtual void OnSaveData(Object& json) const;
};

#endif
