#include "CControlBaseClass.h"

bool CControlBaseClass::IsExists(string name)
{
    return GetObject(name) == NULL ? false : true;
}