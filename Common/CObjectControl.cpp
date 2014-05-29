#include "CObjectControl.h"

bool CObjectControl::IsExists(string name)
{
    return _objectList.count(name) > 0;
}

bool CObjectControl::AddObject(string name, CObject* obj)
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

CObject* CObjectControl::GetObject(string name)
{
    if (_objectList.count(name) < 1)
        return NULL;

    return _objectList[name];
}

bool CObjectControl::DelObject(string name)
{
    if (_objectList.count(name) < 1)
        return false;

    if (_objectList[name] != NULL)
        delete _objectList[name];

    _objectList.erase(name);

    return true;
}   
        
void CObjectControl::OnCleanup()
{
    std::map<std::string, CObject*>::iterator it;
    for ( it=_objectList.begin(); it !=_objectList.end(); it++ ){
        if ((*it).second != NULL)
            delete (*it).second;
    }

    _objectList.clear();
}