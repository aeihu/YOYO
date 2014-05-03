#include "CParticleSystem.h"

CParticleSystem::CParticleSystem()
{
    _ratio = _rotation = 0.0f;
}

void CParticleSystem::resetParticle(std::size_t index)
{
    // give a random _Velocity and _LifeTime to the particle
    float angle = 3.14f/2;//(std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    _particles[index]._Velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    _particles[index]._LifeTime = sf::milliseconds((std::rand() % _lifeTime.asMilliseconds()) + 1000);

    // reset the position of the corresponding vertex
    float __x = _emitter.x;
    float __y = _emitter.y;
    if (_emitterDeviation.x != 0)
        __x += _emitterDeviation.x /2 - (std::rand() % _emitterDeviation.x);

    if (_emitterDeviation.y != 0)
        __y += _emitterDeviation.y /2 - (std::rand() % _emitterDeviation.y);

    _particles[index]._Rectangle.setPosition(__x, __y);
}

void CParticleSystem::SetEmitter(sf::Vector2f position)
{
    _emitter = position;
}

void CParticleSystem::Update(sf::Time elapsed)
{
    //elapsed = sf::milliseconds(8);
    for (std::size_t i = 0; i < _particles.size(); ++i){
        // Update the particle _LifeTime
        Particle& p = _particles[i];
        p._LifeTime -= elapsed;

        // if the particle is dead, respawn it
        if (p._LifeTime <= sf::Time::Zero)
            resetParticle(i);

        // Update the position of the corresponding vertex
        
        //cout << elapsed.asSeconds() <<endl;
        _particles[i]._Rectangle.setPosition(_particles[i]._Rectangle.getPosition()+ p._Velocity * elapsed.asSeconds());

        // Update the alpha (transparency) of the particle according to its _LifeTime
        _ratio = p._LifeTime.asSeconds() / _lifeTime.asSeconds();
        _particles[i]._Rectangle.setRotation(_ratio*_rotation*1000);
        _particles[i]._Rectangle.setFillColor(sf::Color(255,255,255,static_cast<sf::Uint8>(_ratio * 255)));
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

bool CParticleSystem::LoadParticle(const char* FileName)
{
    list<string> __expressions = Cio::LoadTxtFile(FileName, "\r\n");
    map<string, string> __valueList;

    for (list<string>::iterator it=__expressions.begin();
        it!=__expressions.end(); it++){
        string __paraName = "";
        string __paraValue = "";
        if(Cio::AnalyticExpression((*it), __paraName, __paraValue))
            __valueList[__paraName] = __paraValue;
    }

    if (!CheckList(__valueList))
        return false;

    if (!SetProperty(__valueList))
        return false;

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
    //
    //if (list.count("TALK_FRAME_RATE") < 1){
    //    cout << "can't find value of TALK_FRAME_RATE." << endl;
    //    result = false;
    //}

    return result;
}

bool CParticleSystem::SetProperty(map<string, string>& list)
{
    if (list.count("TEXTURE") > 0){
        if (!CSurface::OnLoad(list["TEXTURE"], _texture))
            return false;
    }

    int __num = atoi(list["PARTICLE_NUM"].c_str());
    float __w = atof(list["PARTICLE_WIDTH"].c_str());
    float __h = atof(list["PARTICLE_HEIGHT"].c_str());

    _particles.clear();
    for (int i=0; i<__num; i++){
        _particles.push_back(Particle());
        _particles[i]._Rectangle.setSize(sf::Vector2f(__w, __h));
        _particles[i]._Rectangle.setOrigin(15,15);
        if (list.count("TEXTURE") > 0)
            _particles[i]._Rectangle.setTexture(&_texture);
    }

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