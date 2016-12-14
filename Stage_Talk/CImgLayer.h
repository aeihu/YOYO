/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CIMGLAYER_H_
    #define _CIMGLAYER_H_

#include "../Graphics/CImageBaseClass.h"
#include "../Common/CConfigFile.h"

class CImgLayer : public CImageBaseClass, public CConfigFile
{
    private:
        void Flip();
    protected:
        sf::Texture*        _texture;
        sf::Sprite          _sprite;

        virtual bool LoadImg(const char* filename);
        virtual bool CheckList(Object json);
        virtual bool SetProperty(Object json, bool isLoad=true);
    public:
        CImgLayer();
        ~CImgLayer(){};
        
        static CImgLayer* Create(const char* filename);
        
        virtual void FlipX();
        virtual void FlipY();

        virtual void OnLoop();
        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
        virtual void OnCleanup();

        virtual sf::Transform CImgLayer::GetTransform();
};

#endif
