/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
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
#include "../Common/CAdder.h"
#include "../Common/CObject.h"

class CImageBaseClass : virtual public CAdderControl, public CObject
{
    public:
        enum EImageFlag{
            FLAG_POSITION = 1,
            FLAG_ALPHA = 2,
            FLAG_SCALE = 4,
            FLAG_ROTATION = 8,
        };

    private:
        using CAdderControl::OnLoop;
        using CAdderControl::Count;

        char                              _layerOrder;
        int                               _alpha;
        sf::Vector2f                      _scale;
        sf::Vector2f                      _coordinate;
        sf::Vector2f                      _offset;
        float                             _rotation;
        char                              _flag;
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
        
        virtual float& GetRotation();
        void SetRotation(float r);
        sf::Vector2f& GetPosition();
        virtual void SetPosition(float x, float y);
        virtual sf::Vector2f& GetOffset();
        virtual void SetOffset(float x, float y);

        virtual int& GetAlpha();
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

        virtual void OnRender(sf::RenderWindow* Surf_Dest);
        virtual void OnSubRender(sf::RenderWindow* Surf_Dest){}

        virtual bool OnLoop();
        virtual bool OnSubLoop(){return false;}

        virtual bool OnLButtonUp(int mX, int mY){return false;}
        virtual bool OnLButtonDown(int mX, int mY){return false;}
        virtual bool OnMouseMove(int mX, int mY){return false;}
        
        virtual void OnSaveData(ofstream& file) const;
        virtual bool GetVisible() const;
};

#endif
