/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CIMAGEBASECLASS_H_
    #define _CIMAGEBASECLASS_H_

#include <SFML/Graphics.hpp>
#include <list>
#include "../Graphics/CSurface.h"
#include "../Action/CActionBy.h"
#include "../Graphics/CDrawableClass.h"

class CImageBaseClass : public CDrawableClass
{
    protected:
        sf::Vector2f                      _origin;
        bool                              _flipX;
        bool                              _flipY;
    public:
        CImageBaseClass(float x=0.0f, float y=0.0f);
        virtual ~CImageBaseClass();
        
        virtual void FlipX();
        virtual void FlipY();
        virtual const sf::Vector2f& GetGlobalPosition() const =0;

        virtual const float& GetAlpha() const;
        virtual void SetAlpha(int alpha);

        virtual const sf::Vector2f& GetOrigin() const;
        virtual void SetOrigin(float x, float y);
        virtual void SetOriginX(float x);
        virtual void SetOriginY(float y);
        
        virtual CSimultaneousOfAction* CreateActionOfOriginTo(size_t elapsed, float x, float y, bool restore);      
        virtual CActionTo* CreateActionOfOriginXTo(size_t elapsed, float x, bool restore);
        virtual CActionTo* CreateActionOfOriginYTo(size_t elapsed, float y, bool restore);
        
        virtual CSimultaneousOfAction* CreateActionOfOriginBy(size_t elapsed, float x, float y, bool restore);      
        virtual CActionBy* CreateActionOfOriginXBy(size_t elapsed, float x, bool restore);
        virtual CActionBy* CreateActionOfOriginYBy(size_t elapsed, float y, bool restore);

        /////////////////////////////////////////////////

        virtual void CreateActionOfOriginToForSelf(size_t elapsed, float x, float y, bool restore);
        virtual void CreateActionOfOriginXToForSelf(size_t elapsed, float x, bool restore);
        virtual void CreateActionOfOriginYToForSelf(size_t elapsed, float y, bool restore);

        virtual void CreateActionOfOriginByForSelf(size_t elapsed, float x, float y, bool restore);
        virtual void CreateActionOfOriginXByForSelf(size_t elapsed, float x, bool restore);
        virtual void CreateActionOfOriginYByForSelf(size_t elapsed, float y, bool restore);

        virtual void OnRender(sf::RenderTarget* Surf_Dest)=0;
        virtual void OnLoop()=0;
        
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
        virtual bool GetVisible() const;
};

#endif
