/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CPARTICLESYSTEM_H_
    #define _CPARTICLESYSTEM_H_

#include <cmath>
#include "../Common/Cio.h"
#include "../Common/CObject.h"
#include "../Graphics/CSurface.h"

class CParticleSystem : public CObject
{
    private:
        struct Particle
        {
            sf::Vector2f        _Velocity;
            sf::Time            _LifeTime;
            sf::RectangleShape  _Rectangle;
        };

        std::vector<Particle>   _particles;
        sf::Time                _lifeTime;
        sf::Vector2f            _emitter;
        sf::Vector2f            _origin;
        sf::Vector2i            _emitterDeviation;
        int                     _angleMin;
        int                     _angleOffet;
        int                     _speedMin;
        int                     _speedOffet;
        int                     _number;
        sf::Texture             _texture;
        float                   _rotation;
        float                   _ratio;
        float                   _width;
        float                   _height;
        bool                    _enable;

        void resetParticle(std::size_t index);
        bool CheckList(map<string, string>& list);
        bool SetProperty(map<string, string>& list);
    public:
        CParticleSystem();

        bool LoadParticle(const char* FileName);
        bool SetTexture(string filename);
        void SetEmitter(sf::Vector2f position);
        void OnLoop(sf::Time elapsed);
        void OnRender(sf::RenderWindow* Surf_Dest);
        bool GetEnable() const;
        void SetEnable(bool val);
};

#endif
