/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/
#include "Cio.h"

#define CHARACTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_,."
#define NUMBER "0123456789.-"

void Cio::ClearFileInMem(char* &file)
{
	if (file != NULL){
		delete[] file;
		file = NULL;
	}
}

bool Cio::LoadFileToMem(string filename, char* &file, unsigned long& size)
{
	ClearFileInMem(file);

	if (filename.find("*")!=string::npos){
		if (CZlib::OpenFileInZip(filename, file, size) == 0){
			return true;
		}
		return false;
	}
	else{
        filebuf* __pBuf;  
        ifstream __fileStr;    

        __fileStr.open (filename.c_str(), ios::binary); 
        __pBuf=__fileStr.rdbuf();

        size=__pBuf->pubseekoff (0,ios::end,ios::in); 
        __pBuf->pubseekpos (0,ios::in);    

        file=new char[size]; 
        __pBuf->sgetn (file,size); 
        __fileStr.close();  
        return true;
	}
}

string Cio::LoadTxtFile(string filename)
{
	if (filename.find("*")!=string::npos){
		char* __file = NULL;
		unsigned long __size = 0;
		CZlib::OpenFileInZip(filename, __file, __size);
		string __result = __file;
		CZlib::CloseFileInZip(__file);
		return __result;
	}
	else{
		string __result = "";
		ifstream __is (filename.c_str(), std::ifstream::binary);
		if (__is) {
			// get length of file:
			__is.seekg (0, __is.end);
			int __length = __is.tellg();
			__is.seekg (0, __is.beg);

			char * __buffer = new char [__length];

			//cout << "Reading " << __length << " characters... ";
			// read data as a block:
			__is.read (__buffer,__length);

			//if (is)
			//  std::cout << "all characters read successfully.";
			//else
			if (__is)
				__result = __buffer;
			else
				cout << "Cio::LoadTxtFile(): only " << __is.gcount() << " could be read";

			__is.close();

			// ...buffer contains the entire file...

			delete[] __buffer;
		}
		return __result;
	}
}

list<string> Cio::LoadTxtFile(string filename, string symbol, bool isDelete)
{
	unsigned int _offset = 1;
	if (isDelete) _offset = 0;

	string __data = LoadTxtFile(filename);

	list<string> __result;
	
	while(!__data.empty()){
		string __expression = "";	
		if (__data.find_first_of(symbol) != string::npos){
			__expression.insert(0, __data, 0, __data.find_first_of(symbol)+_offset);
			__data.erase(0,__data.find_first_of(symbol)+1);
		}
		else{
			__expression = __data;
			__data = "";
		}

		if (!__expression.empty())
			__result.push_back(__expression);
	}

	return __result;
}

bool Cio::IsOneWord(std::string &str, std::string valid_characters)
{
	if (str.find_first_of(valid_characters) == string::npos)
		return false;

	string __tmp = "";
	__tmp.insert(0, str, str.find_first_of(valid_characters), str.find_last_of(valid_characters)-str.find_first_of(valid_characters)+1);

	if(__tmp.find_first_not_of(valid_characters) != string::npos){
		str = "";
		return false;
	}
	else{
		str = __tmp;
		return true;
	}
}

//==============_(:3J Z)_===================
bool Cio::IsNested(std::string &str, char first_symbol, char last_symbol)
{
	if (str.find_first_of(first_symbol)==string::npos ||
		str.find_last_of(last_symbol)==string::npos)
		return false;

	if (str.find_first_of(first_symbol) >= str.find_last_of(last_symbol))
		return false;

	string __tmp = "";
	__tmp.insert(0, str, str.find_first_of(first_symbol)+1, str.find_last_of(last_symbol)-str.find_first_of(first_symbol)-1);
	str = __tmp;
	return true;
}

list<string> Cio::SplitString(string str, string symbol)
{
    list<string> __result;
    while (str.find(symbol) != string::npos){
	    string __tmp = "";
	    __tmp.insert (0,str,0,str.find(symbol));
        if (IsNested(__tmp, '"', '"'))
            __result.push_back(__tmp);

		str.erase(0,str.find(symbol)+1);
    }

    if (IsNested(str, '"', '"'))
        __result.push_back(str);

    return __result;
}

bool Cio::AnalyticExpression(string str, string symbol, string &name, string &value)
{
    if (str.empty() || str.find(symbol) == string::npos){
        cout << "Cio::AnalyticExpression(): \"" << str << "\" can't find symbol \"" << symbol << "\"." << endl;
		return false;
    }

	name = "";
	name.insert (0,str,0,str.find(symbol));

	if (!IsOneWord(name, CHARACTERS)){
        cout << "Cio::AnalyticExpression(): name of argument \"" << name << "\" is wrong format." << endl;
        return false;
    }

	value = "";
	value.insert (0,str,str.find(symbol) + 1, str.length() - 1);

	if (!IsNested(value, '"', '"'))
        if (!IsOneWord(value, NUMBER)){
            cout << "Cio::AnalyticExpression(): value of argument \"" << name << "\" is wrong format." << endl;
			return false;
        }

	return true;
}

bool Cio::AnalyticExpression(string str, string &name, string &value)
{
	return AnalyticExpression(str, "=", name, value);
}
