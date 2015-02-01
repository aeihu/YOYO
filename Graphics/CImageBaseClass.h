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
#include "../Common/CActionBy.h"

class CImageBaseClass : public CBaiscProperties
{
    public:
        enum ESubImageFlag{
            FLAG_ALPHA = 1,
            FLAG_SCALE = 2,
            FLAG_ROTATION = 4,
        };

    private:
        char                              _layerOrder;
        char                              _flag;
        float                             _alpha;
        list<CImageBaseClass*>            _childrenList;
        CImageBaseClass*                  _baseNode;

        void Flip();
        friend bool CImageBaseClass::SetBaseNode(CImageBaseClass* baseNode);
        bool SetBaseNode(CImageBaseClass* baseNode);
    protected:
        sf::Texture                       _image;
        sf::Sprite                        _sprite;
        bool                              _visible;
        bool                              _flipX;
        bool                              _flipY;
        sf::Vector2f                      _origin;

        bool IsStandby();
        virtual bool LoadImg(const char* filename);
    public:
        CImageBaseClass(float x=0.0f, float y=0.0f);
        virtual ~CImageBaseClass();

        virtual void FlipX();
        virtual void FlipY();

        virtual bool AddChildNode(CImageBaseClass* child);

        virtual const float& GetAlpha() const;
        virtual void SetAlpha(int alpha);
        virtual void SetLayerOrder(char order);
        virtual void SetLayerOrder(vector<string> args);

        virtual const sf::Vector2f& GetScale() const;
        virtual void SetScale(float x, float y);
        virtual void SetScaleX(float x);
        virtual void SetScaleY(float y);

        virtual const sf::Vector2f& GetOrigin() const;
        virtual void SetOrigin(float x, float y);
        virtual void SetOriginX(float x);
        virtual void SetOriginY(float y);

        virtual void SetFlag(char flag);
        virtual char GetFlag() const;
        virtual char GetLayerOrder() const;
        virtual const sf::Vector2f& GetGlobalPosition() const;
        static CImageBaseClass* Create(const char* filename);
        virtual CActionTo* CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore, bool pause);
        virtual CActionBy* CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore, bool pause);
        
        virtual CSimultaneousOfAction* CreateActionOfOriginTo(size_t elapsed, float x, float y, bool restore, bool pause);	  
        virtual CActionTo* CreateActionOfOriginXTo(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionTo* CreateActionOfOriginYTo(size_t elapsed, float y, bool restore, bool pause);
        
        virtual CSimultaneousOfAction* CreateActionOfOriginBy(size_t elapsed, float x, float y, bool restore, bool pause);	  
        virtual CActionBy* CreateActionOfOriginXBy(size_t elapsed, float x, bool restore, bool pause);
        virtual CActionBy* CreateActionOfOriginYBy(size_t elapsed, float y, bool restore, bool pause);

        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual void OnSubRender(sf::RenderTarget* Surf_Dest){}

        virtual bool OnLoop();
        virtual bool OnSubLoop(){return false;}

        virtual bool OnLButtonUp(int mX, int mY){return false;}
        virtual bool OnLButtonDown(int mX, int mY){return false;}
        virtual bool OnMouseMove(int mX, int mY){return false;}
        
        virtual void OnSaveData(Object& json) const;
        virtual bool GetVisible() const;
};

#endif
