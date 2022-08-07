#pragma once

#include <SFML/Audio.hpp>
#include <list>

struct SoundHandler
{
    size_t maxLivingSounds;
    sf::SoundBuffer soundBuffer;
    std::list<sf::Sound> livingSounds;

    void Update();
};
