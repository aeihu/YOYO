/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _CDRAWABLEOBJECTCONTROL_H_
    #define _CDRAWABLEOBJECTCONTROL_H_

#include "../Graphics/CDrawableClass.h"
#include "../Common/CEventFunctions.h"

class CDrawableObjectControl : public CEventFunctions
{
    private:
        friend void CDrawableClass::SetLayerOrder(char order);

        struct CCmp{
            bool operator()(pair<string,CDrawableClass*> obj1, pair<string,CDrawableClass*> obj2)
            {
                return obj1.second->GetLayerOrder() < obj2.second->GetLayerOrder();
            }
        }                                       _sort;
        
        bool                                    _isNeedSort;

        vector<pair<string, CDrawableClass*> >  _drawableObjectList;

    protected:
    public:
        inline CDrawableObjectControl() {_isNeedSort = false;}
        bool IsExists(string name);
        
        bool AddDrawableObject(string name, string objTypeName, string filename);
        bool ResetDrawableObject(string name, string objTypeName);
        bool DelDrawableObject(string name);
        CDrawableClass* GetDrawableObject(string name);
        void CleanActionList();

        void OnLoop();
        void OnRender(sf::RenderWindow* Surf_Dest);
        void OnCleanup();
        void OnSaveData(Object& json) const;
        void OnLoadData(Object json);

        virtual bool OnKeyDown(sf::Event::KeyEvent key);
        virtual bool OnKeyUp(sf::Event::KeyEvent key);
        virtual bool OnMouseMove(int mX, int mY);
        virtual bool OnMouseWheel(int delta);
        virtual bool OnLButtonDown(int mX, int mY);
        virtual bool OnLButtonUp(int mX, int mY);
        virtual bool OnRButtonDown(int mX, int mY);
        virtual bool OnRButtonUp(int mX, int mY);
        virtual bool OnMButtonDown(int mX, int mY);
        virtual bool OnMButtonUp(int mX, int mY);
};

#endif
