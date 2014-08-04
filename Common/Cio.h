/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CIO_H_
    #define _CIO_H_

#include <string>
#include <fstream> 
#include <iostream> 
#include <sstream> 
#include <list> 
#include "CZlib.h"

using namespace std;

class Cio
{
    public:
        static bool IsOneWord(string &str, string valid_characters);
        static bool IsNested(string &str, char first_symbol, char last_symbol);
        static size_t CounterOfString(string str, string symbol, size_t pos=0);
        static string DeleteComment(string str, bool isDelete=true);
        static string& Trim(string& str);

        static bool LoadFileToMem(string filename, char* &file, unsigned long& size);
        static void ClearFileInMem(char* &file);

        static string LoadTxtFile(string filename);
        static list<string> LoadTxtFile(string filename, string symbol, bool isDelete=true);
        static bool AnalyticExpression(string str, string &name, string &value);
        static bool AnalyticExpression(string str, string symbol, string &name, string &value);
        static list<string> SplitString(string str, string symbol);
};

#endif
