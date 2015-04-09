/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSCREENEFFECT_H_
    #define _CSCREENEFFECT_H_

#include "../Graphics/CDrawableClass.h"
#include "../Action/CSimultaneousOfAction.h"
#include "../Action/CSequenceOfAction.h"
#include "../Action/CDeplayOfAction.h"
#include "../Action/CClassFuncOfAction.h"

class CScreenEffect : public CDrawableClass
{
    private:
        friend static CScreenEffect* CScreenEffect::Create(size_t num, float width, float height);

        class PData{
            public:
                float   _x;
                float   _y;
                float   _alpha;
                
                PData();
        };

        vector<PData>           _vertexData;
        sf::VertexArray         _vertexArray;
        CSimultaneousOfAction*  _act;
        
        void SetShow();
        void SetHide();
    public:
        static CScreenEffect* Create(size_t num, float width, float height);

        bool GetVisible() const;
        void OnLoop();
        void OnRender(sf::RenderTarget* Surf_Dest);
        void OnSaveData(Object& json) const;
        void OnLoadData(Object json);

        void SetColor(vector<string> args);

        CSimultaneousOfAction* CreateActionShowOrHide(size_t elapsed, bool isShow, bool pause);
        CSimultaneousOfAction* CreateActionGradient(size_t elapsed, bool isShow, bool L2R, bool pause);
        CSimultaneousOfAction* CreateActionLouver(size_t elapsed, bool isShow, bool L2R, bool slide, bool pause);
};

#endif