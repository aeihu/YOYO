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
#include "../Common/CConfigFile.h"
#include "../Stage_Talk/CImgLayer.h"

class CBox : public CImgLayer
{
    private:
        bool            _isJiugone;
    protected:
        class CJiugong : public sf::Drawable, public sf::Transformable
        {
        private:
            const sf::Texture*      _pTexture;
            sf::VertexArray         _vertexArray;

            void SetVectorForVertexArray(
                sf::Vector2f* vectors,
                size_t width,
                size_t height,
                size_t leftWidth,
                size_t rightWidth,
                size_t topHeight,
                size_t bottomHeight);
        public:
            CJiugong();

            void SetVertexArraySize(
                size_t width,
                size_t height,
                size_t leftWidth,
                size_t rightWidth,
                size_t topHeight,
                size_t bottomHeight);

            void SetTexture(const sf::Texture& texture);

            size_t GetWidth() const;
            size_t GetHeight() const;
            void SetWidth(float width);
            void SetHeight(float height);
            void SetColor(const sf::Color& color);
            const sf::Color& GetColor() const;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        };

        CJiugong    _jiugong;

        virtual bool CheckList(const Object& json);
        virtual bool SetProperty(const Object& json, bool isLoad = true);
        virtual bool LoadImg(string filename);
    public:
        CBox();
        ~CBox();

        virtual sf::Transform GetTransform();
        virtual bool Contains(float x, float y);
        virtual void OnLoop();
        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual float GetWidth();
        virtual float GetHeight();

        bool IsJiugone() const;
};
#endif
