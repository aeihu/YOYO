#include "CParticleSystemControl.h"

CObject* CParticleSystemControl::GetObject(std::string name)
{
    if (_particleSystemList.count(name) < 1)
        return NULL;

    return &_particleSystemList[name];
}

char CParticleSystemControl::ShowParticleSystem(string name)
{
    if (_particleSystemList.count(name) == 0)
        return -1;

    if (_particleSystemList[name].GetEnable())
        return -2;

    _particleSystemList[name].SetEnable(true);
    return 0;
}

char CParticleSystemControl::HideParticleSystem(string name)
{
    if (_particleSystemList.count(name) == 0)
        return -1;

    if (!_particleSystemList[name].GetEnable())
        return -2;

    _particleSystemList[name].SetEnable(false);
    return 0;
}

char CParticleSystemControl::AddParticleSystem(string name, const char* filename)
{
    if (_particleSystemList.count(name) == 0){
        _particleSystemList.insert(
            std::pair<std::string,CParticleSystem>(name, CParticleSystem()));
    }
    else
        return -1;

    if(_particleSystemList[name].LoadConfigFile(filename)){
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
        //cout << clock.restart().asMilliseconds() <<endl;
        
        (*it).second.OnLoop(clock.restart());
    }
}

void CParticleSystemControl::OnRender(sf::RenderWindow* Surf_Dest, char layer)
{
    std::map<std::string, CParticleSystem>::iterator it;
    for ( it=_particleSystemList.begin(); it !=_particleSystemList.end(); it++ )
        (*it).second.OnRender(Surf_Dest, layer);
}

void CParticleSystemControl::OnCleanup()
{
    _particleSystemList.clear();
}