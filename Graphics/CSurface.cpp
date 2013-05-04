/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CSurface.h"
#include <iostream>

using namespace std;

bool CSurface::OnLoad(string File, sf::Image &Img) {
    if (File.find("*") == string::npos){
        if (!Img.LoadFromFile(File)){
            cout << "CSurface::OnLoad(): failed to load '" << File << "'" << endl;
            return false;
        }
        else
            return true;
    }
    else {
        char* __image = NULL;
        unsigned long __size = 0;
        CZlib::OpenFileInZip(File, __image, __size);

        if (__image != NULL){
            if (Img.LoadFromMemory(__image, __size)){
                CZlib::CloseFileInZip(__image);
                return true;
            }
            else{
                CZlib::CloseFileInZip(__image);
                cout << "CSurface::OnLoad(): failed to load '" << File << "'" << endl;
                return false;
            }
        }
        else{
            cout << "CSurface::OnLoad(): failed to load '" << File << "'" << endl;    
            return false;
        }
    }
}

//==============================================================================
sf::Image* CSurface::OnCreate(unsigned int W, unsigned int H, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A)
{
    sf::Image* result = new sf::Image();
    sf::Color color(R,G,B,A);

    if (result->Create(W,H,color))
        return result;
    else{
        if (result != NULL){
            delete result;
            result = NULL;
        }

        return NULL;
    }
}

//==============================================================================
sf::Image* CSurface::OnCreate(unsigned int W, unsigned int H)
{
    return CSurface::OnCreate(W, H, 0, 0, 0, 255);
}

//==============================================================================
bool CSurface::OnDraw(sf::Image* Surf_Dest, sf::Image* Surf_Src)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    Surf_Dest->Copy(*Surf_Src, 0, 0, sf::IntRect(0, 0, Surf_Src->GetWidth(),  Surf_Src->GetHeight()), true);
    return true;
}

//==============================================================================
bool CSurface::OnDraw(sf::Image* Surf_Dest, sf::Image* Surf_Src, int X, int Y)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    Surf_Dest->Copy(*Surf_Src, X, Y, sf::IntRect(0, 0, Surf_Src->GetWidth(),  Surf_Src->GetHeight()), true);
    return true;
}

//==============================================================================
bool CSurface::OnDraw(sf::Image* Surf_Dest, sf::Image* Surf_Src, unsigned int X, unsigned int Y, int X2, int Y2, int W, int H) {
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    Surf_Dest->Copy(*Surf_Src, X, Y, sf::IntRect(X2, Y2, X2+W, Y2+H), true);
    return true;
}

//==============================================================================
bool CSurface::Transparent(sf::Image* Surf_Dest, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A) {
    if(Surf_Dest == NULL) {
        return false;
    }

    Surf_Dest->CreateMaskFromColor(sf::Color(R, G, B, A));
    return true;
}

void CSurface::FreeSurface(sf::Image* Surf_Dest)
{
    if (Surf_Dest != NULL){
        delete Surf_Dest;
        Surf_Dest = NULL;
    }
}
