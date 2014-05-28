#include "CParticleSystem.h"

CParticleSystem::CParticleSystem()
{
    _width = _height = _ratio = _rotation = 0.0f;
    _number = _speedMin = _speedOffet = _angleOffet = _angleMin = 0;
    _enable = false;
}

CParticleSystem* CParticleSystem::Create(const char* filename)
{
    CParticleSystem* __ptc = new CParticleSystem();
    if (__ptc->LoadConfigFile(filename))
        return __ptc;
    
    delete __ptc;
    return NULL;
}

bool CParticleSystem::GetEnable() const
{
    return _enable;
}
        
void CParticleSystem::SetEnable(bool val)
{
    _enable = val;
}

void CParticleSystem::ResetParticle(std::size_t index)
{
    float __angle = (_angleOffet == 0 ? _angleMin : (std::rand() % _angleOffet) + _angleMin) * 3.14f / 180.f;
    float __speed = _speedOffet == 0 ? _speedMin : (std::rand() % 50) + _speedMin;
    _particles[index]._Velocity = sf::Vector2f(std::cos(__angle) * __speed, std::sin(__angle) * __speed);
    _particles[index]._LifeTime = sf::milliseconds((std::rand() % _lifeTime.asMilliseconds()) + 1000);

    float __x = _emitter.x;
    float __y = _emitter.y;
    if (_emitterDeviation.x != 0)
        __x += _emitterDeviation.x /2 - (std::rand() % _emitterDeviation.x);

    if (_emitterDeviation.y != 0)
        __y += _emitterDeviation.y /2 - (std::rand() % _emitterDeviation.y);

    _particles[index]._Rectangle.setPosition(__x, __y);
    //_particles[index]._Layer = std::rand() % 2;
}

void CParticleSystem::SetEmitter(sf::Vector2f position)
{
    _emitter = position;
}

void CParticleSystem::OnLoop(sf::Time elapsed)
{
    elapsed = sf::milliseconds(11);
    if (_enable)
        if (_particles.size() < _number){
            int __i = _number / 50;
            __i = __i == 0 ? _number : __i;
            for (int i=0; i< __i; i++){
                _particles.push_back(Particle());
                _particles[_particles.size()-1]._Rectangle.setSize(sf::Vector2f(_width, _height));
                _particles[_particles.size()-1]._Rectangle.setOrigin(_origin);
                _particles[_particles.size()-1]._Rectangle.setTexture(&_texture);
            }
        }

    for (std::size_t i = _particles.size(); i > 0; i--){
        Particle& p = _particles[i-1];
        p._LifeTime -= elapsed;

        if (p._LifeTime <= sf::Time::Zero)
            if (_enable)
                ResetParticle(i-1);
            else{
                _particles.erase(_particles.begin()+(i-1));
                continue;
            }

        _particles[i-1]._Rectangle.setPosition(_particles[i-1]._Rectangle.getPosition()+ p._Velocity * elapsed.asSeconds());

        _ratio = p._LifeTime.asSeconds() / _lifeTime.asSeconds();
        _particles[i-1]._Rectangle.setRotation(_ratio*_rotation*1000);
        _particles[i-1]._Rectangle.setFillColor(sf::Color(255,255,255,static_cast<sf::Uint8>(_ratio * 255)));
    }
}

