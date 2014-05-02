#include "CControlOfImageBaseClass.h"

bool CControlOfImageBaseClass::SetImageVisibility(std::string name, int alpha, int incr, bool pause)
{
    if (incr == 0)
        incr = CCommon::_Common.INCREMENT;

    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetObject(name));
    if (__obj != NULL){
        __obj->Insert(0,
            alpha, pause,
            &__obj->_Alpha,
            incr);

        return true;
    }

    return false;
}

bool CControlOfImageBaseClass::Move(string name, float x, float y, float incr, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetObject(name));

    if (__obj == NULL)
        return false;

    if (incr > -0.001f && incr < 0.001f)
        incr = (float)CCommon::_Common.INCREMENT;

    if (abs(__obj->_Coordinate.x-x) 
        > abs(__obj->_Coordinate.y-y)){
        float ratio = 1;
        if (abs(__obj->_Coordinate.y-y) != 0){
            ratio = abs(__obj->_Coordinate.y-y) / abs(__obj->_Coordinate.x-x);
            __obj->Insert(0, y, pause, &__obj->_Coordinate.y, incr*ratio);
        }
        
        __obj->Insert(0, x, pause, &__obj->_Coordinate.x, incr);
    }
    else if (abs(__obj->_Coordinate.x-x) 
        < abs(__obj->_Coordinate.y-y)){
        float ratio = 1;
        if (abs(__obj->_Coordinate.x-x) != 0){
            ratio = abs(__obj->_Coordinate.x-x) / abs(__obj->_Coordinate.y-y);
            __obj->Insert(0, x, pause, &__obj->_Coordinate.x, incr*ratio);
        }

        __obj->Insert(0, y, pause, &__obj->_Coordinate.y, incr);
    }
    else{
        __obj->Insert(0, x, pause, &__obj->_Coordinate.x, incr);
        __obj->Insert(0, y, pause, &__obj->_Coordinate.y, incr);
    }
    return true;
}
        
char CControlOfImageBaseClass::Show(string name, float x, float y, char type, float incr, bool pause, int alpha)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetObject(name));

    if (__obj == NULL)
        return -1;

    if (__obj->GetVisible())
        return -2;

    if (incr > -0.001f && incr < 0.001f)
        incr = (float)CCommon::_Common.INCREMENT;

    float buf = CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    float __x = x;
    float __y = y;
    int __inc = (int)incr;

    if (type != 'c'){
        __inc = ((int)buf)/(__inc == 0 ? 1:__inc);
        __inc = __inc<=0?255:255/__inc;
    }

    switch (type)
    {
        case 'u':
            __y += buf;
        break;
        case 'r':
            __x -= buf;
        break;
        case 'd':
            __y -= buf;
        break;
        case 'l':
            __x += buf;
        break;
        default:
            SetImageVisibility(name, alpha, __inc, pause);
            __obj->_Coordinate.x = __x;
            __obj->_Coordinate.y = __y;
            return 0;
        break;
    }

    __obj->_Coordinate.x = __x;
    __obj->_Coordinate.y = __y;
    if (Move(name, x, y, incr, pause)){
        SetImageVisibility(name, alpha, __inc, pause);
        return 0;
    }

    return -1;
}
        
char CControlOfImageBaseClass::Hide(string name, char type, float incr, bool pause)
{
    CImageBaseClass* __obj = static_cast<CImageBaseClass*>(GetObject(name));

    if (__obj == NULL)
        return -1;

    if (!__obj->GetVisible())
        return -2;

    if (incr > -0.001f && incr < 0.001f)
        incr = (float)CCommon::_Common.INCREMENT;

    float buf = CCommon::_Common.CHARACTER_LAYER_MOVE_BUFFER;
    float __x = __obj->_Coordinate.x;
    float __y = __obj->_Coordinate.y;
    int __inc = (int)incr;
    __inc = ((int)buf)/(__inc == 0 ? 1:__inc);//???
    __inc = __inc<=0?255:255/__inc;

    switch (type)
    {
        case 'u':
            __y -= buf;
        break;
        case 'r':
            __x += buf;
        break;
        case 'd':
            __y += buf;
        break;
        case 'l':
            __x -= buf;
        break;
        default:
            SetImageVisibility(name, 0, __inc, pause);
            return 0;
        break;
    }

    if (Move(name, __x, __y, incr, pause)){
        int inc = 255/(((int)buf)/((int)incr));
        SetImageVisibility(name, 0, inc<=0?1:inc, pause);
        return 0;
    }

    return -1;
}
