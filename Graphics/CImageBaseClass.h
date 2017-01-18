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
    public:
        enum ESubNodeFlag{
            FLAG_NONE = 0,
            FLAG_ALPHA = 1,
            FLAG_COLOR = 2,
        };
    protected:
        bool                    _flipX;
        bool                    _flipY;
        list<CImageBaseClass*>  _childrenList;
        CImageBaseClass*        _baseNode;
        char                    _flag;

        bool SetBaseNode(CImageBaseClass* baseNode);
        void Loop(sf::Transformable* obj);
    public:
        CImageBaseClass();
        virtual ~CImageBaseClass();
        
        virtual void FlipX();
        virtual void FlipY();

        virtual void OnRender(sf::RenderTarget* Surf_Dest)=0;
        virtual void OnLoop()=0;
        
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);

        virtual bool AddChildNode(CImageBaseClass* child);
        virtual bool RemoveChildNode(CImageBaseClass* child);

        virtual float GetWidth() const = 0;
        virtual float GetHeight() const = 0;
        virtual void SetFlag(char flag);
        virtual char GetFlag() const;
        virtual sf::Transform GetTransform() = 0;

        virtual void CleanActionList();
        virtual void OnCleanup();

        virtual bool OnKeyDown(sf::Event::KeyEvent key);
        virtual bool OnKeyUp(sf::Event::KeyEvent key);
        virtual bool OnMouseMove(int mX, int mY);
        virtual bool OnMouseWheel(int delta);
        virtual bool OnLButtonDown(int mX, int mY);
        virtual bool OnLButtonUp(int mX, int mY);
        virtual bool OnRButtonDown(int mX, int mY);
        virtual bool OnRButtonUp(int mX, int mY);
        virtual bool OnMButtonDown(int mX, int mY);
        virtual bool OnMButtonUp(int mX, int mY);
};

#endif