void CParticleSystem::OnRender(sf::RenderWindow* Surf_Dest)
{
    for (std::size_t i = 0; i < _particles.size(); ++i){
//        if (_particles[i]._Layer == layer)
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

bool CParticleSystem::CheckList(map<string, string>& list)
{
    bool result = true;
    if (list.count("PARTICLE_NUM") < 1){
        cout << "can't find value of PARTICLE_NUM." << endl;
        result = false;
    }

    if (list.count("PARTICLE_WIDTH") < 1){
        cout << "can't find value of PARTICLE_WIDTH." << endl;
        result = false;
    }

    if (list.count("PARTICLE_HEIGHT") < 1){
        cout << "can't find value of PARTICLE_HEIGHT." << endl;
        result = false;
    }
    
    if (list.count("LIFE_TIME") < 1){
        cout << "can't find value of LIFE_TIME." << endl;
        result = false;
    }
    
    if (list.count("ROTATION_RATIO") < 1){
        cout << "can't find value of ROTATION_RATIO." << endl;
        result = false;
    }
    
    if (list.count("PARTICLE_ANGLE_MAX") < 1){
        cout << "can't find value of PARTICLE_ANGLE_MAX." << endl;
        result = false;
    }
    
    if (list.count("PARTICLE_ANGLE_MIN") < 1){
        cout << "can't find value of PARTICLE_ANGLE_MIN." << endl;
        result = false;
    }

    if (list.count("PARTICLE_SPEED_MAX") < 1){
        cout << "can't find value of PARTICLE_SPEED_MAX." << endl;
        result = false;
    }
    
    if (list.count("PARTICLE_SPEED_MIN") < 1){
        cout << "can't find value of PARTICLE_SPEED_MIN." << endl;
        result = false;
    }

    if (list.count("PARTICLE_ORIGIN_X") < 1){
        cout << "can't find value of PARTICLE_ORIGIN_X." << endl;
        result = false;
    }

    if (list.count("PARTICLE_ORIGIN_Y") < 1){
        cout << "can't find value of PARTICLE_ORIGIN_Y." << endl;
        result = false;
    }

    return result;
}

bool CParticleSystem::SetProperty(map<string, string>& list)
{
    if (list.count("PARTICLE_TEXTURE") > 0){
        if (!CSurface::OnLoad(list["PARTICLE_TEXTURE"], _texture))
            return false;
    }

    _angleMin = atoi(list["PARTICLE_ANGLE_MIN"].c_str());
    int _angleMax = atoi(list["PARTICLE_ANGLE_MAX"].c_str());

    if (_angleMax - _angleMin < 0){
        cout << "PARTICLE_ANGLE_MIN can't be greater than PARTICLE_ANGLE_MAX." << endl;
        return false;
    }
    _angleOffet = _angleMax - _angleMin;

    _speedMin = atoi(list["PARTICLE_SPEED_MIN"].c_str());
    int _speedMax = atoi(list["PARTICLE_SPEED_MAX"].c_str());

    if (_angleMax - _speedMin <= 0){
        cout << "PARTICLE_SPEED_MIN can't be greater than PARTICLE_SPEED_MAX." << endl;
        return false;
    }
    _speedOffet = _speedMax - _speedMin;

    _number = atoi(list["PARTICLE_NUM"].c_str());
    _number = _number <= 0 ? 1 : _number; 

    _width = atof(list["PARTICLE_WIDTH"].c_str());
    _height = atof(list["PARTICLE_HEIGHT"].c_str());
    _origin.x = atof(list["PARTICLE_ORIGIN_X"].c_str());
    _origin.y = atof(list["PARTICLE_ORIGIN_Y"].c_str());

    _particles.clear();

    if (list.count("EMITTER_X") > 0)
        _emitter.x = atof(list["EMITTER_X"].c_str());
    
    if (list.count("EMITTER_Y") > 0)
        _emitter.y = atof(list["EMITTER_Y"].c_str());

    if (list.count("EMITTER_X_DEVIATION") > 0)
        _emitterDeviation.x = atoi(list["EMITTER_X_DEVIATION"].c_str());
    
    if (list.count("EMITTER_Y_DEVIATION") > 0)
        _emitterDeviation.y = atoi(list["EMITTER_Y_DEVIATION"].c_str());
    
    _lifeTime = sf::milliseconds(atoi(list["LIFE_TIME"].c_str()));
    _rotation = atof(list["ROTATION_RATIO"].c_str());

    return true;
}