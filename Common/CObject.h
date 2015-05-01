/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#ifndef _COBJECT_H_
    #define _COBJECT_H_

#include <string>
#include <fstream>
#include <jsonxx.h>

using namespace std;
using namespace jsonxx;

class CObject
{
    private:
        string      _path;
        string      _className;
    protected:
        void SetClassName(string name);
        void SetPath(string path);
    public:
        CObject();

        string GetClassName() const;
        string GetPath() const;
        virtual void OnSaveData(Object& json) const;
        virtual void OnLoadData(Object json){}
};

#endif
