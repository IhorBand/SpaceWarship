#include "SoundHandler.h"

void SoundHandler::Update()
{
    livingSounds.remove_if([](sf::Sound& s) {return s.getStatus() == sf::Sound::Stopped; });
}