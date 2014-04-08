/*
* Copyright (C) 2012-2014, <Aeihu.z, aeihu.z@gmail.com>.
*
* Game Scenario Maker is a free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* Version 2(GPLv2) as published by the Free Software Foundation.
*/

#include "CResourceManager.h"

CCharacterLayerControl CResourceManager::_CharacterLayerControl;
CImgLayerControl CResourceManager::_ImgLayerControl;
CImgLayerControl CResourceManager::_BackgroundLayerControl;
CMessageBoxControl CResourceManager::_MessageBoxControl;
CButtonControl CResourceManager::_ButtonControl;

template<typename X>
void CResourceManager::GetInfo(const char* resourcename, map<string, X> xlist)
{
    unsigned int __total = 0;
    cout<<resourcename<<":"<<endl;

    for (typename map<std::string,  X>::iterator it=xlist.begin();
        it!=xlist.end(); it++ )
    {
        __total++;
        cout<<__total<<": "<< (*it).first <<endl;
    }
    cout<<"Total: "<<__total<<endl;
    cout<<"=========================" <<endl<<endl;
}

void CResourceManager::GetInfo()
{
    GetInfo("ImageList", CResourceManager::_ImgLayerControl._ImgLayerList);
    GetInfo("BackgroundList", CResourceManager::_BackgroundLayerControl._ImgLayerList);
    GetInfo("CharacterList", CResourceManager::_CharacterLayerControl._CharacterList);
    GetInfo("ButtonList", CResourceManager::_ButtonControl._ButtonList);
    GetInfo("MessageBoxList", CResourceManager::_MessageBoxControl._MessageBoxList);
    GetInfo("VoiceList", CSoundBank::_SoundControl._voiceList);
    GetInfo("SEList", CSoundBank::_SoundControl._seList);
}
