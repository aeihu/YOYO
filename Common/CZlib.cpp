/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

#include "CZlib.h"
#include <iostream>

using namespace std;

bool CZlib::SplitFileName(string filename, string symbol, string& s1, string& s2)
{
    s1.clear();
    s2.clear();
    if (filename.find(symbol)==string::npos)
        return false;

    s1.insert(0,filename,0,filename.find(symbol));
    s2.insert(0,filename,filename.find(symbol)+1, filename.length()-1);
    return true;
}

int CZlib::GetFileNamesInZip(std::string filename, list<string>& fileList)
{
    unzFile __file = NULL;
    unz_file_info __fileInfo;
    string __zip = "";
    string __dir = "";

    if (!SplitFileName(filename, "*", __zip, __dir)){
        cout << "CZlib::GetFileNamesInZip(): can't find split symbol." << endl;
        return -1;
    }

    __file = unzOpen(__zip.c_str());

    if (__file == NULL){
        cout << "CZlib::GetFileNamesInZip(): failed to open \"" << __zip << "\"" << endl;
        return -2;
    }

    if (unzGoToFirstFile(__file) == UNZ_OK){

        string __str; 
        do{
            char __name[256] = "";
            unzGetCurrentFileInfo(__file, &__fileInfo, __name, 256, NULL, 0, NULL, 0);
            __str = __name;

            if (__dir == ""){
                if (__str.find("/") == string::npos)
                    fileList.push_back(__zip + "*" + __name);
                else{
                    if (fileList.size() > 0)
                        break;
                }
            }
            else{
                if (__str[__str.length() - 1] != '/'){
                    if (__dir[__dir.length() - 1] != '/')
                        __dir += '/';

                    size_t __findPos = __str.find(__dir);
                    if (__findPos != string::npos && __findPos == 0){
                        if (__str.find_last_of("/") < __dir.length()){
                            fileList.push_back(__zip + "*" + __name);
                        }
                    }
                    else{
                        if (fileList.size() > 0)
                            break;
                    }
                }
            }
        } while (unzGoToNextFile(__file) == UNZ_OK);
    }

    unzClose(__file);

    return 0;
}

int CZlib::OpenFileInZip(string filename, char* &file, unsigned long& size)
{
    CloseFileInZip(file);
    size = 0;

    unzFile __file = NULL;
    unz_file_info __fileInfo;
    string __zip = "";
    string __fileName = "";

    if (!SplitFileName(filename, "*", __zip, __fileName)){
        cout << "CZlib::OpenZipFile(): can't find split symbol." << endl;
        return -1;
    }

    __file = unzOpen(__zip.c_str());
    if (__file == NULL){
        cout << "CZlib::OpenZipFile(): failed to open \"" << __zip << "\"" << endl;
        return -2;
    }

    unzLocateFile(__file,__fileName.c_str(),0);
    
    int __err = unzGetCurrentFileInfo(__file, &__fileInfo, NULL, 0, NULL, 0, NULL, 0);
    if (__err != UNZ_OK){
        cout << "CZlib::OpenZipFile(): can't find file \"" << __fileName << "\"" << endl;
        unzClose(__file);
        return -3;
    }
        
    file = new char[__fileInfo.uncompressed_size];
    size = __fileInfo.uncompressed_size;
    unzOpenCurrentFile(__file);
    unzReadCurrentFile(__file, file, __fileInfo.uncompressed_size);
    unzClose(__file);

    return 0;
}

void CZlib::CloseFileInZip(char* file)
{
    if (file != NULL){
        delete [] file;
        file = NULL;
    }
}
