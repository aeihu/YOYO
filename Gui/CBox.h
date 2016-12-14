/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CBOX_H_
    #define _CBOX_H_

#include "../Graphics/CSurface.h"
#include "../Common/CCommon.h"
#include "CGuiCommon.h"
#include "../Common/CConfigFile.h"
#include "../Stage_Talk/CImgLayer.h"

class CBox : public CImgLayer
{
    private:
        bool         _isJiugone;
        unsigned int _width;
        unsigned int _height;
    protected:
        class CJiugong : public sf::Drawable, public sf::Transformable
        {
        private:
            const sf::Texture*    _pTexture;
            sf::VertexArray       _vertexArray;

            void SetVectorForVertexArray(
                sf::Vector2f* vectors,
                unsigned int width,
                unsigned int height,
                unsigned int leftWidth,
                unsigned int rightWidth,
                unsigned int topHeight,
                unsigned int bottomHeight);
        public:
            CJiugong();

            void SetTexture(const sf::Texture& texture,
                unsigned int width,
                unsigned int height,
                unsigned int leftWidth,
                unsigned int rightWidth,
                unsigned int topHeight,
                unsigned int bottomHeight);

            void SetWidth(float width);
            void SetHeight(float height);
            void SetColor(const sf::Color& color);
            const sf::Color& GetColor() const;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        };

        CJiugong    _jiugong;

        virtual bool CheckList(Object json);
        virtual bool SetProperty(Object json, bool isLoad=true);
    public:
        CBox();
        ~CBox();

        virtual sf::Transform GetTransform();
        virtual void OnLoop();
        virtual void OnRender(sf::RenderTarget* Surf_Dest);
};
#endif
