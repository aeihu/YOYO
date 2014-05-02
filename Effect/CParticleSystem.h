/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CPARTICLESYSTEM_H_
    #define _CPARTICLESYSTEM_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include "../Common/Cio.h"
#include "../Graphics/CSurface.h"

class CParticleSystem
{
    private:
        struct Particle
        {
            sf::Vector2f _Velocity;
            sf::Time _LifeTime;
            sf::RectangleShape _Rectangle;
        };

        std::vector<Particle> _particles;
        sf::Time _lifeTime;
        sf::Vector2f _emitter;
        sf::Texture _texture;

        void resetParticle(std::size_t index);

    public:
        CParticleSystem(unsigned int count, sf::Int32 ms , float w, float h, float x, float y);

        bool SetTexture(string filename);
        void SetEmitter(sf::Vector2f position);
        void Update(sf::Time elapsed);
        void OnRender(sf::RenderWindow* Surf_Dest);
};

#endif
