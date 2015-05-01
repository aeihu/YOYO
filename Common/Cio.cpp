/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/
#include "Cio.h"

#define CHARACTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_,."
#define NUMBER "0123456789.-"
const char TRIM_CH[] = {0x09,0x20};

string& Cio::Trim(string& str)
{
    str.erase(0,str.find_first_not_of(TRIM_CH));  
    str.erase(str.find_last_not_of(TRIM_CH) + 1); 
    return str;
}

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

size_t Cio::CounterOfString(string str, string symbol, size_t pos)
{
    size_t __pos = str.find_first_of(symbol, pos);
    if (__pos == string::npos)
        return 0;
    else
        return 1 + CounterOfString(str, symbol, __pos+1);
}
        
string Cio::ClearBom(string &str)
{
    if (str.length() > 3)
        if ((unsigned char)str[0] == 0xEF && 
            (unsigned char)str[1] == 0xBB && 
            (unsigned char)str[2] == 0xBF)
            str = str.erase(0,3);

    return str;
}

string Cio::LoadTxtFile(string filename)
{
	if (filename.find("*")!=string::npos){
		char* __file = NULL;
		unsigned long __size = 0;
		CZlib::OpenFileInZip(filename, __file, __size);

        if (__file){
		    string __result = __file;
            ClearBom(__result);
		    CZlib::CloseFileInZip(__file);
		    return __result;
        }
        else{
            cout << "Cio::LoadTxtFile(): can't open file \'" << filename << "\'." << endl;
            return "";
        }
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
            
            //char BOM[3] = {0xEF,0xBB,0xBF};
			if (__is){
				__result = __buffer;
                ClearBom(__result);
            }
			else
				cout << "Cio::LoadTxtFile(): only " << __is.gcount() << " could be read";

			__is.close();

			// ...buffer contains the entire file...

			delete[] __buffer;
		}
		return __result;
	}
}

string Cio::DeleteComment(string str, bool isDelete)
{
    size_t __pos = str.find("//");
    if (__pos != string::npos){
        string __str = str.substr(0, __pos);
        for (int i=0; i<__str.length(); i++){
            if (__str[i] == '"')
                isDelete = !isDelete;
        }

        if (isDelete)
            return __str;
        else
            return  str.substr(0, __pos+2) + DeleteComment(str.substr(__pos+2), isDelete);
    }

    return str;
}

list<string> Cio::LoadTxtFile(string filename, string symbol)
{
	string __data = LoadTxtFile(filename);

    list<string> __result = SplitString(__data, "\n\r");
        
    for (list<string>::iterator it=__result.begin();it!=__result.end(); it++){
        (*it) = DeleteComment(*it);
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
    str = Trim(str);

    size_t first_symbol_pos = str.find_first_of(first_symbol);
    size_t last_symbol_pos = str.find_last_of(last_symbol);

	if (first_symbol_pos==string::npos || last_symbol_pos==string::npos)
        return false;

	string __tmp = "";
	__tmp.insert(0, str, first_symbol_pos+1, last_symbol_pos-first_symbol_pos-1);
	str = __tmp;

	return true;
}

list<string> Cio::SplitString(string str, string symbol)
{
    list<string> __result;
    while (str.find_first_of(symbol) != string::npos){
	    string __tmp = "";
	    __tmp.insert (0,str,0,str.find_first_of(symbol));
        __tmp = Trim(__tmp);

        if (!__tmp.empty())
            __result.push_back(__tmp);

		str.erase(0, str.find_first_of(symbol)+1);
    }

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
