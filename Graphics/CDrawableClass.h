/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CDRAWABLECLASS_H_
    #define _CDRAWABLECLASS_H_

#include "../Common/CBaiscProperties.h"

class CDrawableClass : public CBaiscProperties
{
    private:
        unsigned char                     _layerOrder;
    protected:
        bool                              _isShowed;
        float                             _alpha;
        float                             _red;
        float                             _green;
        float                             _blue;
    public:
        CDrawableClass();
        
        virtual unsigned char GetLayerOrder() const;
        virtual void SetLayerOrder(char order);
        virtual void SetLayerOrder(vector<string> args);

        virtual void OnRender(sf::RenderTarget* Surf_Dest)=0;
        virtual void OnLoop()=0;

        virtual CSimultaneousOfAction* CreateActionOfColorTo(size_t elapsed, float r, float g, float b, bool restore, bool pause);	  
        virtual CActionTo* CreateActionOfColorRedTo(size_t elapsed, float r, bool restore, bool pause);
        virtual CActionTo* CreateActionOfColorGreenTo(size_t elapsed, float g, bool restore, bool pause);
        virtual CActionTo* CreateActionOfColorBlueTo(size_t elapsed, float b, bool restore, bool pause);

        virtual CSimultaneousOfAction* CreateActionOfColorBy(size_t elapsed, float r, float g, float b, bool restore, bool pause);	  
        virtual CActionBy* CreateActionOfColorRedBy(size_t elapsed, float r, bool restore, bool pause);
        virtual CActionBy* CreateActionOfColorGreenBy(size_t elapsed, float g, bool restore, bool pause);
        virtual CActionBy* CreateActionOfColorBlueBy(size_t elapsed, float b, bool restore, bool pause);

        virtual CActionTo* CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore, bool pause);
        virtual CActionBy* CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore, bool pause);

        virtual bool OnLButtonUp(int mX, int mY){return false;}
        virtual bool OnLButtonDown(int mX, int mY){return false;}
        virtual bool OnRButtonUp(int mX, int mY){return false;}
        virtual bool OnRButtonDown(int mX, int mY){return false;}
        virtual bool OnMouseMove(int mX, int mY){return false;}

        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
};

#endif
