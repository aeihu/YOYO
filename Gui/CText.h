/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CTEXT_H_
    #define _CTEXT_H_ 

#include <SFML/Graphics.hpp>
#include "../Graphics/CImageBaseClass.h"

class CText : public CImageBaseClass
{
    private:
        sf::Text            _sfText;
        sf::Color           _textColor;
        sf::Color           _shadowColor;
    protected:
        
    public:
        CText();

        static CText* Create();

        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual bool OnLoop();
        
        void SetFont(sf::Font& font);
        void SetStyle(size_t flag);
        void SetString(string str);
        void SetCharacterSize(size_t size);
        void SetColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b); 
};

#endif
