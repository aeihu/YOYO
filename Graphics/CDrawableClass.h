/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CDRAWABLECLASS_H_
    #define _CDRAWABLECLASS_H_

#include "../Common/CBaiscProperties.h"

class CDrawableClass : public CBaiscProperties
{
    private:
        unsigned char                     _layerOrder;
        //bool                              _isShowed;
        float                             _alpha;
        float                             _red;
        float                             _green;
        float                             _blue;
    protected:
    public:
        CDrawableClass();
        
        virtual bool IsShowed() const;
        virtual float GetAlpha() const;
        virtual float GetRed() const;
        virtual float GetGreen() const;
        virtual float GetBlue() const;

        virtual void SetAlpha(int alpha);
        virtual void SetRed(int r);
        virtual void SetGreen(int g);
        virtual void SetBlue(int b);
        virtual void SetColor(int r, int g, int b);

        virtual unsigned char GetLayerOrder() const;
        virtual void SetLayerOrder(char order);
        virtual void SetLayerOrder(vector<char> args);

        virtual void OnRender(sf::RenderTarget* Surf_Dest)=0;
        virtual void OnLoop()=0;

        virtual CSimultaneousOfAction* CreateActionOfColorTo(size_t elapsed, float r, float g, float b, bool restore);      
        virtual CActionTo* CreateActionOfColorRedTo(size_t elapsed, float r, bool restore);
        virtual CActionTo* CreateActionOfColorGreenTo(size_t elapsed, float g, bool restore);
        virtual CActionTo* CreateActionOfColorBlueTo(size_t elapsed, float b, bool restore);

        virtual CSimultaneousOfAction* CreateActionOfColorBy(size_t elapsed, float r, float g, float b, bool restore);      
        virtual CActionBy* CreateActionOfColorRedBy(size_t elapsed, float r, bool restore);
        virtual CActionBy* CreateActionOfColorGreenBy(size_t elapsed, float g, bool restore);
        virtual CActionBy* CreateActionOfColorBlueBy(size_t elapsed, float b, bool restore);

        virtual CActionTo* CreateActionOfAlphaTo(size_t elapsed, float alpha, bool restore);
        virtual CActionBy* CreateActionOfAlphaBy(size_t elapsed, float alpha, bool restore);

        /////////////////////////////////////////////////////////

        virtual void CreateActionOfColorToForSelf(size_t elapsed, float r, float g, float b, bool restore);
        virtual void CreateActionOfColorRedToForSelf(size_t elapsed, float r, bool restore);
        virtual void CreateActionOfColorGreenToForSelf(size_t elapsed, float g, bool restore);
        virtual void CreateActionOfColorBlueToForSelf(size_t elapsed, float b, bool restore);

        virtual void CreateActionOfColorByForSelf(size_t elapsed, float r, float g, float b, bool restore);
        virtual void CreateActionOfColorRedByForSelf(size_t elapsed, float r, bool restore);
        virtual void CreateActionOfColorGreenByForSelf(size_t elapsed, float g, bool restore);
        virtual void CreateActionOfColorBlueByForSelf(size_t elapsed, float b, bool restore);

        virtual void CreateActionOfAlphaToForSelf(size_t elapsed, float alpha, bool restore);
        virtual void CreateActionOfAlphaByForSelf(size_t elapsed, float alpha, bool restore);

        virtual bool OnLButtonUp(int mX, int mY){return false;}
        virtual bool OnLButtonDown(int mX, int mY){return false;}
        virtual bool OnRButtonUp(int mX, int mY){return false;}
        virtual bool OnRButtonDown(int mX, int mY){return false;}
        virtual bool OnMouseMove(int mX, int mY){return false;}

        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json);
};

#endif
