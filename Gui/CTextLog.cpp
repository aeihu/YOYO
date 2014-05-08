#include "CTextLog.h"

CTextLog::CTextLog()
{
//    _number = 0;
}

void CTextLog::SetTextLog(string text)
{
    CTextFunction::SetString(_text, text);
}

void CTextLog::OnLoop()
{
    _btnVoice.OnLoop();
}

void CTextLog::OnRender(sf::RenderWindow* Surf_Dest)
{
    _btnVoice.OnRender(Surf_Dest);
    Surf_Dest->draw(_text);
}

void CTextLog::CVoiceButton::Exec(void* data)
{

}
