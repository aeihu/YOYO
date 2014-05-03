#include "CParticleSystemControl.h"

CObject* CParticleSystemControl::GetObject(std::string name)
{
    if (_particleSystemList.count(name) < 1)
        return NULL;

    return &_particleSystemList[name];
}

char CParticleSystemControl::AddParticleSystem(string name, const char* filename)
{
    if (!IsExists(name)){
        _particleSystemList.insert(
            std::pair<std::string,CParticleSystem>(name, CParticleSystem()));
    }
    else
        return -1;

    if(_particleSystemList[name].LoadParticle(filename)){
        return 0;
    }
    else{
        _particleSystemList.erase(name);
        return -2;
    }
}

bool CParticleSystemControl::DelParticleSystem(string name)
{
    if (_particleSystemList.count(name) == 0)
        return false;
    else{
        _particleSystemList.erase(name);
    }
    return true;
}

void CParticleSystemControl::OnLoop(bool &pause)
{
    std::map<std::string, CParticleSystem>::iterator it;
    for ( it=_particleSystemList.begin(); it !=_particleSystemList.end(); it++ )
    {
        static sf::Clock clock;
       // cout << clock.getElapsedTime().asMilliseconds() <<endl;
        (*it).second.Update(clock.restart());
    }
}

void CParticleSystemControl::OnRender(sf::RenderWindow* Surf_Dest)
{
    std::map<std::string, CParticleSystem>::iterator it;
    for ( it=_particleSystemList.begin(); it !=_particleSystemList.end(); it++ )
        (*it).second.OnRender(Surf_Dest);
}

void CParticleSystemControl::OnCleanup()
{
    _particleSystemList.clear();
}