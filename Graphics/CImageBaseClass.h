/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIMAGEBASECLASS_H_
    #define _CIMAGEBASECLASS_H_

#include <SFML/Graphics.hpp>
#include "../Graphics/CSurface.h"
#include "../Common/CAdder.h"
#include "../Common/Define.h"

class CImageBaseClass : virtual public CAdderControl
{
    private:
        using CAdderControl::OnLoop;
        using CAdderControl::Count;
    protected:
        CImage                      _image;
        CSprite                     _sprite;
        bool                        _visible;

        virtual bool Subclass_Loop(){return false;};
        virtual void Subclass_Render(CWindow* Surf_Dest){};
        bool IsStandby();
    public:
        CCoordinate2f               _Coordinate;
        int                         _Alpha;

        CImageBaseClass(float x=0.0f, float y=0.0f);
        virtual ~CImageBaseClass();

        virtual void OnRender(CWindow* Surf_Dest);
        virtual bool OnLoop();

        virtual bool LoadImg(const char* filename);
};

#endif
