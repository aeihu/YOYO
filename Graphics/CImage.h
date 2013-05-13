/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIMAGE_H_
    #define _CIMAGE_H_

#include "../Common/Define.h"
#include "CSprite.h"

class CImage
{
    private:
        sf::Texture _texture;
        friend void CSprite::SetTexture(const CImage &image, bool resetRect);
    public:
        CImage();
        ~CImage();
        void Create(unsigned int width, unsigned int height);
        bool LoadFromFile(const std::string &filename, const sf::IntRect &area=sf::IntRect());
        bool LoadFromMemory(const void *data, std::size_t size, const sf::IntRect &area=sf::IntRect());
        bool LoadFromImage(const sf::Image &image, const sf::IntRect &area=sf::IntRect());

        void SetSmooth(bool smooth);
        bool IsSmooth() const;
        unsigned int GetWidth();
        unsigned int GetHeight();
};

#endif
