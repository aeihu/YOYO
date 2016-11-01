/*
* Copyright (C) 2012-2015, <Aeihu.z, aeihu.z@gmail.com>.
*
* YOYO is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 3(GPLv3) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CSurface.h"
#include <iostream>

map<string, pair<sf::Texture, list<sf::Texture*>>> CSurface::_textureList;

bool CSurface::GetTextureFromTextureList(string file, sf::Texture* &texture)
{
    if (_textureList.count(file) > 0){
        texture = &_textureList[file].first;
        _textureList[file].second.push_back(texture);
        return true;
    }
    else{
        sf::Texture __texture;
        if (OnLoad(file, __texture)){
            __texture.setSmooth(true);
            _textureList[file] = pair<sf::Texture, list<sf::Texture*>>(__texture, list<sf::Texture*>());

            texture = &_textureList[file].first;
            _textureList[file].second.push_back(texture);
            return true;
        }
    }
    return false;
}

void CSurface::GCForTextureList()
{
    for (map<string, pair<sf::Texture, list<sf::Texture*>>>::iterator it = _textureList.begin(); it != _textureList.end(); ){
        for (list<sf::Texture*>::iterator itList = it->second.second.begin(); itList != it->second.second.end(); ){
            if ((*itList) == NULL){
                itList = it->second.second.erase(itList);
            }
            else
                itList++;
        }

        if (it->second.second.size() < 1){
            it = _textureList.erase(it);
        }
        else
            it++;
    }
}

bool CSurface::OnLoad(string file, sf::Image &img)
{
    if (file.find("*") == string::npos){
        if (!img.loadFromFile(file)){
            cout << "CSurface::OnLoad(): failed to load '" << file << "'" << endl;
            return false;
        }
        else
            return true;
    }
    else {
        char* __image = NULL;
        unsigned long __size = 0;
        CZlib::OpenFileInZip(file, __image, __size);

        if (__image != NULL){
            if (img.loadFromMemory(__image, __size)){
                CZlib::CloseFileInZip(__image);
                return true;
            }
            else{
                CZlib::CloseFileInZip(__image);
                cout << "CSurface::OnLoad(): failed to load '" << file << "'" << endl;
                return false;
            }
        }
        else{
            CZlib::CloseFileInZip(__image);
            cout << "CSurface::OnLoad(): failed to load '" << file << "'" << endl;    
            return false;
        }
    }
}

bool CSurface::OnLoad(string file,  sf::Texture &img) {
    if (file.find("*") == string::npos){
        if (!img.loadFromFile(file)){
            cout << "CSurface::OnLoad(): failed to load '" << file << "'" << endl;
            return false;
        }
        else
            return true;
    }
    else {
        char* __image = NULL;
        unsigned long __size = 0;
        CZlib::OpenFileInZip(file, __image, __size);

        if (__image != NULL){
            if (img.loadFromMemory(__image, __size)){
                CZlib::CloseFileInZip(__image);
                return true;
            }
            else{
                CZlib::CloseFileInZip(__image);
                cout << "CSurface::OnLoad(): failed to load '" << file << "'" << endl;
                return false;
            }
        }
        else{
            CZlib::CloseFileInZip(__image);
            cout << "CSurface::OnLoad(): failed to load '" << file << "'" << endl;    
            return false;
        }
    }
}

bool CSurface::OnDraw(sf::Image* surf_Dest, sf::Image* surf_Src)
{
    if(surf_Dest == NULL || surf_Src == NULL) {
        return false;
    }

    surf_Dest->copy(*surf_Src, 0, 0, sf::IntRect(0, 0, surf_Src->getSize().x,  surf_Src->getSize().y), true);
    return true;
}

//==============================================================================
bool CSurface::OnDraw(sf::Image* surf_Dest, sf::Image* surf_Src, int X, int Y)
{
    if(surf_Dest == NULL || surf_Src == NULL) {
        return false;
    }

    surf_Dest->copy(*surf_Src, X, Y, sf::IntRect(0, 0, surf_Src->getSize().x,  surf_Src->getSize().y), true);
    return true;
}

//==============================================================================
bool CSurface::OnDraw(sf::Image* surf_Dest, sf::Image* surf_Src, size_t X, size_t Y, int X2, int Y2, int W, int H) {
    if(surf_Dest == NULL || surf_Src == NULL) {
        return false;
    }

    surf_Dest->copy(*surf_Src, X, Y, sf::IntRect(X2, Y2, X2+W, Y2+H), true);
    return true;
}

//==============================================================================
bool CSurface::Transparent(sf::Image* surf_Dest, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A) {
    if(surf_Dest == NULL) {
        return false;
    }

    return true;
}

void CSurface::FreeSurface(sf::Image* surf_Dest)
{
    if (surf_Dest != NULL){
        delete surf_Dest;
        surf_Dest = NULL;
    }
}
