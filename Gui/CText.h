/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CTEXT_H_
    #define _CTEXT_H_ 

#include <SFML/Graphics.hpp>
#include "../Graphics/CImageBaseClass.h"
#include "../Text/CFont.h"
#include "../Text/CTextFunction.h"
#include "../Common/CResourceControl.h"

class CText : public CImageBaseClass
{
    private:
        string              _currcentFont;
        sf::Text            _sfText;
        sf::Color           _textColor;
        sf::Color           _shadowColor;
        bool                _shadowEnable;
        float               _shadowPercent;
    protected:
        
    public:
        CText();

        static CText* Create();

        virtual void OnRender(sf::RenderTarget* Surf_Dest);
        virtual void OnLoop();
        
        sf::Color GetColor() const;
        const sf::Vector2f& GetGlobalPosition() const;

        //void FlipX();
        //void FlipY();
        
        void SetShadowEnable(bool b);
        void SetShadowEnable(vector<string> args);

        void SetShadowPercent(float percent);
        void SetShadowPercent(vector<string> args);

        void SetFont(string name);
        void SetFont(vector<string> args);

        void SetStyle(size_t flag);
        void SetStyle(vector<string> args);

        void SetString(string str);
        void SetString(vector<string> args);

        void SetCharacterSize(size_t size);
        void SetCharacterSize(vector<string> args);

        void SetColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b); 
        void SetColor(vector<string> args);
        
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
};

#endif
