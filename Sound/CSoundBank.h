/*
* Copyright (C) 2012-2013, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#ifndef _CSOUNDBANK_H_
	#define _CSOUNDBANK_H_

#include <SFML/Audio.hpp>
#include <map>
#include <string>

using namespace std;
//==============================================================================


class CSoundBank {
	private:
		map<char, pair<sf::SoundBuffer,sf::Sound> >						_VoiceList;
//	public:

		sf::Music																							_BGM;
		map<string, pair<sf::SoundBuffer,sf::Sound> >					_SEList;
	public:
		static CSoundBank           SoundControl;
		CSoundBank();

		void OnLoop();
		void OnCleanup();

		bool Say(const char* FileName);

		int AddSE(string name, const char* FileName) ;
		bool PlaySE(string name);
		bool DeleteSE(string name);

		bool OnLoadBGM(const char* FileName);
		sf::Sound::Status GetBgmStatus();
		void PlayBgm();
		void PauseBgm();
};


//==============================================================================

#endif
