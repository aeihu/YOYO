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

class CImageBaseClass : public CBaiscProperties// virtual public CAdderControl, 
{
    public:
        enum ESubImageFlag{
            FLAG_POSITION = 1,
            FLAG_ALPHA = 2,
            FLAG_SCALE = 4,
            FLAG_ROTATION = 8,
        };

    private:
        //using CAdderControl::OnLoop;
        //using CAdderControl::Count;

        char                              _layerOrder;
        char                              _flag;
        float                             _alpha;
    protected:
        sf::Texture                       _image;
        sf::Sprite                        _sprite;
        bool                              _visible;
        list<CImageBaseClass*>            _childrenList;

        bool IsStandby();
        virtual bool LoadImg(const char* filename);
    public:
        CImageBaseClass(float x=0.0f, float y=0.0f);
        virtual ~CImageBaseClass();

        virtual float& GetAlpha();
        virtual void SetAlpha(int alpha);
        virtual void SetLayerOrder(char order);

        virtual sf::Vector2f& GetScale();
        virtual void SetScale(float x, float y);
        virtual void SetScaleX(float x);
        virtual void SetScaleY(float y);
        virtual void SetFlag(char flag);
        virtual char GetFlag() const;
        virtual char GetLayerOrder() const;
        static CImageBaseClass* Create(const char* filename);
        virtual CAction* CreateActionOfAlpha(size_t elapsed, float alpha, bool restore, bool pause);

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
