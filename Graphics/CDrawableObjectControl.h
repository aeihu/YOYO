/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CDRAWABLEOBJECTCONTROL_H_
    #define _CDRAWABLEOBJECTCONTROL_H_

#include "../Graphics/CImageBaseClass.h"

class CDrawableObjectControl
{
    private:
        struct CCmp{
            bool operator()(pair<string,CImageBaseClass*> obj1, pair<string,CImageBaseClass*> obj2)
            {
                return obj1.second->GetLayerOrder() < obj2.second->GetLayerOrder();
            }
        }                                       _sort;
        
        bool                                    _isNeedSort;

        vector<pair<string, CImageBaseClass*> > _drawableObjectList;

        inline CDrawableObjectControl() {_isNeedSort = false;}
    protected:
    public:
        bool IsExists(string name);
        bool SetImageVisibility(string name, int alpha, size_t elapsed, bool pause);
        bool SetLayerOrder(string name, char order);
        
        bool AddDrawableObject(string objTypeName, string filename);
        bool DelDrawableObject(string name);
        CImageBaseClass* GetDrawableObject(string name);
        void SetDrawableObjectLayerOrder(string name, char layer);

        bool Move(string name, float x, float y, size_t elapsed, bool pause);
        bool MoveX(string name, float x, size_t elapsed, bool pause);
        bool MoveY(string name, float y, size_t elapsed, bool pause);
        char Show(string name, float x, float y, char type, size_t elapsed, bool pause, int alpha=255);
        char Hide(string name, char type, size_t elapsed, bool pause);
};

#endif
