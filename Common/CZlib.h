/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CZLIB_H_
    #define _CZLIB_H_
#include "unzip.h"
#include <string>

class CZlib
{
    private:
    protected:
    public:
        static bool SplitFileName(std::string filename, std::string symbol, std::string& s1, std::string& s2);
        static int OpenFileInZip(std::string filename, char* &file, unsigned long& size);
        static void CloseFileInZip(char* file);
};

#endif
