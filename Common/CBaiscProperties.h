/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CBAISCPROPERTIES_H_
    #define _CBAISCPROPERTIES_H_

#include "../Action/CSequenceOfAction.h"
#include "../Action/CSimultaneousOfAction.h"
#include "CObject.h"
#include <SFML/Graphics.hpp>
#include <list>
#include "../Action/CActionBy.h"

using namespace std;

class CBaiscProperties : public CObject
{
    protected:
        sf::Vector2f                        _scale;
        sf::Vector2f                        _coordinate;
        float                               _rotation;
        
    public:
        CBaiscProperties();

        virtual float& GetRotation();
        void SetRotation(float r);
        sf::Vector2f& GetPosition();
        virtual void SetPosition(float x, float y);

        virtual sf::Vector2f& GetScale();
        virtual void SetScale(float x, float y);
        virtual void SetScaleX(float x);
        virtual void SetScaleY(float y);

        virtual CActionTo* CreateActionOfRotationTo(size_t elapsed, float rotation, bool restore, bool pause);
        virtual CActionBy* CreateActionOfRotationBy(size_t elapsed, float rotation, bool restore, bool pause);

        virtual CSimultaneousOfAction* CreateActionOfScaleTo(size_t elapsed, float x, float y, bool restore, bool pause);
        virtual CActionTo* CreateActionOfScaleXTo(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionTo* CreateActionOfScaleYTo(size_t elapsed, float y, bool restore, bool pause);

        virtual CSimultaneousOfAction* CreateActionOfScaleBy(size_t elapsed, float x, float y, bool restore, bool pause);
        virtual CActionBy* CreateActionOfScaleXBy(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionBy* CreateActionOfScaleYBy(size_t elapsed, float y, bool restore, bool pause);

        virtual CSimultaneousOfAction* CreateActionOfMoveTo(size_t elapsed, float x, float y, bool restore, bool pause);	  
        virtual CActionTo* CreateActionOfMoveXTo(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionTo* CreateActionOfMoveYTo(size_t elapsed, float y, bool restore, bool pause);

        virtual CSimultaneousOfAction* CreateActionOfMoveBy(size_t elapsed, float x, float y, bool restore, bool pause);	  
        virtual CActionBy* CreateActionOfMoveXBy(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionBy* CreateActionOfMoveYBy(size_t elapsed, float y, bool restore, bool pause);

        virtual void OnLoop()=0;
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
};

#endif
