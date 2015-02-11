#include "CObjectControl.h"
#include "../Text/CFont.h"

bool CObjectControl::IsExists(string name)
{
    return _objectList.count(name) > 0;
}

bool CObjectControl::AddObject(string name, string objTypeName, string filename)
{
    CObject* __obj = NULL;

    if (_objectList.count(objTypeName+":"+name) > 0){
        cout << "CObjectControl::AddObject(): " 
            << objTypeName << " \""<< name << "\" has existed." <<endl;
        delete __obj;
        return false;
    }

    if (objTypeName == "Font") __obj = CFont::Create(filename.c_str());

    if (__obj != NULL){
        _objectList[objTypeName+":"+name] = __obj;
        return true;
    }
    else
        cout << "CResourceControl::AddDrawableObject(): failed to create " 
            << objTypeName << "." <<endl;

    return false;
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