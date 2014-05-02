#include "CParticleSystem.h"

CParticleSystem::CParticleSystem(unsigned int count, sf::Int32 ms , float w, float h, float x, float y) :
        _particles(count),_lifeTime(sf::milliseconds(ms)),_emitter(x, y)
{
    for (std::size_t i = 0; i < _particles.size(); ++i){
        _particles[i]._Rectangle.setSize(sf::Vector2f(w, h));
//        _particles[i]._Rectangle.setTexture(&_texture);
    }
}

void CParticleSystem::resetParticle(std::size_t index)
{
    // give a random _Velocity and _LifeTime to the particle
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    _particles[index]._Velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    _particles[index]._LifeTime = sf::milliseconds((std::rand() % 2000) + 1000);

    // reset the position of the corresponding vertex
    _particles[index]._Rectangle.setPosition(_emitter);
}

void CParticleSystem::SetEmitter(sf::Vector2f position)
{
    _emitter = position;
}

void CParticleSystem::Update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < _particles.size(); ++i){
        // Update the particle _LifeTime
        Particle& p = _particles[i];
        p._LifeTime -= elapsed;

        // if the particle is dead, respawn it
        if (p._LifeTime <= sf::Time::Zero)
            resetParticle(i);

        // Update the position of the corresponding vertex
        
        _particles[i]._Rectangle.setPosition(_particles[i]._Rectangle.getPosition()+ p._Velocity * elapsed.asSeconds());

        // Update the alpha (transparency) of the particle according to its _LifeTime
        float ratio = p._LifeTime.asSeconds() / _lifeTime.asSeconds();
        _particles[i]._Rectangle.setFillColor(sf::Color(255,255,255,static_cast<sf::Uint8>(ratio * 255)));
    }
}

void CParticleSystem::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (std::size_t i = 0; i < _particles.size(); ++i){
        Surf_Dest->draw(_particles[i]._Rectangle);
    }
}

bool CParticleSystem::SetTexture(string filename)
{
    if (!CSurface::OnLoad(filename, _texture)){
        cout << "CParticleSystem::SetTexture(): failed to load."<< endl;
        return false;
    }

    for (std::size_t i = 0; i < _particles.size(); ++i){
        _particles[i]._Rectangle.setTexture(&_texture);
    }

    return true;
}
