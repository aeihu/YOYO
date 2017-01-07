/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CTEXT_H_
    #define _CTEXT_H_ 

#include <SFML/Graphics.hpp>
#include "../Graphics/CImageBaseClass.h"
#include "../Text/CFont.h"
#include "../Text/CTextFunction.h"

class CText : public CImageBaseClass
{
    private:
    protected:
        string              _currcentFont;
        sf::Text            _sfText;
        sf::Color           _shadowColor;
        bool                _shadowEnable;
        float               _shadowPercent;
        
    public:
        CText();

        static CText* Create();

        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual void OnLoop();
        
        const sf::Color& GetShadowColor() const;

        //void FlipX();
        //void FlipY();

        float GetShadowPercent() const;

        virtual sf::Transform GetTransform();
        void SetShadowEnable(bool b);
        void SetShadowPercent(float percent);
        void SetFont(string name);
        virtual void SetString(string str);
        void SetCharacterSize(size_t size);

        void SetStyle(size_t flag);
        void SetStyle(vector<string> args);

        void SetShadowColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);

        string GetString();
        
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
};

#endif
