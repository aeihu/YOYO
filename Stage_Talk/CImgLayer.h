/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIMGLAYER_H_
    #define _CIMGLAYER_H_

#include "../Graphics/CImageBaseClass.h"

class CImgLayer : public CImageBaseClass
{
    public:
        enum ESubImageFlag{
            FLAG_ALPHA = 1,
            FLAG_SCALE = 2,
            FLAG_ROTATION = 4,
        };

    private:
        char                        _flag;
        CImgLayer*                  _baseNode;
        list<CImgLayer*>            _childrenList;

        friend bool CImgLayer::SetBaseNode(CImgLayer* baseNode);
        bool SetBaseNode(CImgLayer* baseNode);
        void Flip();
    protected:
        sf::Texture         _texture;
        sf::Sprite          _sprite;

        virtual bool LoadImg(const char* filename);
    public:
        CImgLayer();
        ~CImgLayer(){};
        CImgLayer(float x, float y);
        
        static CImgLayer* Create(const char* filename);
        
        virtual void FlipX();
        virtual void FlipY();

        virtual void SetFlag(char flag);
        virtual char GetFlag() const;

        virtual bool AddChildNode(CImgLayer* child);
        const sf::Vector2f& GetGlobalPosition() const;

        virtual void OnLoop();
        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual void OnSaveData(Object& json) const;
};

#endif
