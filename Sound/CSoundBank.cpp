/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

//==============================================================================
#include "CSoundBank.h"

//==============================================================================
CSoundBank CSoundBank::SoundControl;

//==============================================================================
CSoundBank::CSoundBank() {
	_VoiceList.clear();
}

//------------------------------------------------------------------------------
int CSoundBank::AddSE(std::string name, const char* FileName) {
	if(_SEList.count(name) > 0)
		return -1;

  sf::SoundBuffer Buffer;
  if (!Buffer.LoadFromFile(FileName))
      return -2;

	_SEList[name].first = Buffer;
	_SEList[name].second.SetBuffer(_SEList[name].first);

  return 0;
}
//https://github.com/LaurentGomila/SFML/wiki/Source%3A-MP3-Player
bool CSoundBank::OnLoadBGM(const char* FileName)
{
  if (!_BGM.OpenFromFile(FileName))
	  return false;

	return true;
}

//------------------------------------------------------------------------------
void CSoundBank::OnCleanup()
{
  _SEList.clear();
	_VoiceList.clear();
}


//==============================================================================
bool CSoundBank::PlaySE(string name)
{
	if (_SEList.count(name) < 1)
		return false;

	_SEList[name].second.Play();
	return true;
}

bool CSoundBank::DeleteSE(string name)
{
	if(_SEList.count(name) < 1)
		return false;

	_SEList.erase(name);
	return true;
}

//==============================================================================

sf::Sound::Status CSoundBank::GetBgmStatus()
{
	return _BGM.GetStatus();
}

void CSoundBank::PauseBgm()
{
	_BGM.Pause();
}

void CSoundBank::PlayBgm()
{
	_BGM.Play();
}

bool CSoundBank::Say(const char* FileName)
{    
	sf::SoundBuffer Buffer;
  if (!Buffer.LoadFromFile(FileName))
     return false;

	char name = 0;
	while (_VoiceList.count(name) > 0){
		name++;
	}

	_VoiceList[name].first = Buffer;
	_VoiceList[name].second.SetBuffer(_VoiceList[name].first);
	_VoiceList[name].second.Play();

  return true;
}

void CSoundBank::OnLoop()
{
	if (_VoiceList.size() < 1)
		return;

	for (map<char, pair<sf::SoundBuffer,sf::Sound> >::iterator 
		it=_VoiceList.begin(); it!=_VoiceList.end();  )
	{
		if ((*it).second.second.GetStatus() == sf::Sound::Stopped){
			_VoiceList.erase(it);
			if (it==_VoiceList.end())
				break;
		}
		else
			it++;
	}
}
