#include "CTextLog.h"

CTextLog::CTextLog()
{
    _alpha = 0;
    _voice = NULL;
}

void CTextLog::SetTextLog(string text, sf::SoundBuffer* voice, sf::Font& font)
{
    _text.setFont(font);
    SetTextLog(text, voice);
}

void CTextLog::SetTextLog(string text, sf::SoundBuffer* voice)
{
    OnCleanup();
    CTextFunction::SetString(_text, text);

    if (voice != NULL)
        _voice = new sf::SoundBuffer(*voice);
}

void CTextLog::SetAlpha(int alpha)
{
    _alpha = alpha;
}

void CTextLog::SetPosition(float x, float y)
{
    _coordinate.x = x;
    _coordinate.y = y;
}

void CTextLog::OnLoop()
{
    sf::Color __color = _text.getColor();
    __color.a = _alpha;
    _text.setColor(__color);
    _text.setPosition(_coordinate.x, _coordinate.y);
    _btnVoice.SetPosition(_coordinate.x, _coordinate.y);

    if (_voice != NULL){
        _btnVoice._Alpha = _alpha;
        _btnVoice.OnLoop();
    }
}

void CTextLog::OnRender(sf::RenderWindow* Surf_Dest)
{
    if (_voice != NULL)
        _btnVoice.OnRender(Surf_Dest);

    _text.setOrigin(-2.0f, -2.0f);
    //_text.setColor(_shadowColor);
    Surf_Dest->draw(_text);

    _text.setOrigin(0.0f, 0.0f);
    //_text.setColor(_textColor);
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
