#include "CControlOfImageBaseClass.h"
#include <algorithm>

CControlOfImageBaseClass  CControlOfImageBaseClass::_ResourceManager;

bool CControlOfImageBaseClass::AddDrawableObject(string name, CImageBaseClass* obj)
{
    if (obj == NULL)
        return false;

    if (_drawableObjectList.count(name) > 0){
        delete obj;
        return false;
    }

    _drawableObjectList[name] = obj;
    return true;
}

bool CControlOfImageBaseClass::DelDrawableObject(string name)
{
    if (_drawableObjectList.count(name) < 1)
        return false;

    if (_drawableObjectList[name] != NULL)
        delete _drawableObjectList[name];

    _drawableObjectList.erase(name);

    return true;
}

CImageBaseClass* CControlOfImageBaseClass::GetDrawableObject(string name)
{
    if (_drawableObjectList.count(name) < 1)
        return NULL;

    return _drawableObjectList[name];
}

bool CControlOfImageBaseClass::SetImageVisibility(std::string name, int alpha, float incr, bool pause)
{
    if (incr == 0)
        incr = static_cast<float>(CCommon::_Common.INCREMENT);

    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));
    if (__obj != NULL){
        __obj->Insert(0,
            alpha, pause,
            &__obj->_Alpha,
            incr);

        return true;
    }

    return false;
}

bool CControlOfImageBaseClass::Move(string name, float x, float y, unsigned int elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return false;

    unsigned int __i = elapsed / _interval == 0 ? 1 : elapsed / _interval;
    if (x - __obj->_Coordinate.x < -0.001f || x - __obj->_Coordinate.x > 0.001f){
        __obj->Insert(0, x, pause, &__obj->_Coordinate.x, abs((x - __obj->_Coordinate.x) / __i));
    }

    if (y - __obj->_Coordinate.y < -0.001f || y - __obj->_Coordinate.y > 0.001f){
        __obj->Insert(0, y, pause, &__obj->_Coordinate.y, abs((y - __obj->_Coordinate.y) / __i));
    }
    return true;
}
        
char CControlOfImageBaseClass::Show(string name, float x, float y, char type, unsigned int elapsed, bool pause, int alpha)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return -1;

    if (__obj->GetVisible())
        return -2;

    float __i = elapsed == 0 ? 1 : elapsed / _interval;
    float __x = x;
    float __y = y;

    switch (type)
    {
        case 'u':
            __y += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'r':
            __x -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'd':
            __y -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'l':
            __x += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
    }

    __obj->_Coordinate.x = __x;
    __obj->_Coordinate.y = __y;
    if (Move(name, x, y, elapsed, pause)){
        SetImageVisibility(name, alpha, 255/__i, pause);
        return 0;
    }

    return -1;
}
        
char CControlOfImageBaseClass::Hide(string name, char type, unsigned int elapsed, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetDrawableObject(name));

    if (__obj == NULL)
        return -1;

    if (!__obj->GetVisible())
        return -2;

    float __x = __obj->_Coordinate.x;
    float __y = __obj->_Coordinate.y;
    float __i = elapsed == 0 ? 1 : elapsed / _interval;

    switch (type)
    {
        case 'u':
            __y -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'r':
            __x += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'd':
            __y += CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
        case 'l':
            __x -= CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
        break;
    }

    if (Move(name, __x, __y, elapsed, pause)){
        SetImageVisibility(name, 0, __obj->_Alpha / __i, pause);
        return 0;
    }

    return -1;
}

void CControlOfImageBaseClass::OnLoop(bool &pause)
{
    map<string, CImageBaseClass*>::iterator it;
    for ( it=_drawableObjectList.begin(); it !=_drawableObjectList.end(); it++ )
    {
        if((*it).second->OnLoop()) 
            pause=true;
    }
}

void CControlOfImageBaseClass::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (map<string, CImageBaseClass*>::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++)
        (*it).second->OnRender(Surf_Dest);
}

void CControlOfImageBaseClass::OnCleanup()
{
    for (map<string, CImageBaseClass*>::iterator it=_drawableObjectList.begin(); 
        it!=_drawableObjectList.end(); it++){
            delete (*it).second;
    }

    _drawableObjectList.clear();
}

bool CControlOfImageBaseClass::IsExists(string name)
{
    return _drawableObjectList.count(name) > 0 || _objectList.count(name) > 0;
}