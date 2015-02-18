/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIMAGEBASECLASS_H_
    #define _CIMAGEBASECLASS_H_

#include <SFML/Graphics.hpp>
#include <list>
#include "../Graphics/CSurface.h"
#include "../Common/CBaiscProperties.h"
#include "../Action/CActionBy.h"

class CImageBaseClass : public CBaiscProperties
{
    public:
        enum ESubImageFlag{
            FLAG_ALPHA = 1,
            FLAG_SCALE = 2,
            FLAG_ROTATION = 4,
        };

    private:
        unsigned char                     _layerOrder;
        char                              _flag;
    protected:
        bool                              _visible;
        sf::Vector2f                      _origin;
        float                             _alpha;
    public:
        CImageBaseClass(float x=0.0f, float y=0.0f);
        virtual ~CImageBaseClass();

        virtual const float& GetAlpha() const;
        virtual void SetAlpha(int alpha);
        virtual void SetLayerOrder(char order);
        virtual void SetLayerOrder(vector<string> args);

        virtual const sf::Vector2f& GetOrigin() const;
        virtual void SetOrigin(float x, float y);
        virtual void SetOriginX(float x);
        virtual void SetOriginY(float y);

        virtual void SetFlag(char flag);
        virtual char GetFlag() const;
        virtual unsigned char GetLayerOrder() const;
 
        virtual CActionTo* CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore, bool pause);
        virtual CActionBy* CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore, bool pause);
        
        virtual CSimultaneousOfAction* CreateActionOfOriginTo(size_t elapsed, float x, float y, bool restore, bool pause);	  
        virtual CActionTo* CreateActionOfOriginXTo(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionTo* CreateActionOfOriginYTo(size_t elapsed, float y, bool restore, bool pause);
        
        virtual CSimultaneousOfAction* CreateActionOfOriginBy(size_t elapsed, float x, float y, bool restore, bool pause);	  
        virtual CActionBy* CreateActionOfOriginXBy(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionBy* CreateActionOfOriginYBy(size_t elapsed, float y, bool restore, bool pause);

        virtual void OnRender(sf::RenderTarget* Surf_Dest)=0;
        virtual bool OnLoop()=0;

        virtual bool OnLButtonUp(int mX, int mY){return false;}
        virtual bool OnLButtonDown(int mX, int mY){return false;}
        virtual bool OnMouseMove(int mX, int mY){return false;}
        
        virtual void OnSaveData(Object& json) const;
        virtual bool GetVisible() const;
};

#endif
