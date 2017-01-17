/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CImageBaseClass.h"

CImageBaseClass::CImageBaseClass()
{
    _baseNode = NULL;
    _flag = FLAG_ALPHA | FLAG_COLOR;// alpha grb position orgin
    _flipX = _flipY = false;
}

CImageBaseClass::~CImageBaseClass()
{}
         
void CImageBaseClass::FlipX()
{
    _flipX = !_flipX;
}
        
void CImageBaseClass::FlipY()
{
    _flipY = !_flipY;
}

void CImageBaseClass::OnSaveData(Object& json) const
{
    CDrawableClass::OnSaveData(json);
    json << "flip_x" << _flipX;
    json << "flip_y" << _flipY;
    json << "flag" << _flag;


    //Object __children;
    //for (list<CImageBaseClass*>::const_iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
    //    (*it)->OnSaveData(__children);
    //json << "children" << __children;
}

void CImageBaseClass::OnLoadData(Object json)
{
    CDrawableClass::OnLoadData(json);

    if (_flipX != json.get<Boolean>("flip_x"))
        FlipX();

    if (_flipY != json.get<Boolean>("flip_y"))
        FlipY();

    _flag = json.get<Number>("flag");

    //Object __children = json.get<Object>("children");
    //for (list<CImageBaseClass*>::const_iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
    //    (*it)->OnLoadData(__children);
}

void CImageBaseClass::SetFlag(char flag)
{
    _flag = flag;
}

char CImageBaseClass::GetFlag() const
{
    return _flag;
}

bool CImageBaseClass::SetBaseNode(CImageBaseClass* baseNode)
{
    if (baseNode){
        _baseNode = baseNode;
        return true;
    }

    return false;
}

bool CImageBaseClass::AddChildNode(CImageBaseClass* child)
{
    if (child){
        child->SetBaseNode(this);
        _childrenList.push_back(child);
        return true;
    }

    return false;
}

bool CImageBaseClass::RemoveChildNode(CImageBaseClass* child)
{
    bool __result = false;
    if (child)
        for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end();){
            if ((*it) == child){
                it = _childrenList.erase(it);
                __result = true;
            }
            else
                it++;
        }

    return __result;
}

void CImageBaseClass::CleanActionList()
{
    for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
        (*it)->CleanActionList();
    
    CBaiscProperties::CleanActionList();
}

void CImageBaseClass::OnCleanup()
{
    for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++){
        (*it)->CleanActionList();
        (*it)->OnCleanup();
    }

    CBaiscProperties::OnCleanup();
}

void CImageBaseClass::Loop(sf::Transformable* obj)
{
    if (obj)
        if (IsShowed()){
            if (GetPosition() != obj->getPosition())
                obj->setPosition(GetPosition());

            if (GetOrigin() != obj->getOrigin())
                obj->setOrigin(GetOrigin());

            if (GetScale() != obj->getScale())
                obj->setScale(GetScale());

            if (GetRotation() != obj->getRotation())
                obj->setRotation(GetRotation());

            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++){
                if ((*it)->GetFlag() & FLAG_ALPHA)
                    (*it)->SetAlpha(GetAlpha());

                if ((*it)->GetFlag() & FLAG_COLOR)
                    (*it)->SetColor(GetRed(), GetGreen(), GetBlue());

                (*it)->OnLoop();
            }
        }
}


bool CImageBaseClass::OnKeyDown(sf::Event::KeyEvent key)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnKeyDown(key))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnKeyUp(sf::Event::KeyEvent key)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnKeyUp(key))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnMouseMove(int mX, int mY)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnMouseMove(mX, mY))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnMouseWheel(int delta)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnMouseWheel(delta))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnLButtonDown(int mX, int mY)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnLButtonDown(mX, mY))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnLButtonUp(int mX, int mY)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnLButtonUp(mX, mY))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnRButtonDown(int mX, int mY)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnRButtonDown(mX, mY))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnRButtonUp(int mX, int mY)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnRButtonUp(mX, mY))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnMButtonDown(int mX, int mY)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnMButtonDown(mX, mY))
                return true;
        }
    }

    return false;
}

bool CImageBaseClass::OnMButtonUp(int mX, int mY)
{
    if (IsShowed()){
        if (_actionList.GetSize() < 1){
            for (list<CImageBaseClass*>::iterator it = _childrenList.begin(); it != _childrenList.end(); it++)
            if ((*it)->OnMButtonUp(mX, mY))
                return true;
        }
    }

    return false;
}