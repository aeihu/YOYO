#include "CControlBaseClass.h"

bool CControlBaseClass::IsExists(string name)
{
    return _objectList.count(name) > 0;
}

bool CControlBaseClass::AddObject(string name, CObject* obj)
{
    if (obj == NULL)
        return false;

    if (_objectList.count(name) > 0){
        delete obj;
        return false;
    }

    _objectList[name] = obj;
    return true;
}

CObject* CControlBaseClass::GetObject(string name)
{
    if (_objectList.count(name) < 1)
        return NULL;

    return _objectList[name];
}

bool CControlBaseClass::DelObject(string name)
{
    if (_objectList.count(name) < 1)
        return false;

    if (_objectList[name] != NULL)
        delete _objectList[name];

    _objectList.erase(name);

    return true;
}   
        
void CControlBaseClass::OnCleanup()
{
    std::map<std::string, CObject*>::iterator it;
    for ( it=_objectList.begin(); it !=_objectList.end(); it++ ){
        if ((*it).second != NULL)
            delete (*it).second;
    }

    _objectList.clear();
}