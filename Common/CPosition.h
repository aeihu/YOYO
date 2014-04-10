/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CPOSITION_H_
    #define _CPOSITION_H_

#include <SFML/System.hpp>
#include <map>

using namespace std;

class CPosition
{
    private:
        friend class CResourceManager;
        map<string, sf::Vector2f>        _positions;
    public:
        void AddPosition(string name, float x, float y);
        void DelPosition(string name);
        bool GetPosition(string name, float* x, float* y);
};

#endif
