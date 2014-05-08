#include "CTextLog.h"

CTextLog::CTextLog()
{
    _voice = NULL;
}

void CTextLog::SetTextLog(sf::Text text, sf::SoundBuffer* voice)
{
    OnCleanup();
    _text = text;

    if (voice != NULL)
        _voice = new sf::SoundBuffer(*voice);
}

void CTextLog::OnLoop()
{
    _btnVoice.OnLoop();
}

void CTextLog::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (_voice != NULL)
        _btnVoice.OnRender(Surf_Dest);

    Surf_Dest->draw(_text);
}

void CTextLog::CVoiceButton::Exec(void* data)
{
    sf::SoundBuffer* __voice = static_cast<sf::SoundBuffer*>(data);
    CSoundBank::_SoundControl.PlaySE(*__voice);
}

void CTextLog::OnCleanup()
{
    if (_voice != NULL){
        delete _voice;
        _voice = NULL;
    }
}

void CTextLog::OnMouseMove(int x, int y)
{
    _btnVoice.OnMouseMove(x, y);
}

bool CTextLog::OnLButtonDown(int x, int y)
{
    return _btnVoice.OnLButtonDown(x, y);
}

bool CTextLog::OnLButtonUp(int x, int y)
{
    return _btnVoice.OnLButtonUp(x, y);
}
